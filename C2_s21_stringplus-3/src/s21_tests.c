#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_s21_memchr) {
  char *var_1 = "booamhoam\0";
  char *var_2 = "hoambooam\0";
  char *var_3 = "not entry\0";
  char entry_1 = 'm';
  char entry_2 = '0';
  ck_assert_msg(s21_memchr(var_1, entry_1, 4) == memchr(var_1, entry_1, 4),
                "memchr_test_1");
  ck_assert_msg(s21_memchr(var_1, entry_1, 11) == memchr(var_1, entry_1, 11),
                "memchr_test_2");
  ck_assert_msg(s21_memchr(var_2, entry_1, 4) == memchr(var_2, entry_1, 4),
                "memchr_test_3");
  ck_assert_msg(s21_memchr(var_3, entry_1, 10) == memchr(var_3, entry_1, 10),
                "memchr_test_4");
  ck_assert_msg(s21_memchr(var_1, entry_2, 4) == memchr(var_1, entry_2, 4),
                "memchr_test_5");
  ck_assert_msg(s21_memchr(var_1, entry_2, 11) == memchr(var_1, entry_2, 11),
                "memchr_test_6");
  ck_assert_msg(s21_memchr(var_2, entry_2, 4) == memchr(var_2, entry_2, 4),
                "memchr_test_7");
  ck_assert_msg(s21_memchr(var_3, entry_2, 10) == memchr(var_3, entry_2, 10),
                "memchr_test_8");
}
END_TEST

START_TEST(test_s21_memcmp) {
  char *test1 = "Hello world\0";
  char *test3 = "a\n\0";
  char *test4 = " \n\0";
  char *test7 = "\0";
  char *test8 = "Hello\0";

  ck_assert_msg(s21_memcmp(test1, test8, 4) == memcmp(test1, test8, 4),
                "2_memcmp");
  ck_assert_msg(s21_memcmp(test8, test7, 2) == memcmp(test8, test7, 2),
                "3_memcmp");
  ck_assert_msg(s21_memcmp(test8, test7, 3) != memcmp(test1, test8, 2),
                "4_memcmp");
  ck_assert_msg(s21_memcmp(test3, test4, 3) == memcmp(test3, test4, 3),
                "5_memcmp");
  ck_assert_msg(s21_memcmp(test8, test3, 4) == memcmp(test8, test3, 4),
                "6_memcmp");
}
END_TEST

START_TEST(test_s21_memcpy) {
  char var_1[30] = "booamhoam\0";
  char *var_2 = "hoambooam\0";
  char *var_3 = "short";
  char var_4[30] = "\0";
  char *var_5 = "\0";
  char var_1_s21[30] = "booamhoam\0";
  char *var_2_s21 = "hoambooam\0";
  char *var_3_s21 = "short";
  char var_4_s21[30] = "\0";
  char *var_5_s21 = "\0";
  ck_assert_mem_eq(memcpy(var_1, var_2, 10),
                   s21_memcpy(var_1_s21, var_2_s21, 10), 10);
  ck_assert_mem_eq(memcpy(var_1, var_3, 5), s21_memcpy(var_1_s21, var_3_s21, 5),
                   10);
  ck_assert_mem_eq(memcpy(var_4, var_2, 1), s21_memcpy(var_4_s21, var_2_s21, 1),
                   1);
  ck_assert_mem_eq(memcpy(var_1, var_5, 1), s21_memcpy(var_1_s21, var_5_s21, 1),
                   10);
  ck_assert_mem_eq(memcpy(var_4, var_5, 1), s21_memcpy(var_4_s21, var_5_s21, 1),
                   1);
}
END_TEST

START_TEST(test_s21_memset) {
  char arr1[] = "for testing\0";
  char arr2[] = "another testing\0";
  ck_assert_msg(s21_memset(arr1, 72, 2) == memset(arr1, 72, 2),
                "memset_test_1");
  ck_assert_msg(s21_memset(arr2, 46, 9) == memset(arr2, 46, 9),
                "memset_test_2");
}
END_TEST

START_TEST(test_s21_strncat) {
  char var_1[30] = "booamhoam";
  char *var_2 = "hoambooam";
  char *var_3 = "";
  char var_1_s21[30] = "booamhoam";
  char *var_2_s21 = "hoambooam";
  char *var_3_s21 = "";
  ck_assert_str_eq(strncat(var_1, var_2, 10),
                   s21_strncat(var_1_s21, var_2_s21, 10));
  ck_assert_str_eq(strncat(var_1, var_3, 10),
                   s21_strncat(var_1_s21, var_3_s21, 10));
}
END_TEST

START_TEST(test_s21_strchr) {
  ck_assert_str_eq(s21_strchr("normal", 'm'), strchr("normal", 'm'));
  ck_assert_msg(s21_strchr("normal", 'p') == strchr("normal", 'p'),
                "strchr_null_test");
  ck_assert_str_eq(s21_strchr("", '\0'), strchr("", '\0'));
  ck_assert_str_eq(s21_strchr(" \0", ' '), strchr(" \0", ' '));
  ck_assert_str_eq(s21_strchr("testing\t", '\t'), strchr("testing\t", '\t'));
}
END_TEST

START_TEST(test_s21_strncmp) {
  char test1[] = "Hello world\0";
  char test2[] = "Hello world\n\0";
  char test3[] = "a\n\0";
  char test4[] = " \n\0";
  char test5[] = " \0";
  char test6[] = "\n\0";
  char test7[] = "\0";
  s21_size_t s = 6;
  ck_assert_int_eq(s21_strncmp(test1, test2, s), strncmp(test1, test2, s));
  ck_assert_int_ge(s21_strncmp(test1, test3, s), strncmp(test1, test3, s));
  ck_assert_int_le(s21_strncmp(test1, test4, s), strncmp(test1, test4, s));
  ck_assert_int_le(s21_strncmp(test1, test5, s), strncmp(test1, test5, s));
  ck_assert_int_le(s21_strncmp(test1, test6, s), strncmp(test1, test6, s));
  ck_assert_int_le(s21_strncmp(test1, test7, s), strncmp(test1, test7, s));
  ck_assert_int_le(s21_strncmp(test7, test1, s), strncmp(test7, test1, s));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char var_1[30] = "booamhoam\0";
  char *var_2 = "hoambooam\0";
  char *var_3 = "short";
  char var_4[30] = "\0";
  char *var_5 = "\0";
  char var_1_s21[30] = "booamhoam\0";
  char *var_2_s21 = "hoambooam\0";
  char *var_3_s21 = "short";
  char var_4_s21[30] = "\0";
  char *var_5_s21 = "\0";
  ck_assert_str_eq(strncpy(var_1, var_2, 10),
                   s21_strncpy(var_1_s21, var_2_s21, 10));
  ck_assert_str_eq(strncpy(var_1, var_3, 10),
                   s21_strncpy(var_1_s21, var_3_s21, 10));
  ck_assert_str_eq(s21_strncpy(var_1, var_2, 3),
                   s21_strncpy(var_1_s21, var_2_s21, 3));
  ck_assert_str_eq(strncpy(var_1, var_5, 1),
                   s21_strncpy(var_1_s21, var_5_s21, 1));
  ck_assert_str_eq(strncpy(var_4, var_5, 1),
                   s21_strncpy(var_4_s21, var_5_s21, 1));
}
END_TEST

