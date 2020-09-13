#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "stack_num_and_oper.h"
#include "calculator.h"

bool is_operation(char symb){
    char operation[] = "/*+-()";
    if (strchr(operation, symb) != NULL)
        return true;
    return false;
}

short priority(char oper){
    switch(oper){
        case '(':
        case ')':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        default: abort();
    }
}

int reverse_polish_notation(char *string, stack_num *top_num, stack_oper *top_oper){
    int str_len = (int)strlen(string) - 1;
    if (str_len == 0)
        syntax_error();
    int brackets = 0, num_in_brack = 0;
    for (int i = 0; i < str_len; ++i) {
        if (isdigit(string[i])){
            int num = atoi(string + i);
            i++;
            push_num(&top_num, num);
            while (isdigit(string[i]))
                i++;
            if (brackets != 0)
                num_in_brack++;
        }
        if (!isdigit(string[i])){
            if (string[i] == '\n')
                break;
            if ((string[i] == EOF) || (!is_operation(string[i])))
                syntax_error();
            if (string[i] == '(') {
                push_oper(&top_oper, string[i]);
                brackets++;
            }
            if (string[i] == ')') {
                brackets--;
                if (num_in_brack != 0) {
                    while (top_oper->oper != '(') {
                        calculator(&top_num, &top_oper, top_oper->oper);
                        pop_oper(&top_oper);
                    }
                    pop_oper(&top_oper);
                } else syntax_error();
            }
            if ((string[i] == '+') || (string[i] == '-') || (string[i] == '*') || (string[i] == '/')) {
                while (!(empty_stack_oper(&top_oper)) && (priority(top_oper->oper) >= priority(string[i]))) {
                    calculator(&top_num, &top_oper, top_oper->oper);
                    pop_oper(&top_oper);
                }
                if (empty_stack_oper(&top_oper) || (priority(top_oper->oper) < priority(string[i])))
                    push_oper(&top_oper, string[i]);
            }
        }

    }
    if (brackets != 0)
        syntax_error();
    if (!empty_stack_oper(&top_oper)) {
        while (!empty_stack_oper(&top_oper)) {
            calculator(&top_num, &top_oper, top_oper->oper);
            pop_oper(&top_oper);
        }
    }
    int result = 0;
    if (!empty_stack_num(&top_num))
        result = top_num->num;
    free(&top_num->num);
    return result;
}
