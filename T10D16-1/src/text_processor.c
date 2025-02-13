#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

void format_text(int width, char *text);

int main(int argc, char *argv[]) {
    if (argc != 3 || s21_strcmp(argv[1], "-w") != 0) {
        printf("n/a\n");
        return 1;
    }

    int width = atoi(argv[2]);
    if (width <= 0) {
        printf("n/a\n");
        return 1;
    }

    char text[101];
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("n/a\n");
        return 1;
    }

    format_text(width, text);
    return 0;
}

void format_text(int width, char *text) {
    int len = s21_strlen(text);
    int start = 0;

    while (start < len) {
        int end = start + width;
        if (end >= len) {
            end = len;
        } else {
            while (end > start && text[end] != ' ') {
                end--;
            }
            if (end == start) {
                end = start + width;
            }
        }

        while (text[start] == ' ') {
            start++;
        }

        for (int i = start; i < end; i++) {
            printf("%c", text[i]);
        }

        if (end < len) {
            printf("\n");
        }

        start = end;
    }
}