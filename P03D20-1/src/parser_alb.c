#include "parser_alb.h"

#include "stack.h"

int precedence(char oper);
int is_operator(char c);
void handle_number(const char** token, list_node** output_list, list_node** current_list);
void handle_variable(list_node** output_list, list_node** current_list);
void handle_operator(char token, stack_node** operator_stack, list_node** current_list);
void handle_function(const char** token, stack_node** operator_stack);

list_node* parse_to_rpn(const char* expression) {
    stack_node* operator_stack = NULL;
    list_node* output_list = NULL;
    list_node* current_list = NULL;

    for (const char* token = expression; *token != '\0'; ++token) {
        if (is_digit(*token)) {
            handle_number(&token, &output_list, &current_list);
        } else if (*token == 'x' || *token == 'X') {
            handle_variable(&output_list, &current_list);
        } else if (is_operator(*token)) {
            handle_operator(*token, &operator_stack, &current_list);
        } else if (*token == '(') {
            operator_stack = push(*token, operator_stack);
        } else if (*token == ')') {
            while (operator_stack && operator_stack->value != '(') {
                char oper = pop(&operator_stack);
                current_list = append(current_list, oper, 0);
            }
            pop(&operator_stack);
        } else if (is_alpha(*token)) {
            handle_function(&token, &operator_stack);
        }
    }

    while (operator_stack) {
        char oper = pop(&operator_stack);
        current_list = append(current_list, oper, 0);
    }
    return output_list;
}

int precedence(char oper) {
    int flag;
    switch (oper) {
        case '+':
            flag = 1;
            break;
        case '-':
            flag = 1;
            break;
        case '*':
            flag = 1;
            break;
        case '/':
            flag = 2;
            break;
        case '^':
            flag = 3;
            break;
        case 'i':
            flag = 4;
            break;
        case 'o':
            flag = 4;
            break;
        case 'a':
            flag = 4;
            break;
        case 't':
            flag = 4;
            break;
        case 'q':
            flag = 4;
            break;
        case 'n':
            flag = 4;
            break;
        default:
            flag = 0;
            break;
    }
    return flag;
}

int is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

void handle_number(const char** token, list_node** output_list, list_node** current_list) {
    double value = strtod(*token, (char**)token);
    --(*token);
    if (*output_list == NULL) {
        *output_list = init_node_list(0, value);
        *current_list = *output_list;
    } else {
        *current_list = append(*current_list, 0, value);
    }
}

void handle_variable(list_node** output_list, list_node** current_list) {
    if (*output_list == NULL) {
        *output_list = init_node_list('x', 0);
        *current_list = *output_list;
    } else {
        *current_list = append(*current_list, 'x', 0);
    }
}

void handle_operator(char token, stack_node** operator_stack, list_node** current_list) {
    while (*operator_stack && precedence((*operator_stack)->value) >= precedence(token)) {
        char oper = pop(operator_stack);
        *current_list = append(*current_list, oper, 0);
    }
    *operator_stack = push(token, *operator_stack);
}

void handle_function(const char** token, stack_node** operator_stack) {
    if ((*token)[1] == 'i') {  // sin
        *operator_stack = push('i', *operator_stack);
        *token += 2;
    } else if ((*token)[1] == 'o') {  // cos
        *operator_stack = push('o', *operator_stack);
        *token += 2;
    } else if ((*token)[1] == 'a') {  // tan
        *operator_stack = push('a', *operator_stack);
        *token += 2;
    } else if ((*token)[1] == 't') {  // ctg
        *operator_stack = push('t', *operator_stack);
        *token += 2;
    } else if ((*token)[1] == 'q') {  // sqrt
        *operator_stack = push('q', *operator_stack);
        *token += 3;
    } else if ((*token)[1] == 'n') {  // ln
        *operator_stack = push('n', *operator_stack);
        *token += 1;
    }
}

int is_digit(char c) { return c >= '0' && c <= '9'; }

int is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }