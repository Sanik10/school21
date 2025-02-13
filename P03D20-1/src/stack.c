#include "stack.h"

#include <stdlib.h>

stack_node *get_head(stack_node *root) {
    stack_node *head = root;
    while (head->previous != NULL) head = head->previous;
    return head;
}

stack_node *init_node_stack(int value) {
    stack_node *node = (stack_node *)malloc(sizeof(stack_node));
    node->value = value;
    node->previous = NULL;
    return node;
}
stack_node *push(int value, stack_node *end) {
    stack_node *new_node = init_node_stack(value);
    new_node->previous = end;
    return new_node;
}
int pop(stack_node **end) {
    int popped = 0;
    if (end) {
        struct stack_node *temp = *end;
        *end = (*end)->previous;
        popped = temp->value;
        free(temp);
    }
    return popped;
}

stack_node *init_node_stack_num(double num) {
    stack_node *node = (stack_node *)malloc(sizeof(stack_node));
    node->number = num;
    node->previous = NULL;
    return node;
}
stack_node *push_num(double num, stack_node *end) {
    stack_node *new_node = init_node_stack_num(num);
    new_node->previous = end;
    return new_node;
}
double pop_num(stack_node **end) {
    double popped = 0;
    if (end) {
        struct stack_node *temp = *end;
        *end = (*end)->previous;
        popped = temp->number;
        free(temp);
    }
    return popped;
}

void destroy_stack(stack_node *end) {
    while (end) {
        stack_node *temp = end;
        end = end->previous;
        free(temp);
    }
}