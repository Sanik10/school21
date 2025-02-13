#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int o;
  char pattern[1000];
} grep_options;

int parsing(int argc, char *argv[], grep_options *flag);
void reading_file(regex_t reg, char *file, grep_options flag);
void finding_matches(regex_t reg, char *line, grep_options flag, int *number,
                     int *found, char *file);
void print_matches(char *line, regex_t reg, grep_options flag, int number,
                   char *file);
void checking_n(grep_options flag, int number);
void checking_h(grep_options flag, char *file);
void c_flag(grep_options flag, int found, char *file);
void l_flag(grep_options flag, char *file);
void output(char *line);

#endif