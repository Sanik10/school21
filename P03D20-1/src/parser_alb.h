#ifndef PARSER_ALB_H
#define PARSER_ALB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "stack.h"

list_node* parse_to_rpn(const char* expression);
int is_digit(char c);
int is_alpha(char c);
void print_list(list_node* list);

#endif