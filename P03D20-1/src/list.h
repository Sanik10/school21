#ifndef LIST_H
#define LIST_H

typedef struct list_node {
    char oper;
    double value;
    struct list_node *next;
} list_node;

list_node *init_node_list(char oper, double value);
list_node *append(list_node *elem, char oper, double value);
list_node *remove_elem(list_node *elem, list_node *root);
void destroy_list(list_node *root);

#endif