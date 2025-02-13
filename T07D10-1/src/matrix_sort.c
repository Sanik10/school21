#include <stdio.h>
#include <stdlib.h>

#define STATIC_MAX_SIZE 100

// Прототипы функций
void menu();
void static_allocation(int rows, int cols);
void single_block_dynamic_allocation(int rows, int cols);
void array_of_pointers_allocation(int rows, int cols);
void array_of_pointers_to_arrays_allocation(int rows, int cols);
void input_matrix(int **matrix, int rows, int cols);
void print_matrix(int **matrix, int rows, int cols);
void free_matrix(int **matrix, int rows);

int main() {
    menu();
    return 0;
}

void menu() {
    int choice, rows, cols;
    printf("Способы выделения памяти для матрицы:\n");
    printf("1. Статическое выделение\n");
    printf("2. Динамическое выделение одним блоком\n");
    printf("3. Выделение через массив указателей\n");
    printf("4. Выделение через массив указателей на массивы\n");
    printf("Введите ваш выбор: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("n/a\n");
        exit(1);
    }
    printf("Введите количество строк и столбцов: ");
    if (scanf("%d %d", &rows, &cols) != 2) {
        printf("n/a\n");
        exit(1);
    }
    if (rows <= 0 || cols <= 0) {
        printf("n/a\n");
        exit(1);
    }

    switch (choice) {
        case 1:
            static_allocation(rows, cols);
            break;
        case 2:
            single_block_dynamic_allocation(rows, cols);
            break;
        case 3:
            array_of_pointers_allocation(rows, cols);
            break;
        case 4:
            array_of_pointers_to_arrays_allocation(rows, cols);
            break;
        default:
            printf("n/a\n");
            exit(1);
    }
}

void static_allocation(int rows, int cols) {
    if (rows > STATIC_MAX_SIZE || cols > STATIC_MAX_SIZE) {
        printf("n/a\n");
        exit(1);
    }
    int matrix[STATIC_MAX_SIZE][STATIC_MAX_SIZE];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("n/a\n");
                exit(1);
            }
        }
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
}

void single_block_dynamic_allocation(int rows, int cols) {
    int *matrix = malloc(rows * cols * sizeof(int));
    if (!matrix) {
        printf("n/a\n");
        exit(1);
    }
    for (int i = 0; i < rows * cols; ++i) {
        if (scanf("%d", &matrix[i]) != 1) {
            printf("n/a\n");
            free(matrix);
            exit(1);
        }
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d", matrix[i * cols + j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
    free(matrix);
}

void array_of_pointers_allocation(int rows, int cols) {
    int **matrix = malloc(rows * sizeof(int *));
    if (!matrix) {
        printf("n/a\n");
        exit(1);
    }
    for (int i = 0; i < rows; ++i) {
        matrix[i] = malloc(cols * sizeof(int));
        if (!matrix[i]) {
            for (int j = 0; j < i; ++j) free(matrix[j]);
            free(matrix);
            printf("n/a\n");
            exit(1);
        }
    }
    input_matrix(matrix, rows, cols);
    print_matrix(matrix, rows, cols);
    free_matrix(matrix, rows);
}

void array_of_pointers_to_arrays_allocation(int rows, int cols) {
    int **matrix = malloc(rows * sizeof(int *));
    if (!matrix) {
        printf("n/a\n");
        exit(1);
    }
    int *data = malloc(rows * cols * sizeof(int));
    if (!data) {
        free(matrix);
        printf("n/a\n");
        exit(1);
    }
    for (int i = 0; i < rows; ++i) {
        matrix[i] = &data[i * cols];
    }
    input_matrix(matrix, rows, cols);
    print_matrix(matrix, rows, cols);
    free(data);
    free(matrix);
}

void input_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("n/a\n");
                exit(1);
            }
        }
    }
}

void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
}

void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}