#include "PRN_CALC.h"
#include "calc.h"
#include "input_alb.h"
#include "parser_alb.h"
#include "settings.h"

void print_graph(double **matrix);
double **init_matrix();

int main() {
    char expression[MAX_EXPRESSION_LENGTH];
    input(expression);
    list_node *list_expression = parse_to_rpn(expression);
    double *array = calculate_array(list_expression);
    double **matrix = init_matrix();
    array_to_matrix(array, matrix);
    print_graph(matrix);
    free(matrix);
    destroy_list(list_expression);
    return 0;
}

double **init_matrix() {
    double **matrix = malloc(WIDTH * HEIGHT * sizeof(double) + HEIGHT * sizeof(double *));
    double *ptr = (double *)(matrix + HEIGHT);
    for (int i = 0; i < HEIGHT; i++) matrix[i] = ptr + WIDTH * i;
    return matrix;
}

void print_graph(double **matrix) {
    /*
        INPUT: Matrix contains 0 and 1
                where 0 - Field
                      1 - graph
        OUTPUT: Graph in console
    */
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", matrix[i][j] ? GRAPH_SYMB : FIELD_SYMB);
        }
        printf("\n");
    }
}