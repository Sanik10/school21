#include <stdio.h>

#define ARRAY_SIZE 10

int input(int *arr, int size);

void sort(int *arr, int size);

void output(int *arr, int size);

int main() {
    int arr[ARRAY_SIZE];

    if (input(arr, ARRAY_SIZE) != 0) {
        printf("n/a\n");
        return 1;
    }

    sort(arr, ARRAY_SIZE);

    output(arr, ARRAY_SIZE);

    return 0;
}

int input(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            return 1;
        }
    }

    char trash;
    while ((trash = getchar()) != '\n' && trash != EOF) {
        if (trash != ' ' && trash != '\t' && trash != '\r' && trash != '\v') {
            printf("n/a\n");
            return 1;
        }
    }

    if (trash != '\n') {
        return 1;
    }

    return 0;
}

void sort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void output(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}