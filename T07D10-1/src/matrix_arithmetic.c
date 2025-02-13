#include <stdio.h>
#include <stdlib.h>

// Функция для транспонирования матрицы
void transpose_matrix(int **matrix, int **result, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[j][i] = matrix[i][j];
        }
    }
}

// Функция для умножения матриц
void multiply_matrices(int **matrix1, int **matrix2, int **result, int rows1, int cols1, int cols2) {
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// Функция для ввода матрицы
void input_matrix(int **matrix, int rows, int cols) {
    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("n/a\n");
                exit(1);
            }
        }
    }
}

// Функция для вывода матрицы
void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для освобождения памяти, выделенной под матрицу
void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int rows, cols;

    printf("Введите количество строк и столбцов матрицы: ");
    if (scanf("%d %d", &rows, &cols) != 2) {
        printf("n/a\n");
        return 1;
    }

    // Выделение памяти для матрицы
    int **matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        matrix[i] = malloc(cols * sizeof(int));
    }

    // Ввод матрицы
    input_matrix(matrix, rows, cols);

    // Транспонирование матрицы
    int **transposed_matrix = malloc(cols * sizeof(int *));
    for (int i = 0; i < cols; ++i) {
        transposed_matrix[i] = malloc(rows * sizeof(int));
    }
    transpose_matrix(matrix, transposed_matrix, rows, cols);

    // Умножение матрицы на транспонированную
    int **result_matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        result_matrix[i] = malloc(rows * sizeof(int));
    }
    multiply_matrices(matrix, transposed_matrix, result_matrix, rows, cols, rows);

    // Вывод результирующей матрицы
    printf("Результирующая матрица:\n");
    print_matrix(result_matrix, rows, rows);

    // Освобождение памяти
    free_matrix(matrix, rows);
    free_matrix(transposed_matrix, cols);
    free_matrix(result_matrix, rows);

    return 0;
}