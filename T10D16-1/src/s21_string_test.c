#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

void s21_strlen_test(char *str, size_t expected);
void s21_strcmp_test(char *str1, char *str2, int expected);
void s21_strcpy_test(char *str1, char *expected);
void s21_strcat_test(char *str1, char *str2, char *expected);
void s21_strchr_test(char *str, int chr, int expected);
void s21_strstr_test(const char *str, const char *substr, int expected);
void s21_strtok_test(const char *str, const char *delim, const char *expected);

int main() {
#ifdef STRELEN_TESTS
    s21_strlen_test("Whats up, doc!", 14);
    s21_strlen_test("", 0);
    s21_strlen_test(
        "qwertyuiopasdfghjklzxcvbnm,qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm,"
        "qwertyuiopasdfghjklzx",
        101);
    s21_strlen_test(NULL, 0);
    s21_strlen_test("A", 1);
#endif

#ifdef STRCMP_TESTS
    s21_strcmp_test("Whats up, doc!", "Whats up, doc!", 0);
    s21_strcmp_test("", "", 0);
    s21_strcmp_test("Passwore", "Password", 'e' - 'd');
    s21_strcmp_test("Hello", "hello", 'H' - 'h');
    s21_strcmp_test(NULL, "Hello", -1);
    s21_strcmp_test("Hello", NULL, 1);
    s21_strcmp_test(NULL, NULL, 0);
#endif

#ifdef STRCPY_TESTS
    s21_strcpy_test("Whats_up_doc!", "Whats_up_doc!");
    s21_strcpy_test("Whats up, doc!", "Whats up, doc!");
    s21_strcpy_test("", "");
    s21_strcpy_test("Password", "Password");
#endif

#ifdef STRCAT_TESTS
    s21_strcat_test("Whats up,", " doc!", "Whats up, doc!");
    s21_strcat_test("", "", "");
    s21_strcat_test("Hello", NULL, "Hello");
#endif

#ifdef STRCHR_TESTS
    s21_strchr_test("0123456789", '6', 7);
    s21_strchr_test("Whats up, doc!", ',', 9);
    s21_strchr_test("Hello", 'x', -1);  // normal case
    s21_strchr_test(NULL, 'H', -1);     // abnormal
#endif

#ifdef STRSTR_TESTS
    s21_strstr_test("0123456789", "567", 6);
    s21_strstr_test("Whats up, doc!", "up", 7);
    s21_strstr_test("Hello", "world", -1);  // normal case
    s21_strstr_test(NULL, "Hello", -1);     // abnormal
    s21_strstr_test("Hello", NULL, 0);      // abnormal
#endif

#ifdef STRTOK_TESTS
    char str1[] = "Whats up, doc!";
    char str2[] = "Hello mir, manera krutit mir";
    s21_strtok_test(str1, ",", "Whats up");
    s21_strtok_test(str2, " ", "Hello");
#endif

#ifdef TEXT_PROCESSOR

#endif

    return 0;
}

void s21_strlen_test(char *str, size_t expected) {
    size_t result = s21_strlen(str);
    printf("Input: '%s', Expected: %zu, Got: %zu, ", str ? str : "(null)", expected, result);
    if (expected == result) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strcmp_test(char *str1, char *str2, int expected) {
    int result = s21_strcmp(str1, str2);
    printf("Input 1: '%s', Input 2: '%s', Expected: %d, Got: %d, ", str1 ? str1 : "(null)",
           str2 ? str2 : "(null)", expected, result);
    if (expected == result) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strcpy_test(char *str1, char *expected) {
    char destination[100];
    char *result = s21_strcpy(destination, str1);
    printf("Input: '%s', Expected: '%s', Got: '%s', ", str1 ? str1 : "(null)", expected ? expected : "(null)",
           result ? result : "(null)");
    if ((str1 == NULL && result == NULL) || (str1 != NULL && s21_strcmp(result, expected) == 0)) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strcat_test(char *str1, char *str2, char *expected) {
    if (str1 == NULL && str2 == NULL) {
        printf("Input 1: '(null)', Input 2: '(null)', Expected: '(null)', Got: '(null)', SUCCESS\n");
        return;
    }

    size_t length1 = s21_strlen(str1);
    size_t length2 = s21_strlen(str2);
    size_t buff_length = length1 + length2 + 1;

    char *result = (char *)malloc(buff_length);
    if (result == NULL) {
        perror("malloc failed");
        return;
    }

    s21_strcpy(result, str1);
    s21_strcat(result, str2);
    printf("Input 1: '%s', Input 2: '%s', Expected: '%s', Got: '%s', ", str1 ? str1 : "(null)",
           str2 ? str2 : "(null)", expected ? expected : "(null)", result ? result : "(null)");
    if (s21_strcmp(result, expected) == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    free(result);
}

void s21_strchr_test(char *str, int chr, int expected) {
    char *result = s21_strchr(str, chr);
    int got = result ? result - str + 1 : -1;
    printf("Input: '%s', Character: '%c', Expected: %d, Got: %d, ", str ? str : "(null)", chr, expected, got);
    if (got == expected) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strstr_test(const char *str, const char *substr, int expected) {
    char *result = s21_strstr(str, substr);
    int got = result ? result - str + 1 : -1;
    printf("Input: '%s', Substring: '%s', Expected: %d, Got: %d, ", str ? str : "(null)",
           substr ? substr : "(null)", expected, got);
    if (got == expected) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strtok_test(const char *str, const char *delim, const char *expected) {
    char *str_copy = (char *)malloc(s21_strlen(str) + 1);
    s21_strcpy(str_copy, str);
    if (str_copy == NULL) {
        perror("strdup failed");
        return;
    }

    char *result = s21_strtok(str_copy, delim);
    printf("Input: '%s', Delim: '%s', Expected: '%s', ", str ? str : "(null)", delim,
           expected ? expected : "(null)");

    if (s21_strcmp(result, expected) == 0) {
        printf("Got: '%s', SUCCESS\n", result ? result : "(null)");
    } else {
        printf("Got: '%s', FAIL\n", result ? result : "(null)");
    }

    free(str_copy);
}