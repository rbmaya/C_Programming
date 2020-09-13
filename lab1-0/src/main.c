#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PATT 17
#define SIZE_ASCII (UCHAR_MAX + 1)
#define MAX_BUF 1000

static void table_build(unsigned char *pattern, int *table, int len_patt){
    for (int i = 0; i < SIZE_ASCII; i++){
        table[i] = len_patt;
    }
    for (int i = len_patt - 1; i >= 0; i--){
        table[(pattern[i])] = len_patt - i - 1;
    }
}

static int last_shift(int *table, unsigned char *buf, unsigned char *pattern, int len_patt,
        int last, long long int index_shift) {
    for (size_t i = (size_t)(len_patt - 1); i >= 1; i--) {
        int j = last - len_patt + (int)i;
        printf("%lli ", j + index_shift);
        if (i == 1) {
            last += len_patt;
            return last;
        }
        if (pattern[i - 1] != buf[j - 1]) {
            last += table[(buf[j - 1])] - 1;
            return last;
        }
    }
    return 0;
}

static void boyer_moor(int *table, unsigned char *buf, unsigned char *pattern, int len_patt, int len_buf, long long int index_shift){
    int last = len_patt;
    while (last <= len_buf){
        printf("%lli ", last + index_shift);
        if ((pattern[len_patt - 1]) != (buf[last - 1])){
            last += table[(short)(buf[last - 1])];
        } else {
            last = last_shift(table, buf, pattern, len_patt, last, index_shift);
        }
    }

    if (last > MAX_BUF){
        int buf_end = len_patt - last + len_buf;
        for (int i = 0; i < buf_end; i++){
            buf[i] = buf[len_buf - buf_end + i];
        }
        int check = (int)fread((char *)buf + buf_end, sizeof(char), (size_t)(MAX_BUF - buf_end), stdin);
        if (check == 0) {
            exit(0);
        }
        index_shift += last - len_patt;
        boyer_moor(table, buf, pattern, len_patt, buf_end + check, index_shift);
    }
}

int main() {
    unsigned char pattern[MAX_PATT + 1];
    if (fgets((char *) pattern, MAX_PATT + 1, stdin) == NULL){
        perror("Bad Input");
        return EXIT_FAILURE;
    }

    int table[SIZE_ASCII];

    int len_patt = (int)(strlen((char*)pattern)) - 1;

    table_build(pattern, table, len_patt);

    unsigned char *buffer = malloc(MAX_BUF * sizeof(*buffer));

    if (buffer == NULL) {
        perror("Memory Error");
        return EXIT_FAILURE;
    }

    int len_buf = (int)fread(buffer, sizeof(char), (size_t)MAX_BUF, stdin);
    long long int index_shift = 0;

    boyer_moor(table, buffer, pattern, len_patt, len_buf, index_shift);

    free(buffer);

    return 0;
}
