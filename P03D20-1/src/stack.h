#ifndef STACK_H
#define STACK_H

typedef struct stack_node {
    int value;
    double number;
    struct stack_node *previous;
} stack_node;

stack_node *init_node_stack(int value);
stack_node *push(int value, stack_node *end);
int pop(stack_node **end);

stack_node *init_node_stack_num(double num);
stack_node *push_num(double num, stack_node *end);
double pop_num(stack_node **end);

stack_node *get_head(stack_node *root);

void destroy_stack(stack_node *end);

#endif