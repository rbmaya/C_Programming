#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATT 17
#define MAX_BUF 1000
#define SIMPLE_NUM 3

static void degree_number(int degree, long long int *deg_num){
    *deg_num = 1;
    for (int i = 1; i <= degree; i++){
        deg_num[i] = deg_num[i - 1]*SIMPLE_NUM;
    }
}

static long long int hash_string(int len_string, unsigned char *string, long long int *deg_num){
    long long int hash = 0;
    for (int i = 0; i < len_string; i++){
      hash += (string[i]%SIMPLE_NUM)*deg_num[i];
    }
    return hash;
}

static void table_hash(unsigned char *string, long long int *table, int len_patt, int len_buf,
        long long int *deg_num){
    for (int i = 1; i <= len_buf - len_patt; i++) {
        table[i] = (table[i - 1]
                - string[i - 1] % SIMPLE_NUM)/SIMPLE_NUM
                + (string[i - 1 + (long long)len_patt] % SIMPLE_NUM) * deg_num[len_patt - 1];
    }
}

static void rabin_karp(unsigned char *buf, int len_buf, unsigned char *pattern, int len_patt,
        long long int hash_patt, long long int *table,
        long long int index_shift, long long int *deg_num){

    table_hash(buf, table, len_patt, len_buf, deg_num);
    int last = 0;
    while (last + len_patt <= len_buf){
        if (table[last] == hash_patt){
            for (int j = 0; j < len_patt; j++) {
                int i = last + j;
                    printf("%lli ", i + 1 + index_shift);
                    if (buf[i] != pattern[j]) {
                        break;
                    }
            }
        }
        last++;
    }

    if (last + len_patt > MAX_BUF){
        int buf_end = len_buf - last;
        for (int i = 0; i < buf_end; i++){
            buf[i] = buf[len_buf - buf_end + i];
        }
        int check = (int)fread((char *)buf + buf_end, sizeof(char), (size_t)(MAX_BUF - buf_end), stdin);
        if (check == 0) {
            exit(0);
        }
        index_shift += len_buf - buf_end;
        rabin_karp(buf, buf_end + check, pattern, len_patt, hash_patt, table, index_shift, deg_num);
    }
}

int main() {
    unsigned char pattern[MAX_PATT + 1];
    if (fgets((char *) pattern, MAX_PATT + 1, stdin) == NULL){
        perror("Bad Input");
        return EXIT_FAILURE;
    }

    int len_patt = (int)(strlen((char*)pattern)) - 1;
    long long int deg_num[MAX_PATT];
    degree_number(len_patt - 1, deg_num);
    long long int hash_patt = hash_string(len_patt, pattern, deg_num);

    printf("%lli ", hash_patt);

    unsigned char *buffer = malloc(MAX_BUF * sizeof(*buffer));

    if (buffer == NULL) {
        perror("Memory Error");
        return EXIT_FAILURE;
    }

    int len_buf = (int)fread(buffer, sizeof(char), (size_t)MAX_BUF, stdin);

    if (len_buf == 0){
        exit(0);
    }

    long long int index_shift = 0;
    
    long long int table[MAX_BUF];
    *table = hash_string(len_patt, buffer, deg_num);

    rabin_karp(buffer, len_buf, pattern, len_patt, hash_patt, table, index_shift, deg_num);

    free(buffer);
    return 0;
}
