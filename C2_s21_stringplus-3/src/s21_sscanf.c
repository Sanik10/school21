#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int count = 0;
  int countB = 0;
  int flags = 1;
  SscanfSpecifier specif = {0};
  char *current_str = (char *)str;
  char *current_format = (char *)format;
  va_list var_params;
  va_start(var_params, format);
  while (*current_format) {
    if (*current_format == '%') {
      flags = 1;
      current_format++;
      int specificator_length =
          parse_specificator_from_format(&specif, current_format, countB);
      if (specificator_length == -1) break;
      current_format += specificator_length;
      int step = countB;
      count = value_to_string(&specif, var_params, current_str, &countB, count);
      current_str += countB - step;
    } else {
      if ((is_white_space(*current_format) ||
           *current_format == *current_str) &&
          flags) {
        if (*current_format == *current_str) {
          current_str++;
          countB++;
        }
      } else {
        flags = 0;
      }
      current_format++;
    }
  }
  va_end(var_params);
  return count;
}

int value_to_string(SscanfSpecifier *sp, va_list ptr, const char *str,
                    int *countB, int count) {
  int size = 0;
  sp->count = count;
  while (is_white_space(*str) && sp->spec != 'c') {
    str++;
    (*countB)++;
  }
  if (*str == '\0' && sp->spec != 'n' && sp->spec != '%') {
    sp->err = -1;
  } else {
    if (sp->setWidth && !sp->width) {
      sp->width = 1;
    }
    size = get_value_s((char *)str, sp);
    if ('p' == sp->spec && !size) {
      sp->spec = '%';
    }
  }
  if (sp->err) {
    if (-1 == sp->err) {
      if (!count) {
        count = -1;
      }
    }
  } else {
    str += size;
    *countB += size;
    if ('s' != sp->spec || size) {
      set_value(ptr, sp);
    }
    if (!sp->err) {
      count = sp->count;
    } else {
      count = -1;
    }
  }
  return count;
}

int is_white_space(char c) {
  char spase[7] = {9, 10, 11, 12, 13, 32, 0};
  return search_first_char(spase, c) ? 1 : 0;
}

char *search_first_char(const char *str, int c) {
  char *res = NULL;
  int size = (int)s21_strlen(str);
  if (0 <= c && 127 >= c) {
    for (int i = 0; i < size; i++) {
      if (str[i] == c) {
        res = (char *)str + i;
        break;
      }
    }
  }
  return res;
}

int fill_struct_sp(char *crop_format, SscanfSpecifier *sp) {
  int err = 0;
  char *modif = "hlL";
  char *spec = "cdieEfgGosuxXpn%";
  SscanfSpecifier qwer = {0};
  *sp = qwer;
  while (*crop_format != '\0' && !err) {
    if (*crop_format == '*') {
      sp->pod = '*';
      crop_format++;
    } else if (*crop_format >= '0' && *crop_format <= '9') {
      crop_format += parse_to_int_s(crop_format, &(sp->width));
      sp->setWidth = 1;
    }
    while (search_first_char(modif, *crop_format) && !err) {
      if (sp->mod == '\0') {
        sp->mod = *crop_format;
        sp->countMod = 1;
        crop_format++;
      } else if (sp->mod == *crop_format && sp->countMod < 2) {
        sp->countMod = 2;
        crop_format++;
      } else {
        err = 1;
      }
    }
    if (!sp->spec) {
      if (search_first_char(spec, *crop_format) && !err) {
        sp->spec = *crop_format;
        crop_format++;
      }
    } else {
      err = 1;
    }
  }
  return err;
}

int parse_specificator_from_format(SscanfSpecifier *specif, const char *format,
                                   int countB) {
  char *spec = "cdieEfgGosuxXpn%";
  int crop_format_length =
      (long long int)s21_strpbrk(format, spec) - (long long int)format + 1;
  char *crop_format = (char *)calloc(crop_format_length + 1, sizeof(char));
  s21_strncpy(crop_format, format, crop_format_length);
  fill_struct_sp(crop_format, specif);
  specif->countB = countB;
  specif->next = *(format + crop_format_length);
  free(crop_format);
  if (specif->err) {
    crop_format_length = -1;
  }

  return crop_format_length;
}

int str_to_str(char *str, SscanfSpecifier *sp) {
  s21_size_t counter = 0;
  s21_size_t size = 0;
  if (is_white_space(*str)) {
    str++;
    counter++;
  }
  s21_size_t len = strlen_mod(str);
  size = sp->setWidth ? (unsigned long)sp->width : len;
  char *string = calloc(size + 1, sizeof(char));
  char spase[7] = {9, 10, 11, 12, 13, 32, 0};
  if (len) {
    for (s21_size_t i = 0; i < size && *str && !s21_strchr(spase, *str); ++i) {
      string[i] = *(str);
      str++;
      counter++;
    }
  }
  sp->val.p = string;
  return counter < size ? counter : size;
}

