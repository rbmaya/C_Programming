#include <stdio.h>
#include <stdlib.h>
#include "stack_num_and_oper.h"

void syntax_error() {
    printf("syntax error\n");
    exit(0);
}

void calculator(stack_num **top_num, stack_oper **top_oper, char oper) {
    if ((oper == '(') || (oper == ')'))
        syntax_error();
    else {
        int num1 = 0, num2 = 0;
        if (!empty_stack_num(top_num)) {
            num1 = (*top_num)->num;
            pop_num(top_num);
        } else syntax_error();
        if (!empty_stack_num(top_num)) {
            num2 = (*top_num)->num;
            pop_num(top_num);
        } else syntax_error();
        if (oper == '+')
            push_num(top_num, num2 + num1);
        if (oper == '-')
            push_num(top_num, num2 - num1);
        if (oper == '*')
            push_num(top_num, num2 * num1);
        if (oper == '/') {
            if (num1 != 0) {
                push_num(top_num, num2 / num1);
            } else {
                printf("division by zero");
                free(*top_num);
                free(*top_oper);
                exit(0);
            }
        }
    }
}
