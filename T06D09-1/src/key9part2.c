#include <stdio.h>

#define LEN 100

int input(int *a, int *b, int *len1, int *len2);
void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
int compare(int *buff1, int len1, int *buff2, int len2);

int main() {
    int len1 = 0, len2 = 0;
    int buff1[LEN], buff2[LEN], result[LEN + 1];
    int result_length;

    if (input(buff1, buff2, &len1, &len2) != 0) {
        printf("n/a\n");
        return 1;
    }

    sum(buff1, len1, buff2, len2, result, &result_length);
    int start = 0;
    while (start < result_length && result[start] == 0) {
        start++;
    }
    if (start == result_length) {
        printf("0");
    } else {
        for (int i = start; i < result_length; i++) {
            printf("%d", result[i]);
        }
    }
    printf("\n");

    if (compare(buff1, len1, buff2, len2) >= 0) {
        sub(buff1, len1, buff2, len2, result, &result_length);
        start = 0;
        while (start < result_length && result[start] == 0) {
            start++;
        }
        if (start == result_length) {
            printf("0");
        } else {
            for (int i = start; i < result_length; i++) {
                printf("%d", result[i]);
            }
            printf("\n");
        }
    } else {
        printf("n/a\n");
    }

    return 0;
}

int input(int *a, int *b, int *len1, int *len2) {
    char c, trash;
    int i = 0;

    while (1) {
        int result = scanf("%c%c", &c, &trash);
        if (result != 2) {
            return 1;
        }
        if (trash != ' ' && trash != '\n' && trash != EOF) {
            return 1;
        }
        if (c >= '0' && c <= '9') {
            if (i < LEN) {
                a[i++] = c - '0';
            } else {
                return 1;
            }
        } else if (c != ' ') {
            return 1;
        }
        if (trash == '\n' || trash == EOF) {
            break;
        }
    }
    *len1 = i;

    i = 0;
    while (1) {
        int result = scanf("%c%c", &c, &trash);
        if (result != 2) {
            return 1;
        }
        if (trash != ' ' && trash != '\n' && trash != EOF) {
            return 1;
        }
        if (c >= '0' && c <= '9') {
            if (i < LEN) {
                b[i++] = c - '0';
            } else {
                return 1;
            }
        } else if (c != ' ') {
            return 1;
        }
        if (trash == '\n' || trash == EOF) {
            break;
        }
    }
    *len2 = i;

    if (*len1 == 0 || *len2 == 0) {
        return 1;
    }

    return 0;
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int carry = 0;
    int i = len1 - 1, j = len2 - 1, k = LEN;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) {
            sum += buff1[i];
            i--;
        }
        if (j >= 0) {
            sum += buff2[j];
            j--;
        }

        result[k] = sum % 10;
        carry = sum / 10;
        k--;
    }

    *result_length = LEN - k;
    for (int i = 0; i < *result_length; i++) {
        result[i] = result[i + k + 1];
    }
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int borrow = 0;
    int i = len1 - 1, j = len2 - 1, k = LEN;

    while (i >= 0) {
        int diff = buff1[i] - borrow;
        if (j >= 0) {
            diff -= buff2[j];
            j--;
        }

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[k] = diff;
        i--;
        k--;
    }

    *result_length = LEN - k;

    while (*result_length > 1 && result[LEN - *result_length + 1] == 0) {
        (*result_length)--;
    }

    for (int i = 0; i < *result_length; i++) {
        result[i] = result[i + LEN - *result_length + 1];
    }
}

int compare(int *buff1, int len1, int *buff2, int len2) {
    if (len1 > len2) {
        return 1;
    } else if (len1 < len2) {
        return -1;
    } else {
        for (int i = 0; i < len1; i++) {
            if (buff1[i] > buff2[i]) {
                return 1;
            } else if (buff1[i] < buff2[i]) {
                return -1;
            }
        }
        return 0;
    }
}