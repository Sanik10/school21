#include <stdio.h>

int is_prime(int n);
int find_largest_prime_divisor(int a);
int subtract_until_zero(int a, int b);

int main() {
    int a;

    if (scanf("%d", &a) != 1) {
        printf("n/a\n");
        return 1;
    }

    if (a == 0) {
        printf("n/a\n");
        return 1;
    }

    printf("%d\n", find_largest_prime_divisor(a));
    return 0;
}

int is_prime(int n) {
    if (n <= 1) return 0;

    for (int i = 2; i * i <= n; i++) {
        int temp = n;
        while (temp >= i) {
            temp = subtract_until_zero(temp, i);
        }
        if (temp == 0) {
            return 0;
        }
    }
    return 1;
}

int subtract_until_zero(int a, int b) {
    while (a >= b) {
        a -= b;
    }
    return a;
}

int find_largest_prime_divisor(int a) {
    int abs_a = a < 0 ? -a : a;
    int largest_prime_divisor = 1;
    int divisor = 2;

    while (divisor <= abs_a) {
        int temp = abs_a;
        while (temp >= divisor) {
            temp = subtract_until_zero(temp, divisor);
        }

        if (temp == 0 && is_prime(divisor)) {
            largest_prime_divisor = divisor;
        }
        divisor++;
    }

    return largest_prime_divisor;
}