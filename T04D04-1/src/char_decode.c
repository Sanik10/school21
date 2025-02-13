#include <stdio.h>

int encode(char symbol) { return symbol; }

char decode(int hex_num) { return hex_num; }

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("n/a\n");
        return 1;
    }

    int mode = argv[1][0] - '0';

    if (mode != 0 && mode != 1) {
        printf("n/a\n");
        return 1;
    }

    if (mode == 0) {
        char symbol1, symbol2;
        while (scanf("%c%c", &symbol1, &symbol2) == 2) {
            if (symbol2 == ' ') {
                printf("%02X%c", encode(symbol1), symbol2);
            } else if (symbol2 == '\n') {
                printf("%02X%c", encode(symbol1), symbol2);
                return 0;
            } else {
                printf("n/a\n");
                return 1;
            }
        }
        printf("\n");
    } else if (mode == 1) {
        int hex_num;
        char symbol2;

        while (scanf("%02X%c", &hex_num, &symbol2) == 2) {
            if (symbol2 == ' ') {
                printf("%c%c", decode(hex_num), symbol2);
            } else if (symbol2 == '\n') {
                printf("%c%c", decode(hex_num), symbol2);
                return 0;
            } else {
                printf("n/a\n");
                return 1;
            }
        }
        printf("\n");
    }

    return 0;
}