#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE_PER 10

static void bad_input(){
    printf("bad input");
    exit(0);
}

static bool check_in_table(const char *per, int *count){
    char table[] = "0123456789";
    for (size_t i = 0; i < sizeof(table); ++i){
        if (*per == table[i]){
            count[*per - '0']++;
            return true;
        }
    }
    return false;
}

static void check(char *per) {
    int count[SIZE_PER] = {0};
    int len_per = strlen(per);
    for (int i = 0; i < len_per; i++) {
        if (!(check_in_table(&per[i], count)) || (count[per[i] - '0'] > 1)){
            bad_input();
        }
    }
}

static void swap(char *a, int i, int j){
    char c = a[i];
    a[i] = a[j];
    a[j] = c;
}

static void reverse (char *a, int len_per, int pos){
    for (int i = pos + 1; i <= (len_per + pos) / 2; i++) {
        swap(a, i, len_per - i + pos);
    }
}

static void permutation(char *a, int len_per, int n) {
    while (n > 0) {
            int pos = len_per - 2;
            while (a[pos] > a[pos + 1]){ pos--; }
            if (pos < 0) {break;}

            int i = len_per - 1;
            while ((i > pos) && (a[i] < a[pos])) {
                i--;
            }
            swap(a, i, pos);

            if ((a[pos + 1] < a[pos + 2]) || (pos + 2 > len_per)) {
                printf("%s\n", a);
            } else {
                reverse(a, len_per, pos);
                printf("%s\n", a);
            }
        n--;
    }

}

int main() {
    char per[SIZE_PER + 1] = {0};
    int n;

    scanf("%10s", per);
    scanf("%d", &n);
    if (n <= 0) {
        return 0;
    }
    int len_per = strlen(per);

    check(per);

    permutation(per, len_per, n);

    return 0;
}
