#ifndef UNTITLED1_STACK_NUM_AND_OPER_H
#define UNTITLED1_STACK_NUM_AND_OPER_H

#include <stdbool.h>

typedef struct stack_num{
    int num;
    struct stack_num *next;
} stack_num;

typedef struct stack_oper{
    char oper;
    struct stack_oper *next;
} stack_oper;

bool empty_stack_num(stack_num**);
bool empty_stack_oper(stack_oper**);
void push_num(stack_num**, int);
void push_oper(stack_oper**, char);
void pop_num(stack_num**);
void pop_oper(stack_oper**);

#endif