START_TEST(test_s21_strcspn) {
  char *var_1 = "normal\0";
  char *var_2 = " \0";
  char *var_3 = "testing\t";
  ck_assert_msg(s21_strcspn(var_1, "smk") == strcspn(var_1, "smk"),
                "strcspn_test_1");
  ck_assert_msg(s21_strcspn(var_1, "spk") == strcspn(var_1, "spk"),
                "strcspn_test_2");
  ck_assert_msg(s21_strcspn(var_2, "\0") == strcspn(var_2, "\0"),
                "strcspn_test_3");
  ck_assert_msg(s21_strcspn(var_2, " ") == strcspn(var_2, " "),
                "strcspn_test_4");
  ck_assert_msg(s21_strcspn(var_3, "\t") == strcspn(var_3, "\t"),
                "strcspn_test_5");
}
END_TEST

START_TEST(test_s21_strerror) {
  for (int i = 0 - 1; i <= 134 + 1; i++) {
    ck_assert_pstr_eq(strerror(i), s21_strerror(i));
  }
  ck_assert_pstr_eq("Unknown error -2", s21_strerror(-2));
  ck_assert_pstr_eq("Unknown error 136", s21_strerror(136));
  ck_assert_pstr_eq("Success", s21_strerror(0));
}
END_TEST

START_TEST(test_s21_strlen) {
  char *var_1 = "booamhoam\0";
  char *var_2 = "\n";
  char *var_3 = "\0";
  ck_assert_msg(s21_strlen(var_1) == strlen(var_1), "strlen_test_1");
  ck_assert_msg(s21_strlen(var_2) == strlen(var_2), "strlen_test_2");
  ck_assert_msg(s21_strlen(var_3) == strlen(var_3), "strlen_test_3");
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char *var_1 = "normal\0";
  char *var_2 = " \0";
  char *var_3 = "testing\t";
  ck_assert_msg(s21_strpbrk(var_1, "smk") == strpbrk(var_1, "smk"),
                "strpbrk_test_1");
  ck_assert_msg(s21_strpbrk(var_1, "spk") == strpbrk(var_1, "spk"),
                "strpbrk_test_2");
  ck_assert_msg(s21_strpbrk(var_2, "\0") == strpbrk(var_2, "\0"),
                "strpbrk_test_3");
  ck_assert_msg(s21_strpbrk(var_2, " ") == strpbrk(var_2, " "),
                "strpbrk_test_4");
  ck_assert_msg(s21_strpbrk(var_3, "\t") == strpbrk(var_3, "\t"),
                "strpbrk_test_5");
}
END_TEST

START_TEST(test_s21_strstr) {
  char *var_1 = "normal\0";
  char *var_2 = " \0";
  char *var_3 = "testing\t";
  ck_assert_msg(s21_strstr(var_1, "rm") == strstr(var_1, "rm"),
                "strstr_test_1");
  ck_assert_msg(s21_strstr(var_1, "ram") == strstr(var_1, "ram"),
                "strstr_test_2");
  ck_assert_msg(s21_strstr(var_2, "\0") == strstr(var_2, "\0"),
                "strstr_test_3");
  ck_assert_msg(s21_strstr(var_2, " ") == strstr(var_2, " "), "strstr_test_4");
  ck_assert_msg(s21_strstr(var_3, "\t") == strstr(var_3, "\t"),
                "strstr_test_5");
}
END_TEST

START_TEST(test_s21_strrchr) {
  ck_assert_str_eq(s21_strrchr("aboba biba\0", 'b'),
                   strrchr("aboba biba\0", 'b'));
  ck_assert_str_eq(s21_strrchr("a\n\0", '\n'), strrchr("a\n\0", '\n'));
  ck_assert_str_eq(s21_strrchr("aboba biba\n\0", '\0'),
                   strrchr("aboba biba\n\0", '\0'));
  ck_assert_msg(s21_strrchr("", 'e') == strrchr("", 'e'), "strchr_test");
  ck_assert_str_eq(s21_strrchr(" \0", ' '), strrchr(" \0", ' '));
}
END_TEST

START_TEST(test_s21_strtok) {
  char var_1[12] = "bo.o.am.hoam";
  char var_2[12] = "ho..ambooam.";
  char var_3[12] = ".short";
  char var_4[12] = "\0";
  char var_5[12] = "booamhoam";
  char var_6[12] = "hoabooam";
  char var_1_s21[12] = "bo.o.am.hoam";
  char var_2_s21[12] = "ho..ambooam.";
  char var_3_s21[12] = ".short";
  char var_4_s21[12] = "\0";
  char var_5_s21[12] = "booamhoam";
  char var_6_s21[12] = "hoabooam";
  for (int i = 0; i < 5; i++) {
    ck_assert_str_eq(strtok(var_1, "."), s21_strtok(var_1_s21, "."));
  }
  for (int i = 0; i < 5; i++) {
    ck_assert_str_eq(strtok(var_2, "."), s21_strtok(var_2_s21, "."));
  }
  for (int i = 0; i < 5; i++) {
    ck_assert_str_eq(strtok(var_3, "."), s21_strtok(var_3_s21, "."));
  }
  for (int i = 0; i < 5; i++) {
    ck_assert_msg(strtok(var_4, ".") == s21_strtok(var_4_s21, "."),
                  "strtok_null_test");
  }
  for (int i = 0; i < 5; i++) {
    ck_assert_str_eq(strtok(var_5, "am"), s21_strtok(var_5_s21, "am"));
  }
  for (int i = 0; i < 5; i++) {
    ck_assert_str_eq(strtok(var_6, "am"), s21_strtok(var_6_s21, "am"));
  }

  char arr1[100] = "this. is test..just test";
  char *parr1 = arr1;
  char arr2[100] = "this. is test..just test";
  char *parr2 = arr2;
  s21_strtok(parr1, " .");
  strtok(parr2, " .");
  ck_assert_str_eq(parr1, parr2);
  parr1 = s21_strtok(NULL, " .");
  parr2 = strtok(NULL, " .");
  ck_assert_str_eq(parr1, parr2);
  parr1 = s21_strtok(NULL, " .");
  parr2 = strtok(NULL, " .");
  ck_assert_str_eq(parr1, parr2);
}
END_TEST

