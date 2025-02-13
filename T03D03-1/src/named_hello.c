#include <stdio.h>

int main() {
    int name;

    if (scanf("%d", &name) == 1) {
        printf("Hello, %d!\n", name);
    } else {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    return 0;
}