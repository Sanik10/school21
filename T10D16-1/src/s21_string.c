#include "s21_string.h"

size_t s21_strlen(const char *str) {
    if (str == NULL) {
        return 0;
    }
    const char *ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }

    return ptr - str;
}

int s21_strcmp(const char *str1, const char *str2) {
    if (str1 == NULL && str2 == NULL) {
        return 0;
    } else if (str1 == NULL) {
        return -1;
    } else if (str2 == NULL) {
        return 1;
    }
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

char *s21_strcpy(char *dst, const char *src) {
    char *temp = dst;
    while (*src != '\0') {
        *temp = *src;
        temp++;
        src++;
    }
    *temp = '\0';
    return dst;
}

char *s21_strcat(char *dst, const char *src) {
    if (src == NULL) {
        return 0;
    }

    if (dst == NULL) {
        return 0;
    }
    char *ptr = dst;
    while (*ptr != '\0') {
        ptr++;
    }

    while (*src != '\0') {
        *ptr = *src;
        ptr++;
        src++;
    }

    *ptr = '\0';

    return dst;
}

char *s21_strchr(const char *str, int ch) {
    if (str == NULL) {
        return 0;
    }

    char c = (char)ch;
    while (*str) {
        if (*str == c) {
            return (char *)str;
        }
        str++;
    }
    return (c == '\0') ? (char *)str : NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
    if (haystack == NULL) {
        return 0;
    }

    if (needle == NULL) {
        return 0;
    }
    if (*needle == '\0') {
        return (char *)haystack;
    }

    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;
        while (*n != '\0' && *h == *n) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char *)haystack;
        }

        haystack++;
    }
    return NULL;
}

char *s21_strtok(char *str, const char *delim) {
    if (str == NULL) {
        return str;
    }

    if (delim == NULL) {
        return 0;
    }

    static char *last;

    while (*str != '\0' && s21_strchr(delim, *str) != NULL) {
        str++;
    }

    if (*str == '\0') {
        last++;
        return NULL;
    }

    char *token = str;

    while (*str != '\0' && s21_strchr(delim, *str) == NULL) {
        str++;
    }

    if (*str != '\0') {
        *str++ = '\0';
        last = str;
    } else {
        last = NULL;
    }

    return token;
}