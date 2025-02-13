#include "list.h"

#include <stdio.h>

int test_remove_door();
int test_add_door();

int main() {
    if (test_add_door() == SUCCESS) {
        printf("test_add_door passed\n");
    } else {
        printf("test_add_door failed\n");
    }

    if (test_remove_door() == SUCCESS) {
        printf("test_remove_door passed\n");
    } else {
        printf("test_remove_door failed\n");
    }

    return 0;
}

int test_remove_door() {
    struct door door1 = {.id = 1, .status = 0};
    struct door door2 = {.id = 2, .status = 0};
    // struct door door3 = {.id = 3, .status = 0};
    struct node* root = init(&door1);
    if (!root) return FAIL;
    add_door(root, &door2);
    // add_door(root, &door3);

    root = remove_door(root->next, root);
    if (root->next != NULL) {
        destroy(root);
        return FAIL;
    }

    root = remove_door(root, root);
    if (root != NULL) {
        destroy(root);
        return FAIL;
    }

    destroy(root);
    return SUCCESS;
}

int test_add_door() {
    struct door door1 = {.id = 1, .status = 0};
    struct door door2 = {.id = 2, .status = 0};
    struct node* root = init(&door1);
    if (!root) return FAIL;

    struct node* new_node = add_door(root, &door2);
    find_door(1, new_node);
    if (!new_node || root->next != new_node || new_node->data.id != 2) {
        destroy(root);
        return FAIL;
    }

    destroy(root);
    return SUCCESS;
}