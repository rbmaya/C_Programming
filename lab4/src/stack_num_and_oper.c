#include <stdbool.h>
#include <stdlib.h>

typedef struct stack_num{
    int num;
    struct stack_num *next;
} stack_num;

typedef struct stack_oper{
    char oper;
    struct stack_oper *next;
} stack_oper;

bool empty_stack_num(stack_num **top_num){
    if (*top_num == NULL){
        return true;
    } else return false;
}

bool empty_stack_oper(stack_oper **top_oper){
    if (*top_oper == NULL){
        return *top_oper == NULL;
    } else return false;
}

void push_num(stack_num **top, int data){
    stack_num *temp = (stack_num*)malloc(sizeof(stack_num));
    temp->num = data;
    temp->next = *top;
    *top = temp;
}

void push_oper(stack_oper **top, char data){
    stack_oper *temp = (stack_oper*)malloc(sizeof(stack_oper));
    temp->oper = data;
    temp->next = *top;
    *top = temp;
}

void pop_num(stack_num **top){
    stack_num *temp = *top;
    *top = (*top)->next;
    free(temp);
}

void pop_oper(stack_oper **top){
    stack_oper *temp = *top;
    *top = (*top)->next;
    free(temp);
}
