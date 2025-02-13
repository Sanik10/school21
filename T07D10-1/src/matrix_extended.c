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
void find_max_in_rows_static(int matrix[STATIC_MAX_SIZE][STATIC_MAX_SIZE], int rows, int cols,
                             int *max_in_rows);
void find_min_in_cols_static(int matrix[STATIC_MAX_SIZE][STATIC_MAX_SIZE], int rows, int cols,
                             int *min_in_cols);
void find_max_in_rows(int **matrix, int rows, int cols, int *max_in_rows);
void find_min_in_cols(int **matrix, int rows, int cols, int *min_in_cols);
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

    int max_in_rows[rows];
    int min_in_cols[cols];

    find_max_in_rows_static(matrix, rows, cols, max_in_rows);
    find_min_in_cols_static(matrix, rows, cols, min_in_cols);

    printf("\n");
    for (int i = 0; i < rows; ++i) {
        printf("%d", max_in_rows[i]);
        if (i < rows - 1) printf(" ");
    }
    printf("\n");
    for (int j = 0; j < cols; ++j) {
        printf("%d", min_in_cols[j]);
        if (j < cols - 1) printf(" ");
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

    int *max_in_rows = malloc(rows * sizeof(int));
    int *min_in_cols = malloc(cols * sizeof(int));

    int **matrix_ptr = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        matrix_ptr[i] = &matrix[i * cols];
    }

    find_max_in_rows(matrix_ptr, rows, cols, max_in_rows);
    find_min_in_cols(matrix_ptr, rows, cols, min_in_cols);

    printf("\n");
    for (int i = 0; i < rows; ++i) {
        printf("%d", max_in_rows[i]);
        if (i < rows - 1) printf(" ");
    }
    printf("\n");
    for (int j = 0; j < cols; ++j) {
        printf("%d", min_in_cols[j]);
        if (j < cols - 1) printf(" ");
    }

    free(max_in_rows);
    free(min_in_cols);
    free(matrix_ptr);
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

    int *max_in_rows = malloc(rows * sizeof(int));
    int *min_in_cols = malloc(cols * sizeof(int));

    find_max_in_rows(matrix, rows, cols, max_in_rows);
    find_min_in_cols(matrix, rows, cols, min_in_cols);

    printf("\n");
    for (int i = 0; i < rows; ++i) {
        printf("%d", max_in_rows[i]);
        if (i < rows - 1) printf(" ");
    }
    printf("\n");
    for (int j = 0; j < cols; ++j) {
        printf("%d", min_in_cols[j]);
        if (j < cols - 1) printf(" ");
    }

    free(max_in_rows);
    free(min_in_cols);
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

    int *max_in_rows = malloc(rows * sizeof(int));
    int *min_in_cols = malloc(cols * sizeof(int));

    find_max_in_rows(matrix, rows, cols, max_in_rows);
    find_min_in_cols(matrix, rows, cols, min_in_cols);

    printf("\n");
    for (int i = 0; i < rows; ++i) {
        printf("%d", max_in_rows[i]);
        if (i < rows - 1) printf(" ");
    }
    printf("\n");
    for (int j = 0; j < cols; ++j) {
        printf("%d", min_in_cols[j]);
        if (j < cols - 1) printf(" ");
    }

    free(max_in_rows);
    free(min_in_cols);
    free(data);
    free(matrix);
}

// Функция для ввода матрицы
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

// Функция для печати матрицы
void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
}

// Функции для поиска максимального в строках и минимального в столбцах для статически выделенной матрицы
void find_max_in_rows_static(int matrix[STATIC_MAX_SIZE][STATIC_MAX_SIZE], int rows, int cols,
                             int *max_in_rows) {
    for (int i = 0; i < rows; ++i) {
        int max = matrix[i][0];
        for (int j = 1; j < cols; ++j) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
        max_in_rows[i] = max;
    }
}

void find_min_in_cols_static(int matrix[STATIC_MAX_SIZE][STATIC_MAX_SIZE], int rows, int cols,
                             int *min_in_cols) {
    for (int j = 0; j < cols; ++j) {
        int min = matrix[0][j];
        for (int i = 1; i < rows; ++i) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        min_in_cols[j] = min;
    }
}

// Функции для поиска максимального в строках и минимального в столбцах для динамически выделенной матрицы
void find_max_in_rows(int **matrix, int rows, int cols, int *max_in_rows) {
    for (int i = 0; i < rows; ++i) {
        int max = matrix[i][0];
        for (int j = 1; j < cols; ++j) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
        max_in_rows[i] = max;
    }
}

void find_min_in_cols(int **matrix, int rows, int cols, int *min_in_cols) {
    for (int j = 0; j < cols; ++j) {
        int min = matrix[0][j];
        for (int i = 1; i < rows; ++i) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        min_in_cols[j] = min;
    }
}

// Функция для освобождения памяти динамически выделенной матрицы
void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}