START_TEST(test_s21_to_lower) {
  char var_1[50] = "b4-*--+z%faSDf&o.o.amHL.hP6o8am.";
  char var_2[50] = "b4-*--+z%fasdf&o.o.amhl.hp6o8am.";
  char *var_3 = s21_to_lower(var_1);
  ck_assert_str_eq(var_3, var_2);
  free(var_3);
}
END_TEST

START_TEST(test_s21_to_upper) {
  char var_1[50] = "b4-*--+z%faSDf&o.o.amHL.hP6o8am.";
  char var_2[50] = "B4-*--+Z%FASDF&O.O.AMHL.HP6O8AM.";
  char *var_3 = s21_to_upper(var_1);
  ck_assert_str_eq(var_3, var_2);
  free(var_3);
}
END_TEST

START_TEST(test_s21_insert) {
  char var_1[30] = "booamhoam";
  char *var_2 = "hoambooam";
  char *var_3 = "short";
  char var_4[30] = "\0";
  char *var_5 = "\0";
  char *result = NULL;

  result = s21_insert(var_1, var_2, 5);
  ck_assert_str_eq("booamhoambooamhoam", result);
  free(result);

  result = s21_insert(var_1, var_3, 0);
  ck_assert_str_eq("shortbooamhoam", result);
  free(result);

  result = s21_insert(var_1, var_2, 9);
  ck_assert_str_eq("booamhoamhoambooam", result);
  free(result);

  result = s21_insert(var_1, var_5, 1);
  ck_assert_str_eq("booamhoam", result);
  free(result);

  result = s21_insert(var_4, var_2, 0);
  ck_assert_str_eq("hoambooam", result);
  free(result);

  result = s21_insert(var_1, var_2, 11);
  ck_assert_ptr_null(result);
  free(result);

  char test1[] = "Hello world\0";
  char test9[] = "aloha\0";
  char *test14 = s21_NULL;
  char test16[] = "HELLO, VERTER!\0";
  int it1 = 6, it2 = 11, it3 = 10, it4 = 12, it5 = -1;

  char *insert_test1 = s21_insert(test16, test9, it1);
  ck_assert_str_eq(insert_test1, "HELLO,aloha VERTER!\0");
  free(insert_test1);

  char *insert_test2 = s21_insert(test1, test9, it2);
  ck_assert_str_eq(insert_test2, "Hello worldaloha\0");
  free(insert_test2);

  char *insert_test3 = s21_insert(test1, test9, it3);
  ck_assert_str_eq(insert_test3, "Hello worlalohad\0");
  free(insert_test3);

  char *insert_test4 = s21_insert(test1, test9, it4);
  ck_assert_ptr_null(insert_test4);
  free(insert_test4);

  char *insert_test5 = s21_insert(test1, test9, it5);
  ck_assert_ptr_null(insert_test5);
  free(insert_test5);

  char *insert_test6 = s21_insert(test14, test9, it2);
  ck_assert_ptr_null(insert_test6);
  free(insert_test6);

  char *insert_test7 = s21_insert(test1, test14, it2);
  ck_assert_ptr_null(insert_test7);
  free(insert_test7);
}
END_TEST

START_TEST(test_s21_trim) {
  char var_1[30] = "*//*-booamhoam=*//*-";
  char var_2[30] = "*****hoambooam****u";
  char *result = NULL;
  result = s21_trim(var_1, "*//-");
  ck_assert_str_eq("booamhoam=", result);
  free(result);
  result = s21_trim(var_2, "*");
  ck_assert_str_eq("hoambooam****u", result);
  free(result);
  result = s21_trim(var_1, "mb");
  ck_assert_str_eq("*//*-booamhoam=*//*-", result);
  free(result);

  char *test14 = s21_NULL;
  char *test15 = "";
  char *test17 = "***ver***ter***\0";
  char *test18 = "ver***ter \0";
  char *test19 = "***verter\0";
  char *test20 = "*******\0";
  char *test22 = "*\0";
  char *test23 = "* \0";
  char *trim_test1 = s21_trim(test17, test22);
  ck_assert_str_eq(trim_test1, "ver***ter\0");
  free(trim_test1);

  char *trim_test2 = s21_trim(test18, test23);
  ck_assert_str_eq(trim_test2, "ver***ter\0");
  free(trim_test2);

  char *trim_test3 = s21_trim(test19, test22);
  ck_assert_str_eq(trim_test3, "verter\0");
  free(trim_test3);

  char *trim_test4 = s21_trim(test20, test22);
  ck_assert_str_eq(trim_test4, "");
  free(trim_test4);

  char *trim_test5 = s21_trim(test15, test22);
  ck_assert_str_eq(trim_test5, "");
  free(trim_test5);

  char *trim_test8 = s21_trim(test14, test22);
  ck_assert_ptr_eq(trim_test8, s21_NULL);
  free(trim_test8);
}
END_TEST

START_TEST(test_sprintf_c) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%5c", 69);
  sprintf(origin, "%5c", 69);

  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  s21_sprintf(copy1, "%lc", 'z');
  sprintf(origin1, "%lc", 'z');

  ck_assert_str_eq(origin1, copy1);
}
END_TEST

START_TEST(test_sprintf_d) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%010d", 1011);
  sprintf(origin, "%010d", 1011);
  ck_assert_str_eq(origin, copy);
  s21_sprintf(copy, "% 26d", 1011);
  sprintf(origin, "% 26d", 1011);
  ck_assert_str_eq(origin, copy);
  s21_sprintf(copy, "%1.0d", 0);
  sprintf(origin, "%1.0d", 0);
  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  long int a = 12123476021384612;

  s21_sprintf(copy1, "%ld", a);
  sprintf(origin1, "%ld", a);
  ck_assert_str_eq(origin1, copy1);

  char copy2[1024];
  char origin2[1024];
  short b = 778;

  s21_sprintf(copy2, "%hd", b);
  sprintf(origin2, "%hd", b);
  ck_assert_str_eq(origin2, copy2);

  char copy4[1024];
  char origin4[1024];
  int t = 2314123;
  s21_sprintf(copy4, "%+d", t);
  sprintf(origin4, "%+d", t);
  ck_assert_str_eq(origin4, copy4);

  char copy5[1024];
  char origin5[1024];
  int s = 2314123;
  s21_sprintf(copy5, "% d", s);
  sprintf(origin5, "% d", s);
  ck_assert_str_eq(origin5, copy5);
}
END_TEST

