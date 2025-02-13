#include <stdio.h>

#define ARRAY_SIZE 10

int input(int *arr, int size);
void quickSort(int *arr, int low, int high);
void mergeSort(int *arr, int n);
void merge(int *arr1, int n1, int *arr2, int n2, int *result);
void output(int *arr, int size);

int main() {
    int inputArray[ARRAY_SIZE];
    int mergedArray[ARRAY_SIZE];

    if (input(inputArray, ARRAY_SIZE) != 0) {
        printf("n/a\n");
        return 1;
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        mergedArray[i] = inputArray[i];
    }

    quickSort(inputArray, 0, ARRAY_SIZE - 1);
    output(inputArray, ARRAY_SIZE);

    mergeSort(mergedArray, ARRAY_SIZE);
    output(mergedArray, ARRAY_SIZE);

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

void quickSort(int *arr, int first, int last) {
    if (first < last) {
        int left = first, right = last, middle = arr[(left + right) / 2];
        do {
            while (arr[left] < middle) left++;
            while (arr[right] > middle) right--;
            if (left <= right) {
                int tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        quickSort(arr, first, right);
        quickSort(arr, left, last);
    }
}

void mergeSort(int *arr, int n) {
    if (n <= 1) return;

    int mid = n / 2;
    mergeSort(arr, mid);
    mergeSort(arr + mid, n - mid);
    int temp[n];
    merge(arr, mid, arr + mid, n - mid, temp);
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}

void merge(int *arr1, int n1, int *arr2, int n2, int *result) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    while (i < n1) result[k++] = arr1[i++];
    while (j < n2) result[k++] = arr2[j++];
}

void output(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}