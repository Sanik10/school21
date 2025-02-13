#include "s21_grep.h"

int main(int argc, char *argv[]) {
  grep_options flag = {0};
  if (argc > 1) {
    int error = parsing(argc, argv, &flag);
    if (error != 1) {
      regex_t reg;
      int err = regcomp(&reg, flag.pattern, flag.i ? REG_ICASE : 0);
      if (err == 0) {
        for (int i = optind; i < argc; i++) {
          reading_file(reg, argv[i], flag);
        }
        regfree(&reg);
      }
    }
  }
  return 0;
}

int parsing(int argc, char *argv[], grep_options *flag) {
  int fl, err = 0;
  while ((fl = getopt(argc, argv, "e:ivnclhso")) != -1) {
    switch (fl) {
      case 'e':
        flag->e = 1;
        strcpy(flag->pattern, optarg);
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'o':
        flag->o = 1;
        break;
      default:
        err = 1;
        fprintf(stderr, "usage: grep [-flag] [file ...]\n");
        break;
    }
  }
  if (strlen(flag->pattern) == 0) {
    strcpy(flag->pattern, argv[optind++]);
  }
  if (argc - optind == 1) flag->h = 1;
  if (flag->v) flag->o = 0;
  return err;
}

void reading_file(regex_t reg, char *file, grep_options flag) {
  FILE *f = fopen(file, "r");
  if (!f) {
    if (!flag.s) fprintf(stderr, "%s: No such file or directory\n", file);
  } else {
    char line[4096];
    int number = 1, found = 0;
    while (fgets(line, sizeof(line), f) != NULL) {
      finding_matches(reg, line, flag, &number, &found, file);
      number++;
    }
    c_flag(flag, found, file);
    if (found > 0) l_flag(flag, file);
    fclose(f);
  }
}

void finding_matches(regex_t reg, char *line, grep_options flag, int *number,
                     int *found, char *file) {
  int result = regexec(&reg, line, 0, NULL, 0);
  if (flag.v) result = !result;
  if (result == 0) {
    (*found)++;
    if (!flag.c && !flag.l) {
      if (flag.o)
        print_matches(line, reg, flag, *number, file);
      else {
        checking_h(flag, file);
        checking_n(flag, *number);
        output(line);
      }
    }
  }
}

void checking_h(grep_options flag, char *file) {
  if (!flag.h) printf("%s:", file);
}

void checking_n(grep_options flag, int number) {
  if (flag.n) printf("%d:", number);
}

void c_flag(grep_options flag, int found, char *file) {
  if (flag.c) {
    checking_h(flag, file);
    if (flag.l && found > 0) found = 1;
    printf("%d\n", found);
  }
}

void l_flag(grep_options flag, char *file) {
  if (flag.l) printf("%s\n", file);
}

void print_matches(char *line, regex_t reg, grep_options flag, int number,
                   char *file) {
  regmatch_t matches;
  char *now = line;
  while (regexec(&reg, now, 1, &matches, 0) == 0) {
    int start = matches.rm_so;
    int end = matches.rm_eo;
    checking_h(flag, file);
    checking_n(flag, number);
    printf("%.*s\n", end - start, now + start);
    now += end;
  }
}

void output(char *line) {
  int n = (int)strlen(line);
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}