START_TEST(test_sprintf_i) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%i", 20222321);
  sprintf(origin, "%i", 20222321);
  ck_assert_str_eq(origin, copy);
  s21_sprintf(copy, "%*i", 20, 20222321);
  sprintf(origin, "%*i", 20, 20222321);
  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  long int a = 12123476021384612;

  s21_sprintf(copy1, "%li", a);
  sprintf(origin1, "%li", a);
  ck_assert_str_eq(origin1, copy1);

  char copy4[1024];
  char origin4[1024];
  int t = 2314123;
  s21_sprintf(copy4, "%+i", t);
  sprintf(origin4, "%+i", t);
  ck_assert_str_eq(origin4, copy4);

  char copy5[1024];
  char origin5[1024];
  int s = 2314123;
  s21_sprintf(copy5, "% i", s);
  sprintf(origin5, "% i", s);
  ck_assert_str_eq(origin5, copy5);
}
END_TEST

START_TEST(test_sprintf_f) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%-20.8f", 23.0);
  sprintf(origin, "%-20.8f", 23.0);
  ck_assert_str_eq(origin, copy);
  s21_sprintf(copy, "%15.0f", 23.0);
  sprintf(origin, "%15.0f", 23.0);
  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  long double a = 231412341.1235;
  s21_sprintf(copy1, "%-50.8Lf", a);
  sprintf(origin1, "%-50.8Lf", a);
  ck_assert_str_eq(origin1, copy1);

  char copy3[1024];
  char origin3[1024];
  double c = 2314123;
  s21_sprintf(copy3, "%#f", c);
  sprintf(origin3, "%#f", c);
  ck_assert_str_eq(origin3, copy3);
}
END_TEST

START_TEST(test_sprintf_s) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%s", "this is test");
  sprintf(origin, "%s", "this is test");
  ck_assert_str_eq(origin, copy);
  s21_sprintf(copy, "%22.20s", "this is test");
  sprintf(origin, "%22.20s", "this is test");
  ck_assert_str_eq(origin, copy);
  s21_sprintf(copy, "%22.*s", 5, "this is test");
  sprintf(origin, "%22.*s", 5, "this is test");
  ck_assert_str_eq(origin, copy);
  s21_sprintf(copy, "%5.7s", "this is test");
  sprintf(origin, "%5.7s", "this is test");
  ck_assert_str_eq(origin, copy);
  s21_sprintf(copy, "%-22.5s", "this is test");
  sprintf(origin, "%-22.5s", "this is test");
  ck_assert_str_eq(origin, copy);
  char copy1[1024];
  char origin1[1024];
  s21_sprintf(copy1, "%22ls", L"this is test");

  sprintf(origin1, "%22ls", L"this is test");

  ck_assert_str_eq(origin1, copy1);
}
END_TEST

START_TEST(test_sprintf_o) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%010o", 1234);
  sprintf(origin, "%010o", 1234);
  ck_assert_str_eq(origin, copy);
  s21_sprintf(copy, "%1.0o", 0);
  sprintf(origin, "%1.0o", 0);
  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  long int a = 234314124123412;
  s21_sprintf(copy1, "%lo", a);
  sprintf(origin1, "%lo", a);
  ck_assert_str_eq(origin1, copy1);

  char copy3[1024];
  char origin3[1024];
  unsigned int c = 2314123;
  s21_sprintf(copy3, "%#o", c);
  sprintf(origin3, "%#o", c);
  ck_assert_str_eq(origin3, copy3);
}
END_TEST

START_TEST(test_sprintf_u) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%u", 1234);

  sprintf(origin, "%u", 1234);

  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  unsigned long int a = 241234123412;
  s21_sprintf(copy1, "%lu", a);

  sprintf(origin1, "%lu", a);

  ck_assert_str_eq(origin1, copy1);
}
END_TEST

START_TEST(test_sprintf_x) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%3x", 1234);

  sprintf(origin, "%3x", 1234);

  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  long int a = 12423151245612512;
  s21_sprintf(copy1, "%lx", a);

  sprintf(origin1, "%lx", a);

  ck_assert_str_eq(origin1, copy1);

  char copy3[1024];
  char origin3[1024];
  unsigned int c = 2314123;
  s21_sprintf(copy3, "%#x", c);
  sprintf(origin3, "%#x", c);
  ck_assert_str_eq(origin3, copy3);
}
END_TEST

START_TEST(test_sprintf_X) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%X", 1234);

  sprintf(origin, "%X", 1234);

  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  long int a = 12423151245612512;
  s21_sprintf(copy1, "%lX", a);

  sprintf(origin1, "%lX", a);

  ck_assert_str_eq(origin1, copy1);

  char copy3[1024];
  char origin3[1024];
  unsigned int c = 2314123;
  s21_sprintf(copy3, "%#X", c);
  sprintf(origin3, "%#X", c);
  ck_assert_str_eq(origin3, copy3);
}
END_TEST

START_TEST(test_sprintf_p) {
  char copy[1024];
  char origin[1024];
  int a = 1234;

  s21_sprintf(copy, "%50p", &a);

  sprintf(origin, "%50p", (void *)&a);

  ck_assert_str_eq(origin, copy);
}
END_TEST

START_TEST(test_sprintf_n) {
  char copy[1024] = {0};
  char origin[1024] = {0};
  int a = 1234;

  s21_sprintf(copy, "abc%n", &a);
  sprintf(origin, "abc%n", &a);

  ck_assert_str_eq(origin, copy);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%% %X", 1234);

  sprintf(origin, "%% %X", 1234);

  ck_assert_str_eq(origin, copy);
}
END_TEST

START_TEST(test_sprintf_e) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%25.8e", 1234.1);

  sprintf(origin, "%25.8e", 1234.1);

  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  long double a = 234124123412.14;

  s21_sprintf(copy1, "%Le", a);

  sprintf(origin1, "%Le", a);

  ck_assert_str_eq(origin1, copy1);

  char copy3[1024];
  char origin3[1024];
  double c = 2314123;
  s21_sprintf(copy3, "%#e", c);
  sprintf(origin3, "%#e", c);
  ck_assert_str_eq(origin3, copy3);
}
END_TEST