int str_to_char(const char *str, SscanfSpecifier *sp) {
  s21_size_t len = s21_strlen(str);
  s21_size_t value_size =
      sp->setWidth ? (sp->width < (int)len ? (s21_size_t)sp->width : len) : 1;
  char *current_value = malloc(value_size * sizeof(char));
  int length_to_next_value = value_size;
  s21_memcpy(current_value, str, value_size);
  if (is_white_space(sp->next)) {
    while (is_white_space(*(str + value_size))) {
      str++;
      length_to_next_value++;
    }
  }
  sp->val.p = current_value;
  return length_to_next_value;
}

int get_value_s(char *str, SscanfSpecifier *sp) {
  int count = 0;
  switch (to_lower_char(sp->spec)) {
    case 'i':
    case 'd':
    case 'u':
    case 'x':
    case 'o':
      count = get_int_idu(str, sp);
      break;
    case 'p':
      count = get_int_idu(str, sp);
      break;
    case 'n':
      sp->val.li = sp->countB;
      break;
    case 'c':
      count = str_to_char(str, sp);
      break;
    case 's':
      count = str_to_str(str, sp);
      break;
    case '%':
      if ('%' == *str) {
        count = 1;
      } else {
        sp->err = 1;
      }
      break;
    case 'f':
    case 'e':
    case 'g':;
      count = switch_feg(str, sp);
      break;
  }
  return count;
}

char to_lower_char(char c) { return (64 < c && 91 > c) ? c + 32 : c; }

void set_value(va_list ptr, SscanfSpecifier *sp) {
  if ('*' != sp->pod) {
    void *pointer = s21_NULL;
    if ('p' != sp->spec && '%' != sp->spec) {
      pointer = va_arg(ptr, void *);
    }
    switch_func(pointer, sp, ptr);
    if ('n' != sp->spec && '%' != sp->spec) {
      sp->count += 1;
    }
  }
  if ('c' == sp->spec || 's' == sp->spec) {
    free(sp->val.p);
  }
}

// defines the strlen_mod function, which calculates the length of the string s,
// excluding spaces and line breaks
s21_size_t strlen_mod(char *s) {
  s21_size_t len = 0;
  while (*s != 0 && is_white_space(*s) == 0) {
    s++;
    len++;
  }
  return len;
}

// Assigning a parameter depending on the specifier
int switch_func(void *pointer, SscanfSpecifier *sp, va_list ptr) {
  switch (to_lower_char(sp->spec)) {
    case 'd':
    case 'i':
    case 'n':
      mod_din(pointer, sp);
      break;
    case 'u':
    case 'x':
    case 'o':
      mod_uxo(pointer, sp);
      break;
    case 'p':
      *(va_arg(ptr, void **)) = (void *)sp->val.li;
      break;
    case 'f':
    case 'e':
    case 'g':
      if ('l' == sp->mod) {
        *(double *)pointer = (double)sp->val.ld;
      } else if ('L' == sp->mod) {
        *(long double *)pointer = sp->val.ld;
      } else {
        *(float *)pointer = (float)sp->val.ld;
      }
      break;
    case 'c':
      s21_memcpy(pointer, sp->val.p, sp->setWidth ? sp->width : 1);
      break;
    case 's':
      s21_strcpy((char *)pointer, (char *)(sp->val.p));
      break;
  }
  return 0;
}

int switch_feg(char *str, SscanfSpecifier *sp) {
  int count = 0;
  int res = is_nanInf_s(str);
  if (1 == res) {
    if ('-' == *str) {
      sp->val.ld = -NAN;
      count += 4;
    } else if ('+' == *str) {
      sp->val.ld = NAN;
      count += 4;
    } else {
      sp->val.ld = NAN;
      count += 3;
    }
  } else if (2 == res) {
    if ('-' == *str) {
      sp->val.ld = -INFINITY;
      count += 4;
    } else if ('+' == *str) {
      sp->val.ld = INFINITY;
      count += 4;
    } else {
      sp->val.ld = INFINITY;
      count += 3;
    }
  } else {
    count = get_int_feg(str, sp);
  }
  return count;
}

int get_int_idu(char *str, SscanfSpecifier *sp) {
  int count = 0;
  int notion = set_notion(sp);
  char spase[7] = {9, 10, 11, 12, 13, 32, 0};
  while (search_first_char(spase, *str)) {
    str++;
    count++;
  }
  if ('p' == sp->spec && '0' == *str && 'x' == *(str + 1)) {
    str += 2;
    count += 2;
    if (sp->setWidth) {
      sp->width -= 2;
      if (!sp->width) {
        sp->err = 1;
      }
    }
  }
  int mark = 1;
  int step = mark_set(str, &mark, sp);
  count += step;
  str += step;
  char *suc = s21_NULL;
  if ('o' == sp->spec) {
    suc = "01234567";
  } else if ('x' == to_lower_char(sp->spec) || 'i' == sp->spec ||
             'p' == sp->spec) {
    suc = "0123456789abcdefABCDEF";
  } else {
    suc = "0123456789";
  }
  return logicI_du(sp, str, suc, count, mark, notion);
}

