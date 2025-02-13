#include <stdio.h>

#define MAX_ARRAY_SIZE 10

void input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

int main() {
    int length;
    int buffer[MAX_ARRAY_SIZE];
    int numbers[MAX_ARRAY_SIZE];
    int count = 0;

    input(buffer, &length);

    if (length == 0) {
        printf("n/a\n");
        return 1;
    }

    int sum = sum_numbers(buffer, length);
    if (sum == 0) {
        printf("n/a\n");
        return 1;
    }

    count = find_numbers(buffer, length, sum, numbers);

    if (count == 0) {
        printf("n/a\n");
    } else {
        printf("%d\n", sum);
        output(numbers, count);
    }

    return 0;
}

void input(int *buffer, int *length) {
    if (scanf("%d", length) != 1 || *length <= 0 || *length > MAX_ARRAY_SIZE) {
        *length = 0;
        while (getchar() != '\n')
            ;
        return;
    }
    for (int i = 0; i < *length; i++) {
        if (scanf("%d", &buffer[i]) != 1) {
            *length = 0;
            while (getchar() != '\n')
                ;
            return;
        }
    }
}

void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

int sum_numbers(int *buffer, int length) {
    int sum = 0;
    int has_even = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0 && buffer[i] != 0) {
            sum += buffer[i];
            has_even = 1;
        }
    }
    return has_even ? sum : 0;
}

int find_numbers(int *buffer, int length, int number, int *numbers) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[count] = buffer[i];
            count++;
        }
    }
    return count;
}