START_TEST(test_sprintf_E) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%E", 1234.1);

  sprintf(origin, "%E", 1234.1);

  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  s21_sprintf(copy1, "%E", -1234.1);

  sprintf(origin1, "%E", -1234.1);
  ck_assert_str_eq(origin1, copy1);

  char copy2[1024];
  char origin2[1024];
  long double b = 234124123412.14;

  s21_sprintf(copy2, "%LE", b);

  sprintf(origin2, "%LE", b);

  ck_assert_str_eq(origin2, copy2);

  char copy3[1024];
  char origin3[1024];
  double c = 2314123;
  s21_sprintf(copy3, "%#E", c);
  sprintf(origin3, "%#E", c);
  ck_assert_str_eq(origin3, copy3);
}
END_TEST

START_TEST(test_sprintf_g) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%020.2g", 1234.51);

  sprintf(origin, "%020.2g", 1234.51);

  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  s21_sprintf(copy1, "%g", -1234.1123123123);
  sprintf(origin1, "%g", -1234.1123123123);

  ck_assert_str_eq(origin1, copy1);

  char copy2[1024];
  char origin2[1024];
  long double a = 21341234124.134;
  s21_sprintf(copy2, "%Lg", a);
  sprintf(origin2, "%Lg", a);

  ck_assert_str_eq(origin2, copy2);

  char copy3[1024];
  char origin3[1024];
  long double b = 0;
  s21_sprintf(copy3, "%Lg", b);
  sprintf(origin3, "%Lg", b);

  ck_assert_str_eq(origin3, copy3);

  char copy4[1024];
  char origin4[1024];
  double c = 2314123;
  s21_sprintf(copy4, "%#g", c);
  sprintf(origin4, "%#g", c);
  ck_assert_str_eq(origin4, copy4);
}
END_TEST

START_TEST(test_sprintf_G) {
  char copy[1024];
  char origin[1024];
  s21_sprintf(copy, "%8.2G", 12456534.1);

  sprintf(origin, "%8.2G", 12456534.1);

  ck_assert_str_eq(origin, copy);

  char copy1[1024];
  char origin1[1024];
  s21_sprintf(copy1, "%G", -1234.1123123123);

  sprintf(origin1, "%G", -1234.1123123123);

  ck_assert_str_eq(origin1, copy1);

  char copy4[1024];
  char origin4[1024];
  double c = 2314123;
  s21_sprintf(copy4, "%#G", c);
  sprintf(origin4, "%#G", c);
  ck_assert_str_eq(origin4, copy4);
}
END_TEST

START_TEST(test_sscanf_dif) {
  int success1 = 0;
  int success2 = 0;
  char c1 = 'f';
  char c2 = 'f';
  int d1 = 1;
  int d2 = 1;
  float f1 = 2.0;
  float f2 = 2.0;
  char s1[20] = "Waldemar";
  char s2[20] = "Waldemar";
  char *str = "Hello. My name -343.5e-12 is Jimmy Pop and I am 026 years old.";
  success1 =
      s21_sscanf(str, "Hello. %cy name %f is %s Pop and I am %*d years old.",
                 &c1, &f1, s1);
  success2 = sscanf(str, "Hello. %cy name %f is %s Pop and I am %*d years old.",
                    &c2, &f2, s2);
  ck_assert_msg(c1 == c2, "test_sscanf_c_1");
  ck_assert_float_eq_tol(f1, f2, 6);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(success1, success2);
}
END_TEST

START_TEST(test_sscanf_c) {
  char c1 = 'f';
  char c2 = 'f';
  char *str = "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years old.";
  s21_sscanf(str,
             "Hello. My name -343.%ce-2 is Jimmy Pop and I am 026 years old.",
             &c1);
  sscanf(str, "Hello. My name -343.%ce-2 is Jimmy Pop and I am 026 years old.",
         &c2);
  ck_assert_msg(c1 == c2, "test_sscanf_c_1");
  s21_sscanf(str,
             "%cello. My name -343.5e-2 is Jimmy Pop and I am 026 years old.",
             &c1);
  sscanf(str, "%cello. My name -343.5e-2 is Jimmy Pop and I am 026 years old.",
         &c2);
  ck_assert_msg(c1 == c2, "test_sscanf_c_2");
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years old%c",
             &c1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years old%c",
         &c2);
  ck_assert_msg(c1 == c2, "test_sscanf_c_3");
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years old%c",
             &c1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years old%c",
         &c2);
  ck_assert_msg(c1 == c2, "test_sscanf_c_4");
  char c3 = 'f';
  char c4 = 'f';
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years ol%c%c",
             &c1, &c3);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years ol%c%c",
         &c2, &c4);
  ck_assert_msg(c1 == c2 && c3 == c4, "test_sscanf_c_5");
}
END_TEST

