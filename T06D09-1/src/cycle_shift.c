#include <stdio.h>

#define MAX_ARRAY_SIZE 10

void input(int *buffer, int *length, int *shift);
void output(int *buffer, int length);
void cycle_shift(int *buffer, int length, int shift);

int main() {
    int length;
    int buffer[MAX_ARRAY_SIZE];
    int shift;

    input(buffer, &length, &shift);

    if (length == 0) {
        printf("n/a\n");
        return 1;
    }

    cycle_shift(buffer, length, shift);
    output(buffer, length);

    return 0;
}

void input(int *buffer, int *length, int *shift) {
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
    if (scanf("%d", shift) != 1) {
        *length = 0;
        while (getchar() != '\n')
            ;
    }
}

void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

void cycle_shift(int *buffer, int length, int shift) {
    int temp[MAX_ARRAY_SIZE];
    int normalized_shift = (shift % length + length) % length;

    for (int i = 0; i < length; i++) {
        temp[i] = buffer[(i + normalized_shift) % length];
    }

    for (int i = 0; i < length; i++) {
        buffer[i] = temp[i];
    }
}