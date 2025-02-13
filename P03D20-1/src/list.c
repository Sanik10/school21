#include "list.h"

#include <stdlib.h>

list_node *init_node_list(char oper, double value) {
    list_node *first = (list_node *)malloc(sizeof(list_node));
    first->value = value;
    first->oper = oper;
    first->next = NULL;
    return first;
}
list_node *append(list_node *elem, char oper, double value) {
    elem->next = init_node_list(oper, value);
    return elem->next;
}

list_node *remove_elem(list_node *elem, list_node *root) {
    if (elem == NULL || root == NULL) return NULL;

    if (elem == root) {
        struct list_node *new_root = root->next;
        free(root);
        return new_root;
    }
    struct list_node *current = root;
    while (current->next != NULL && current->next != elem) {
        current = current->next;
    }

    if (current->next == elem) {
        current->next = elem->next;
        free(elem);
    }

    return root;
}

void destroy_list(list_node *root) {
    struct list_node *current = root;
    while (current != NULL) {
        struct list_node *next = current->next;
        free(current);
        current = next;
    }
}