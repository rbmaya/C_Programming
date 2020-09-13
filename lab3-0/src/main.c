#include <stdio.h>
#include <stdlib.h>

static void swap(int *x, int *y){
    int z = *x;
    *x = *y;
    *y = z;
}

static void sorting (int *num, int left, int right){
    int central;
    int i = left;
    int j = right;

    central = num[(i + j) / 2];

    while (i < j) {
        while (num[i] < central) {
            i++;
        }
        while (num[j] > central) {
            j--;
        }
        if (i <= j) {
            swap(&num[i],&num[j]);
            j--;
            i++;
        }
    }

    if (i < right) {
        sorting(num, i, right);
    }

    if (j > left) {
        sorting(num, left, j);
    }
}

int main() {
    int n;
    int *a;
    int i;

    scanf("%d",&n);

    a = (int*)malloc(n * sizeof(int));

    if (a == NULL){
        perror("Memory Error");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    sorting(a, 0, n - 1);

    for (i = 0; i < n; i++) {
        printf("%d ",a[i]);
    }
    free(a);
    return 0;
}