START_TEST(test_sscanf_d) {
  int d1 = 2;
  int d2 = 2;
  char *str =
      "Hello. My name -343.5e-2 is Jimmy Pop and I am 2646388764387643 years "
      "old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %d years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %d years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  int d3 = 1;
  int d4 = 1;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2d%2d years old.",
             &d1, &d3);
  sscanf(str,
         "Hello. My name -343.5e-2 is Jimmy Pop and I am %2d%2d years old.",
         &d2, &d4);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
  short sd1 = 2;
  short sd2 = 2;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %hd years old.",
             &sd1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %hd years old.",
         &sd2);
  ck_assert_int_eq(sd1, sd2);
  long ld1 = 2;
  long ld2 = 2;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %ld years old.",
             &ld1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %ld years old.",
         &ld2);
  ck_assert_int_eq(ld1, ld2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2d years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2d years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am -026 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %d years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %d years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2d years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2d years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_i) {
  int d1 = 2;
  int d2 = 2;
  char *str = "Hello. My name -343.5e-2 is Jimmy Pop and I am 26.3 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am 026.3 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  short sd1 = 2;
  short sd2 = 2;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %hi years old.",
             &sd1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %hi years old.",
         &sd2);
  ck_assert_int_eq(sd1, sd2);
  long ld1 = 2;
  long ld2 = 2;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %li years old.",
             &ld1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %li years old.",
         &ld2);
  ck_assert_int_eq(ld1, ld2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2i years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2i years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am -026 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2i years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2i years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am 0x26 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am 0xf26 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am -066 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %i years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  s21_sscanf(str,
             "Hello. My name -343%i5e-2 is Jimmy Pop and I am -066 years old.",
             &d1);
  sscanf(str, "Hello. My name -343%i5e-2 is Jimmy Pop and I am -066 years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  s21_sscanf(str,
             "Hello. My name -343%i5e-2 is Jimmy Pop and I am -%hi6 years old.",
             &d1, &sd1);
  sscanf(str,
         "Hello. My name -343%i5e-2 is Jimmy Pop and I am -%hi6 years old.",
         &d2, &sd2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(sd1, sd2);
  str = "Hello. My name -3430xf5e-2 is Jimmy Pop and I am -066 years old.";
  s21_sscanf(str,
             "Hello. My name -343%i-2 is Jimmy Pop and I am %hi6 years old.",
             &d1, &sd1);
  sscanf(str, "Hello. My name -343%i-2 is Jimmy Pop and I am %hi6 years old.",
         &d2, &sd2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(sd1, sd2);
}
END_TEST

START_TEST(test_sscanf_x) {
  unsigned int d1 = 2;
  unsigned int d2 = 2;
  char *str = "Hello. My name -343.5e-2 is Jimmy Pop and I am 26.3 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %x years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %x years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  unsigned int d3 = 1;
  unsigned int d4 = 1;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2x%2x years old.",
             &d1, &d3);
  sscanf(str,
         "Hello. My name -343.5e-2 is Jimmy Pop and I am %2x%2x years old.",
         &d2, &d4);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
  short unsigned sd1 = 2;
  short unsigned sd2 = 2;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %hx years old.",
             &sd1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %hx years old.",
         &sd2);
  ck_assert_int_eq(sd1, sd2);
  long unsigned ld1 = 2;
  long unsigned ld2 = 2;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %lx years old.",
             &ld1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %lx years old.",
         &ld2);
  ck_assert_int_eq(ld1, ld2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2x years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2x years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am -026 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %x years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %x years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2x years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2x years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str =
      "Hello. My name -343.5e-2 is Jimmy Pop and I am -fffffeeeefffff25 years "
      "old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %X years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %X years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2x years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2x years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am f25 years old.";
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2x years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2x years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  s21_sscanf(str,
             "Hello. My name -343.%hx-2 is Jimmy Pop and I am %x years old.",
             &sd1, &d1);
  sscanf(str, "Hello. My name -343.%hx-2 is Jimmy Pop and I am %x years old.",
         &sd2, &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(sd1, sd2);
  s21_sscanf(str,
             "Hello. My name -343.%*x-2 is Jimmy Pop and I am %x years old.",
             &d1);
  sscanf(str, "Hello. My name -343.%*x-2 is Jimmy Pop and I am %x years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  s21_sscanf(str,
             "Hello. My name -343.%2hx-2 is Jimmy Pop and I am %2x years old.",
             &sd1, &d1);
  sscanf(str, "Hello. My name -343.%2hx-2 is Jimmy Pop and I am %2x years old.",
         &sd2, &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(sd1, sd2);
}
END_TEST

START_TEST(test_sscanf_p) {
  void *p1;
  void *p2;
  char *str = "Hello. My name -343.5e-2 is Jimmy Pop and I am 26.3 years old.";
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %p6.3 years old.",
             &p1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %p6.3 years old.",
         &p2);
  ck_assert_msg(p1 == p2, "test_sscanf_p_1");
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop %pnd I am 26.3 years old.",
             &p1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop %pnd I am 26.3 years old.",
         &p2);
  ck_assert_msg(p1 == p2, "test_sscanf_p_2");
}
END_TEST

START_TEST(test_sscanf_o) {
  unsigned int d1 = 2;
  unsigned int d2 = 2;
  char *str = "Hello. My name -343.5e-2 is Jimmy Pop and I am 26.3 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %o years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %o years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  unsigned int d3 = 1;
  unsigned int d4 = 1;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %3o%3o years old.",
             &d1, &d3);
  sscanf(str,
         "Hello. My name -343.5e-2 is Jimmy Pop and I am %3o%3o years old.",
         &d2, &d4);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(d3, d4);
  short unsigned sd1 = 2;
  short unsigned sd2 = 2;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %ho years old.",
             &sd1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %ho years old.",
         &sd2);
  ck_assert_int_eq(sd1, sd2);
  long unsigned ld1 = 2;
  long unsigned ld2 = 2;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %lo years old.",
             &ld1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %lo years old.",
         &ld2);
  ck_assert_int_eq(ld1, ld2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2o years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2o years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am -026 years old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %o years old.", &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %o years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2o years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2o years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am -725 years old.";
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2o years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2o years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  str = "Hello. My name -343.5e-2 is Jimmy Pop and I am 725 years old.";
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2o years old.",
             &d1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2o years old.",
         &d2);
  ck_assert_int_eq(d1, d2);
  s21_sscanf(str,
             "Hello. My name -%112ho.5e-2 is Jimmy Pop and I am %2o years old.",
             &sd1, &d1);
  sscanf(str,
         "Hello. My name -%112ho.5e-2 is Jimmy Pop and I am %2o years old.",
         &sd2, &d2);
  ck_assert_int_eq(sd1, sd2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_s) {
  char s1[50] = "f";
  char s2[50] = "f";
  char s3[50] = "f";
  char s4[50] = "f";
  char *str = "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years old.";
  s21_sscanf(str, "Hello. My name -343.%s is Jimmy Pop and I am 026 years old.",
             s1);
  sscanf(str, "Hello. My name -343.%s is Jimmy Pop and I am 026 years old.",
         s2);
  ck_assert_str_eq(s1, s2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and %s am 026 years old.",
             s1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and %s am 026 years old.",
         s2);
  ck_assert_str_eq(s1, s2);
  s21_sscanf(str, "%s My name -343.5e-2 is Jimmy Pop and I am 026 years old.",
             s1);
  sscanf(str, "%s My name -343.5e-2 is Jimmy Pop and I am 026 years old.", s2);
  ck_assert_str_eq(s1, s2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years old%s",
             s1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years old%s",
         s2);
  ck_assert_str_eq(s1, s2);
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years o%s", s1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years o%s",
         s2);
  ck_assert_str_eq(s1, s2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years %s%s",
             s1, s3);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am 026 years %s%s",
         s2, s4);
  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
}
END_TEST

