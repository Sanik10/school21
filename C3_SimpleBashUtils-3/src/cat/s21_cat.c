#include "s21_cat.h"

#include <getopt.h>
#include <string.h>

int main(int argc, char *argv[]) {
  cat_options flag = {0};
  if (parsing(argc, argv, &flag) == 0) {
    for (int i = optind; i < argc; i++) {
      reading_file(argv[i], flag);
    }
  }
  return 0;
}

int parsing(int argc, char *argv[], cat_options *flag) {
  int fl, err = 0;
  struct option longopts[] = {{"number-nonblank", 0, NULL, 'b'},
                              {"number", 0, NULL, 'n'},
                              {"squeeze-blank", 0, NULL, 's'},
                              {0, 0, 0, 0}};
  while ((fl = getopt_long(argc, argv, "beEnsTtv", longopts, 0)) != -1) {
    switch (fl) {
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      default:
        err = 1;
        fprintf(stderr, "usage: cat [-beEnsTtv] [file ...]\n");
    }
  }
  return err;
}

void reading_file(const char *file, cat_options flag) {
  FILE *f = fopen(file, "r");
  if (!f) {
    fprintf(stderr, "cat: %s: No such file or directory\n", file);
  } else {
    int c = fgetc(f);
    char last_c = '\n';
    int number = 0, empty = 0;
    while (c != EOF) {
      processing(c, flag, &last_c, &empty, &number);
      c = fgetc(f);
    }
    fclose(f);
  }
}

void processing(int c, cat_options flag, char *last, int *empty, int *number) {
  if (!(flag.s == 1 && *last == '\n' && c == '\n' && *empty == 1)) {
    *empty = (*last == '\n' && c == '\n');
    if (*last == '\n' && (flag.n || (flag.b && c != '\n'))) {
      printf("%6d\t", ++(*number));
    }
    if (flag.e && c == '\n') putchar('$');
    if (flag.t && c == '\t') {
      putchar('^');
      c = '\t' + 64;
    }
    if (flag.v) c = flag_v(c);
    putchar(c);
  }
  *last = c;
}

char flag_v(int c) {
  if (c <= 31 && c != '\n' && c != '\t') {
    putchar('^');
    c += 64;
  } else if (c == 127) {
    putchar('^');
    c = '?';
  } else if (c > 127 && c < 160) {
    printf("M-^");
    c -= 64;
  }
  return c;
}