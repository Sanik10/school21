#include "stack.h"

#include <stdio.h>

int test_push() {
    struct stack* s = init();
    if (!s) return FAIL;

    if (push(s, 10) != SUCCESS) {
        destroy(s);
        return FAIL;
    }

    if (s->top->data != 10) {
        destroy(s);
        return FAIL;
    }

    destroy(s);
    return SUCCESS;
}

int test_pop() {
    struct stack* s = init();
    if (!s) return FAIL;

    push(s, 20);
    int value;
    if (pop(s, &value) != SUCCESS || value != 20) {
        destroy(s);
        return FAIL;
    }

    if (pop(s, &value) != FAIL) {
        destroy(s);
        return FAIL;
    }

    destroy(s);
    return SUCCESS;
}

int main() {
    if (test_push() == SUCCESS) {
        printf("test_push passed\n");
    } else {
        printf("test_push failed\n");
    }

    if (test_pop() == SUCCESS) {
        printf("test_pop passed\n");
    } else {
        printf("test_pop failed\n");
    }

    return 0;
}