START_TEST(test_sscanf_f) {
  float f1 = 2;
  float f2 = 2;
  char *str =
      "Hello. My name -34336767.7434105344142432468475e-2 is Jimmy Pop and I "
      "am 2646388764387643 years old.";
  s21_sscanf(
      str,
      "Hello. My name %f is Jimmy Pop and I am 2646388764387643 years old.",
      &f1);
  sscanf(str,
         "Hello. My name %f is Jimmy Pop and I am 2646388764387643 years old.",
         &f2);
  ck_assert_int_eq(f1, f2);
  float f3 = 1;
  float f4 = 1;
  s21_sscanf(str,
             "Hello. My name -34336767.7434105344142432468475e-2 is Jimmy Pop "
             "and I am %2f%2f years old.",
             &f1, &f3);
  sscanf(str,
         "Hello. My name -34336767.7434105344142432468475e-2 is Jimmy Pop and "
         "I am %2f%2f years old.",
         &f2, &f4);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(f3, f4);
  double lf1 = 2;
  double lf2 = 2;
  str =
      "Hello. My name -34336767.7434105344142432468475e2 is Jimmy Pop and I "
      "am "
      "2646388764387643 years old.";
  s21_sscanf(
      str,
      "Hello. My name -%lf is Jimmy Pop and I am 2646388764387643 years old.",
      &lf1);
  sscanf(
      str,
      "Hello. My name -%lf is Jimmy Pop and I am 2646388764387643 years old.",
      &lf2);
  ck_assert_int_eq(lf1, lf2);
  long double llf1 = 2;
  long double llf2 = 2;
  s21_sscanf(
      str,
      "Hello. My name %Lf is Jimmy Pop and I am 2646388764387643 years old.",
      &llf1);
  sscanf(str,
         "Hello. My name %Lf is Jimmy Pop and I am 2646388764387643 years old.",
         &llf2);
  ck_assert_int_eq(llf1, llf2);
  s21_sscanf(
      str,
      "Hello. My name %3f is Jimmy Pop and I am 2646388764387643 years old.",
      &f1);
  sscanf(str,
         "Hello. My name %3f is Jimmy Pop and I am 2646388764387643 years old.",
         &f2);
  ck_assert_int_eq(f1, f2);
}
END_TEST

START_TEST(test_sscanf_u) {
  unsigned int u1 = 2;
  unsigned int u2 = 2;
  char *str =
      "Hello. My name -343.5e-2 is Jimmy Pop and I am 2646388764387643 years "
      "old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %u years old.", &u1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %u years old.",
         &u2);
  ck_assert_int_eq(u1, u2);
  unsigned int u3 = 1;
  unsigned int u4 = 1;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2u%2u years old.",
             &u1, &u3);
  sscanf(str,
         "Hello. My name -343.5e-2 is Jimmy Pop and I am %2u%2u years old.",
         &u2, &u4);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(u3, u4);
  short unsigned su1 = 2;
  short unsigned su2 = 2;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %hu years old.",
             &su1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %hu years old.",
         &su2);
  ck_assert_int_eq(su1, su2);
  long unsigned lu1 = 2;
  long unsigned lu2 = 2;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %lu years old.",
             &lu1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %lu years old.",
         &lu2);
  ck_assert_int_eq(lu1, lu2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %2u years old.",
             &u1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %2u years old.",
         &u2);
  ck_assert_int_eq(u1, u2);
}
END_TEST

START_TEST(test_sscanf_n) {
  int n1 = 2;
  int n2 = 2;
  char *str =
      "Hello. My name -343.5e-2 is Jimmy Pop and I am 2646388764387643 years "
      "old.";
  s21_sscanf(
      str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %n years old.", &n1);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %n years old.",
         &n2);
  ck_assert_int_eq(n1, n2);
  s21_sscanf(str,
             "%nello. My name -343.5e-2 is Jimmy Pop and I am 2646388764387643 "
             "years old.",
             &n1);
  sscanf(str,
         "%nello. My name -343.5e-2 is Jimmy Pop and I am 2646388764387643 "
         "years old.",
         &n2);
  ck_assert_int_eq(n1, n2);
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am 2646388764387643 "
             "years old%n",
             &n1);
  sscanf(str,
         "Hello. My name -343.5e-2 is Jimmy Pop and I am 2646388764387643 "
         "years old%n",
         &n2);
  ck_assert_int_eq(n1, n2);
  int n3 = 1;
  int n4 = 1;
  s21_sscanf(str,
             "Hello. My name -343.5e-2 is Jimmy Pop and I am %n%n years old.",
             &n1, &n3);
  sscanf(str, "Hello. My name -343.5e-2 is Jimmy Pop and I am %n%n years old.",
         &n2, &n4);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(n3, n4);
}
END_TEST

