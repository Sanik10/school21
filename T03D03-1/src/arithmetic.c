#include <stdio.h>

int sum(int a, int b);
int diff(int a, int b);
int mul(int a, int b);
int div(int a, int b);

int main() {
    int num1, num2;

    if (scanf("%d %d", &num1, &num2) != 2) {
        printf("n/a\n");
        return 1;
    }

    printf("%d %d %d", sum(num1, num2), diff(num1, num2), mul(num1, num2));

    if (num2 != 0) {
        printf(" %d\n", div(num1, num2));
    } else {
        printf(" n/a\n");
    }

    return 0;
}

int sum(int a, int b) { return a + b; }

int diff(int a, int b) { return a - b; }

int mul(int a, int b) { return a * b; }

int div(int a, int b) { return a / b; }