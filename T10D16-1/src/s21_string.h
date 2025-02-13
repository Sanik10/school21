#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdlib.h>

size_t s21_strlen(const char *);
int s21_strcmp(const char *, const char *);
char *s21_strcpy(char *restrict, const char *restrict);
char *s21_strcat(char *restrict, const char *restrict);
char *s21_strchr(const char *, int);
char *s21_strstr(const char *, const char *);
char *s21_strtok (char *, const char *);

#endif