int mark_set(char *str, int *mark, SscanfSpecifier *sp) {
  int count = 0;
  if ('+' == *str || '-' == *str) {
    if ('-' == *str) {
      *mark = -1;
    }
    if (sp->setWidth) {
      sp->width--;
      if (!sp->width) {
        sp->err = 1;
      }
    }
    str++;
    count++;
  }
  return count;
}

int set_notion(SscanfSpecifier *sp) {
  int notion = 10;
  if (search_first_char("xXp", sp->spec)) {
    notion = 16;
  }
  if (search_first_char("o", sp->spec)) {
    notion = 8;
  }
  if (search_first_char("i", sp->spec)) {
    notion = 0;
  }
  return notion;
}

int logicI_du(SscanfSpecifier *sp, char *str, char *suc, int count, int mark,
              int notion) {
  long long int result = 0;
  if (!sp->err && search_first_char(suc, *str)) {
    if (sp->setWidth) {
      int size = (int)s21_strspn(str, "0123456789abcdefABCDEF");
      sp->width = sp->width > size ? size : sp->width;
      char *buf = (char *)calloc((sp->width + 1), sizeof(char));
      s21_strncpy(buf, str, sp->width);
      result = strtoll(buf, s21_NULL, notion);
      count += sp->width;
      free(buf);
    } else {
      char *st = str;
      result = strtoll(str, &str, notion);
      count += str - st;
    }
    if (0 > mark && result == INT64_MAX) {
      result *= mark;
      result -= 1;
    } else {
      result *= mark;
    }
    sp->val.li = result;
  } else {
    if ('p' != sp->spec && !sp->err) {
      if ('\0' != *str) {
        sp->err = 1;
      } else {
        sp->err = -1;
      }
    }
  }
  return count;
}

int mod_din(void *pointer, SscanfSpecifier *sp) {
  if (2 == sp->countMod) {
    if ('l' == sp->mod) {
      *(long long *)pointer = (long long)sp->val.li;
    } else if ('h' == sp->mod) {
      *(signed char *)pointer = (signed char)(long int)sp->val.li;
    }
  } else {
    if ('l' == sp->mod) {
      *(long *)pointer = (long)sp->val.li;
    } else if ('h' == sp->mod) {
      *(short *)pointer = (short)(long int)lroundl(sp->val.li);
    } else {
      *(int *)pointer = (int)sp->val.li;
    }
  }
  return 0;
}

int mod_uxo(void *pointer, SscanfSpecifier *sp) {
  if (2 == sp->countMod) {
    if ('l' == sp->mod) {
      *(unsigned long long *)pointer = (unsigned long long)sp->val.li;
    } else if ('h' == sp->mod) {
      *(unsigned char *)pointer = (unsigned char)(long int)(double)sp->val.li;
    }
  } else {
    if ('l' == sp->mod) {
      *(unsigned long *)pointer = (unsigned long)sp->val.li;
    } else if ('h' == sp->mod) {
      *(unsigned short *)pointer = (unsigned short)(long int)(double)sp->val.li;
    } else {
      *(unsigned int *)pointer = (unsigned int)sp->val.li;
    }
  }
  return 0;
}

int parse_to_int_s(char *str, int *val) {
  int count = 0;
  *val = 0;
  while (*str >= '0' && *str <= '9') {
    *val *= 10;
    *val += *str - '0';
    str++;
    count++;
  }

  return count;
}

int get_int_feg(char *str, SscanfSpecifier *sp) {
  long double result = 0;
  int count = 0;
  char spase[7] = {9, 10, 11, 12, 13, 32, 0};
  while (search_first_char(spase, *str)) {
    str++;
    count++;
  }

  int mark = 1;
  int step = mark_set(str, &mark, sp);

  count += step;
  str += step;

  if ('.' == *str && !search_first_char("0123456789", *(str + 1))) {
    sp->err = 1;
  }

  if (!sp->err && search_first_char("0123456789.", *str)) {
    if (sp->setWidth) {
      int size = (int)s21_strspn(str, "0123456789e-+.");
      sp->width = sp->width > size ? size : sp->width;
      char *buf = (char *)calloc((sp->width + 1), sizeof(char));
      s21_strncpy(buf, str, sp->width);
      result = strtold(buf, s21_NULL);
      count += sp->width;
      free(buf);
    } else {
      char *st = str;
      result = strtold(str, &str);
      count += str - st;
    }

    result *= mark;
    sp->val.ld = result;
  } else {
    if (!sp->err) {
      sp->err = 1;
    }
  }
  return count;
}

int is_nanInf_s(const char *str) {
  int result = 0;
  if ('-' == *str || '+' == *str) {
    str++;
  }
  char *buf = s21_to_lower(str);
  if (!s21_strncmp(buf, "nan", 3)) {
    result = 1;
  }
  if (!s21_strncmp(buf, "inf", 3)) {
    result = 2;
  }
  free(buf);
  return result;
}
