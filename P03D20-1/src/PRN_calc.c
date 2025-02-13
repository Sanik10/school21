#include "PRN_calc.h"

#include <stdio.h>

#include "calc.h"
#include "parser_alb.h"
#include "settings.h"

double calculate_postfix(list_node *postfix, double x) {
    list_node *lexeme = postfix;
    stack_node *stack_root = init_node_stack_num(0);
    double number = 0;

    while (lexeme) {
        if (lexeme->oper == 'x') {
            number = x;

        } else if (lexeme->value) {
            number = lexeme->value;

        } else if (lexeme->oper == '-') {
            number = pop_num(&stack_root);
            stack_node *stack_head = get_head(stack_root);
            if (stack_head == stack_root)
                number = -number;
            else {
                number = pop_num(&stack_root) - number;
            }

        } else if (lexeme->oper == '+') {
            number = pop_num(&stack_root);
            number += pop_num(&stack_root);

        } else if (lexeme->oper == '*') {
            number = pop_num(&stack_root);
            number *= pop_num(&stack_root);

        } else if (lexeme->oper == '/') {
            number = pop_num(&stack_root);
            number = pop_num(&stack_root) / number;

        } else if (lexeme->oper == 'i') {
            number = sin(pop_num(&stack_root));

        } else if (lexeme->oper == 'o') {
            number = cos(pop_num(&stack_root));

        } else if (lexeme->oper == 'a') {
            number = 1 / tan(pop_num(&stack_root));

        } else if (lexeme->oper == 't') {
            number = tan(pop_num(&stack_root));

        } else if (lexeme->oper == 'q') {
            number = sqrt(pop_num(&stack_root));

        } else if (lexeme->oper == 'n') {
            number = log(pop_num(&stack_root));
        } else if (lexeme->oper == '^') {
            number = pow(number, pop_num(&stack_root));
        }

        stack_root = push_num(number, stack_root);

        lexeme = lexeme->next;
    }

    double y = pop_num(&stack_root);
    destroy_stack(stack_root);
    return y;
}

double *calculate_array(list_node *postfix) {
    double *array = malloc(WIDTH * sizeof(double));
    for (int i = 0; i < WIDTH; i++) {
        array[i] = calculate_postfix(postfix, scale_to_4pi(i));
    }
    return array;
}