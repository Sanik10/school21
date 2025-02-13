#ifndef S21_STRING_H
#define S21_STRING_H

#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_NULL ((void *)0)
typedef long unsigned s21_size_t;

// string
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_memmove(void *dest, const void *src, size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
int s21_strcmp(const char *s1, const char *s2);
void s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strspn(const char *str1, const char *str2);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *c);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

// sprintf
#if defined(__APPLE__)
#define STR_NULL "(null)"
#endif
#if defined(__linux__)
#define STR_NULL "(nil)"
#endif

typedef struct flags {
  int min;
  int pl;
  int spase;
  int grid;
  int zero;
} Flags;

typedef struct specif {
  char spec;
  char mod;
  int countMod;
  Flags flag;
  int width;
  int precision;
  int prec;
  char pod;
  int count;
} Specif;

int s21_sprintf(char *str, const char *format, ...);

int get_spec(const char *format, Specif *sp, va_list ptr);
int choice_format_case(char *buf, Specif sp);
char to_lower_p(char c);
int spec_p(char *str, Specif *sp, va_list ptr);
int spec_fe(char *str, Specif *sp, va_list ptr);
int spec_g(char *str, Specif *sp, va_list ptr);
void format_for_help(char *str, Specif sp);
int precis_width(char *str, Specif *sp, va_list ptr);
long double for_round(Specif sp, char *str, long double a, int *man);

s21_size_t string_wch_cpy(char *str, char c);
int string_to_string(Specif sp, char *str, va_list ptr);
int char_to_string(Specif sp, char *str, va_list ptr);

int get_char(Specif sp, char *str, char c);
int get_w_char(Specif sp, char *str, wchar_t c);

int string_w_cpy(char *str, wchar_t *buf, Specif sp);
int string_cpy(char *str, char *buf, Specif sp);
int format_w_char_string(Specif sp, char *str, wchar_t *buf);
int format_char_string(Specif sp, char *str, char *buf);

int string_duble(Specif sp, char *str, long double a);
int get_number(char *str, __int128_t a, int notation);
int get_number_u(char *str, long long unsigned a, int notation);

long double get_value_mod_doub(Specif sp, va_list ptr);
long long get_value_mod_int(Specif sp, va_list ptr);
long long unsigned get_value_mod_u_int(Specif sp, va_list ptr);

int format_for_input_int_fi(char *str, Specif sp);
int format_for_input_int(Specif sp, char *str);
int filling_in_width_buffer(Specif sp, char *buf, int n);
int insert_my(char *str, int c, s21_size_t n);

int get_value(char *str, Specif *sp, va_list ptr);
int init_parametr(char *str, Specif *sp, va_list ptr);
int parse_to_int(char *str, int *val);

long double create_round(Specif sp, char *str, long double a, int *man);
int double_to_string_g(char *str, long double a, Specif *sp);
int double_to_string(char *str, long double a, Specif sp);
int signed_to_string(char *str, __int128_t a, Specif sp);
int unsigned_to_string(char *str, long long unsigned a, Specif sp);

// sscanf
typedef union {
  long double ld;
  long long int li;
  void *p;
} UnionVal;

typedef struct SscanfSpecifier {
  char spec;
  char mod;
  int width;
  int setWidth;
  int countMod;
  char pod;
  int count;
  UnionVal val;
  int err;
  char next;
  int countB;
} SscanfSpecifier;

int s21_sscanf(const char *str, const char *format, ...);
int value_to_string(SscanfSpecifier *sp, va_list ptr, const char *str,
                    int *countB, int count);
int is_white_space(char c);
int parse_specificator_from_format(SscanfSpecifier *specif, const char *format,
                                   int countB);
int str_to_str(char *str, SscanfSpecifier *sp);
s21_size_t strlen_mod(char *s);
int str_to_char(const char *str, SscanfSpecifier *sp);
int get_value_s(char *str, SscanfSpecifier *sp);

char to_lower_char(char c);

void set_value(va_list ptr, SscanfSpecifier *sp);
s21_size_t strlen_mod(char *s);
int is_white_space(char c);
void set_value(va_list ptr, SscanfSpecifier *sp);
int switch_func(void *pointer, SscanfSpecifier *sp, va_list ptr);
char *search_first_char(const char *str, int c);
int logicI_du(SscanfSpecifier *sp, char *str, char *suc, int count, int mark,
              int notion);
int mark_set(char *str, int *mark, SscanfSpecifier *sp);
int get_int_idu(char *str, SscanfSpecifier *sp);
int set_notion(SscanfSpecifier *sp);
int mod_din(void *pointer, SscanfSpecifier *sp);
int fill_struct_sp(char *crop_format, SscanfSpecifier *sp);

int parse_to_int_s(char *str, int *val);
int switch_feg(char *str, SscanfSpecifier *sp);
int mod_uxo(void *pointer, SscanfSpecifier *sp);
int get_int_feg(char *str, SscanfSpecifier *sp);
int is_nanInf_s(const char *str);

#endif  // S21_STRING_H
