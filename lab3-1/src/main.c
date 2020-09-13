#include <stdio.h>
#include <stdlib.h>

static void swap(int *x, int *y){
    int z = *x;
    *x = *y;
    *y = z;
}

static void sorting (int *num, int n, int i) {
    int max_descendant = 0;
    int done = 0;
    while ((2 * i + 1 < n) && (done != 1)){
       if ((2 * i + 2 < n) && (num[2 * i + 2] > num [2 * i + 1])){
           max_descendant = 2 * i + 2;
       } else max_descendant = 2 * i + 1;

       if (num[i] < num[max_descendant]){
           swap(&num[i],&num[max_descendant]);
           i = max_descendant;
        } else done = 1;
    }
}

int main() {
    int n;
    int *a;
    int i;

    scanf("%d",&n);

    a = malloc(n * sizeof(int));

    if (a == NULL){
        perror("Memory Error");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (i = n / 2 - 1; i >= 0; i--){
        sorting(a, n, i);
    }

    for (i = n - 1; i > 0; i--){
        swap(&a[0],&a[i]);
        sorting(a, i, 0);
    }

    for (i = 0 ; i < n; i++) {
        printf("%d ",a[i]);
    }
    free(a);
    return 0;
}