int main() {
  Suite *s = suite_create("main");
  SRunner *runner = srunner_create(s);
  int err = 0;

  TCase *s21_memchrCase = tcase_create("memchr_test");
  suite_add_tcase(s, s21_memchrCase);
  tcase_add_test(s21_memchrCase, test_s21_memchr);

  TCase *s21_memcmpCase = tcase_create("memcmp_test");
  suite_add_tcase(s, s21_memcmpCase);
  tcase_add_test(s21_memcmpCase, test_s21_memcmp);

  TCase *s21_memcpyCase = tcase_create("memcpy_test");
  suite_add_tcase(s, s21_memcpyCase);
  tcase_add_test(s21_memcpyCase, test_s21_memcpy);

  TCase *s21_memset = tcase_create("memset_test");
  suite_add_tcase(s, s21_memset);
  tcase_add_test(s21_memset, test_s21_memset);

  TCase *s21_strncat = tcase_create("strncat_test");
  suite_add_tcase(s, s21_strncat);
  tcase_add_test(s21_strncat, test_s21_strncat);

  TCase *s21_strchr = tcase_create("strchr");
  suite_add_tcase(s, s21_strchr);
  tcase_add_test(s21_strchr, test_s21_strchr);

  TCase *s21_strncmp = tcase_create("strncmp_test");
  suite_add_tcase(s, s21_strncmp);
  tcase_add_test(s21_strncmp, test_s21_strncmp);

  TCase *s21_strncpy = tcase_create("strncpy_test");
  suite_add_tcase(s, s21_strncpy);
  tcase_add_test(s21_strncpy, test_s21_strncpy);

  TCase *s21_strcspn = tcase_create("strcspn_test");
  suite_add_tcase(s, s21_strcspn);
  tcase_add_test(s21_strcspn, test_s21_strcspn);

  TCase *s21_strerror = tcase_create("strerror_test");
  suite_add_tcase(s, s21_strerror);
  tcase_add_test(s21_strerror, test_s21_strerror);

  TCase *s21_strlen = tcase_create("strlen");
  suite_add_tcase(s, s21_strlen);
  tcase_add_test(s21_strlen, test_s21_strlen);

  TCase *s21_strpbrk = tcase_create("strpbrk");
  suite_add_tcase(s, s21_strpbrk);
  tcase_add_test(s21_strpbrk, test_s21_strpbrk);

  TCase *s21_strstr = tcase_create("strstr");
  suite_add_tcase(s, s21_strstr);
  tcase_add_test(s21_strstr, test_s21_strstr);

  TCase *s21_strrchr = tcase_create("strrchr");
  suite_add_tcase(s, s21_strrchr);
  tcase_add_test(s21_strrchr, test_s21_strrchr);

  TCase *s21_strtok = tcase_create("strtok");
  suite_add_tcase(s, s21_strtok);
  tcase_add_test(s21_strtok, test_s21_strtok);

  TCase *s21_to_upper = tcase_create("to_upper");
  suite_add_tcase(s, s21_to_upper);
  tcase_add_test(s21_to_upper, test_s21_to_upper);

  TCase *s21_to_lower = tcase_create("to_lower");
  suite_add_tcase(s, s21_to_lower);
  tcase_add_test(s21_to_lower, test_s21_to_lower);

  TCase *s21_insert = tcase_create("insert");
  suite_add_tcase(s, s21_insert);
  tcase_add_test(s21_insert, test_s21_insert);

  TCase *s21_trim = tcase_create("trim");
  suite_add_tcase(s, s21_trim);
  tcase_add_test(s21_trim, test_s21_trim);

  TCase *s21_sprintf_c = tcase_create("sprintf_c");
  suite_add_tcase(s, s21_sprintf_c);
  tcase_add_test(s21_sprintf_c, test_sprintf_c);

  TCase *s21_sprintf_d = tcase_create("sprintf_d");
  suite_add_tcase(s, s21_sprintf_d);
  tcase_add_test(s21_sprintf_d, test_sprintf_d);

  TCase *s21_sprintf_i = tcase_create("sprintf_i");
  suite_add_tcase(s, s21_sprintf_i);
  tcase_add_test(s21_sprintf_i, test_sprintf_i);

  TCase *s21_sprintf_f = tcase_create("sprintf_f");
  suite_add_tcase(s, s21_sprintf_f);
  tcase_add_test(s21_sprintf_f, test_sprintf_f);

  TCase *s21_sprintf_s = tcase_create("sprintf_s");
  suite_add_tcase(s, s21_sprintf_s);
  tcase_add_test(s21_sprintf_s, test_sprintf_s);

  TCase *s21_sprintf_o = tcase_create("sprintf_o");
  suite_add_tcase(s, s21_sprintf_o);
  tcase_add_test(s21_sprintf_o, test_sprintf_o);

  TCase *s21_sprintf_u = tcase_create("sprintf_u");
  suite_add_tcase(s, s21_sprintf_u);
  tcase_add_test(s21_sprintf_u, test_sprintf_u);

  TCase *s21_sprintf_x = tcase_create("sprintf_x");
  suite_add_tcase(s, s21_sprintf_x);
  tcase_add_test(s21_sprintf_x, test_sprintf_x);

  TCase *s21_sprintf_X = tcase_create("sprintf_X");
  suite_add_tcase(s, s21_sprintf_X);
  tcase_add_test(s21_sprintf_X, test_sprintf_X);

  TCase *s21_sprintf_p = tcase_create("sprintf_p");
  suite_add_tcase(s, s21_sprintf_p);
  tcase_add_test(s21_sprintf_p, test_sprintf_p);

  TCase *s21_sprintf_n = tcase_create("sprintf_n");
  suite_add_tcase(s, s21_sprintf_n);
  tcase_add_test(s21_sprintf_n, test_sprintf_n);

  TCase *s21_sprintf_percent = tcase_create("sprintf_percent");
  suite_add_tcase(s, s21_sprintf_percent);
  tcase_add_test(s21_sprintf_percent, test_sprintf_percent);

  TCase *s21_sprintf_e = tcase_create("sprintf_e");
  suite_add_tcase(s, s21_sprintf_e);
  tcase_add_test(s21_sprintf_e, test_sprintf_e);

  TCase *s21_sprintf_E = tcase_create("sprintf_E");
  suite_add_tcase(s, s21_sprintf_E);
  tcase_add_test(s21_sprintf_E, test_sprintf_E);

  TCase *s21_sprintf_g = tcase_create("sprintf_g");
  suite_add_tcase(s, s21_sprintf_g);
  tcase_add_test(s21_sprintf_g, test_sprintf_g);

  TCase *s21_sprintf_G = tcase_create("sprintf_G");
  suite_add_tcase(s, s21_sprintf_G);
  tcase_add_test(s21_sprintf_G, test_sprintf_G);

  TCase *s21_sscanf_dif = tcase_create("sscanf_dif");
  suite_add_tcase(s, s21_sscanf_dif);
  tcase_add_test(s21_sscanf_dif, test_sscanf_dif);

  TCase *s21_sscanf_c = tcase_create("sscanf_c");
  suite_add_tcase(s, s21_sscanf_c);
  tcase_add_test(s21_sscanf_c, test_sscanf_c);

  TCase *s21_sscanf_d = tcase_create("sscanf_d");
  suite_add_tcase(s, s21_sscanf_d);
  tcase_add_test(s21_sscanf_d, test_sscanf_d);

  TCase *s21_sscanf_i = tcase_create("sscanf_i");
  suite_add_tcase(s, s21_sscanf_i);
  tcase_add_test(s21_sscanf_i, test_sscanf_i);

  TCase *s21_sscanf_x = tcase_create("sscanf_x");
  suite_add_tcase(s, s21_sscanf_x);
  tcase_add_test(s21_sscanf_x, test_sscanf_x);

  TCase *s21_sscanf_p = tcase_create("sscanf_p");
  suite_add_tcase(s, s21_sscanf_p);
  tcase_add_test(s21_sscanf_p, test_sscanf_p);

  TCase *s21_sscanf_o = tcase_create("sscanf_o");
  suite_add_tcase(s, s21_sscanf_o);
  tcase_add_test(s21_sscanf_o, test_sscanf_o);

  TCase *s21_sscanf_s = tcase_create("sscanf_s");
  suite_add_tcase(s, s21_sscanf_s);
  tcase_add_test(s21_sscanf_s, test_sscanf_s);

  TCase *s21_sscanf_f = tcase_create("sscanf_f");
  suite_add_tcase(s, s21_sscanf_f);
  tcase_add_test(s21_sscanf_f, test_sscanf_f);

  TCase *s21_sscanf_u = tcase_create("sscanf_u");
  suite_add_tcase(s, s21_sscanf_u);
  tcase_add_test(s21_sscanf_u, test_sscanf_u);

  TCase *s21_sscanf_n = tcase_create("sscanf_n");
  suite_add_tcase(s, s21_sscanf_n);
  tcase_add_test(s21_sscanf_n, test_sscanf_n);

  srunner_run_all(runner, CK_NORMAL);
  err = srunner_ntests_failed(runner);
  srunner_free(runner);
  return err != 0;
}
