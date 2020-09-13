#include <stdio.h>
#include <stdlib.h>
#include "stack_num_and_oper.h"
#include "calculator.h"
#include "RPN.h"

#define MAX_STRING 2000

int main() {
    stack_num *top_num = NULL;
    stack_oper *top_oper = NULL;

    char *string = malloc(MAX_STRING * sizeof(*string));

    if (string == NULL){
        perror("Memory Error");
        return EXIT_FAILURE;
    }
    fgets(string, MAX_STRING, stdin);

    printf("%d", reverse_polish_notation(string, top_num, top_oper));

    free(string);
    free(top_num);
    free(top_oper);

    return 0;
}
