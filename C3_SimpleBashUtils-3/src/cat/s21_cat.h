#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} cat_options;

int parsing(int argc, char *argv[], cat_options *flag);
void reading_file(const char *file, cat_options flag);
void processing(int c, cat_options flag, char *prev, int *empty, int *number);
char flag_v(int c);

#endif