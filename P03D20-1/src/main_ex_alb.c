#include <stdio.h>

#include "input_alb.h"
#include "list.h"
#include "parser_alb.h"
#include "settings.h"

void print_list(list_node* list);

int main() {
    char expression[MAX_EXPRESSION_LENGTH];
    input(expression);
    printf("Сырая строка: %s\n", expression);
    list_node* rpn_list = parse_to_rpn(expression);
    print_list(rpn_list);
    destroy_list(rpn_list);  // Освобождаем память
    return 0;
}

// Функция для печати списка
void print_list(list_node* list) {
    while (list) {
        if (list->oper == 'v') {
            if (list->value == -1)
                printf("x ");
            else
                printf("%lf ", list->value);
        } else {
            printf("%c ", list->oper);
        }
        list = list->next;
    }
    printf("\n");
    ;
}