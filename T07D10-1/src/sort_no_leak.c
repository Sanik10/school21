#include <stdio.h>
#include <stdlib.h>

int input(int *arr, int size);

void sort(int *arr, int size);

void output(int *arr, int size);

int main() {
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("n/a");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("n/a");
        return 1;
    }

    if (input(arr, n) != 0) {
        printf("n/a");
        free(arr);
        return 1;
    }

    sort(arr, n);

    output(arr, n);

    free(arr);

    return 0;
}

int input(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            return 1;
        }
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
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
}