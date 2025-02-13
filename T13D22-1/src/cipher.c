#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"

void print_file(const char *file_path, FILE *logfile) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("n/a\n");
        logcat(logfile, "Error opening file for reading", error);
        return;
    }
    logcat(logfile, "File opened for reading", info);

    int ch;
    int is_empty = 1;
    while ((ch = fgetc(file)) != EOF) {
        is_empty = 0;
        putchar(ch);
    }

    if (is_empty) {
        printf("n/a\n");
        logcat(logfile, "File is empty", info);
    }

    fclose(file);
    logcat(logfile, "File closed", info);
}

void append_to_file(const char *file_path, const char *text, FILE *logfile) {
    FILE *file = fopen(file_path, "a");
    if (file == NULL) {
        printf("n/a\n");
        logcat(logfile, "Error opening file for appending", error);
        return;
    }
    logcat(logfile, "File opened for appending", info);

    fprintf(file, "%s\n", text);
    fclose(file);
    logcat(logfile, "Text appended to file", info);
    logcat(logfile, "File closed", info);
}

void caesar_cipher_file(const char *file_path, int shift, FILE *logfile) {
    FILE *file = fopen(file_path, "r+");
    if (file == NULL) {
        printf("n/a\n");
        logcat(logfile, "Error opening file for Caesar cipher", error);
        return;
    }
    logcat(logfile, "File opened for Caesar cipher", info);

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *content = (char *)malloc(file_size + 1);
    if (!content) {
        printf("n/a\n");
        logcat(logfile, "Memory allocation error", error);
        fclose(file);
        return;
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';

    for (long i = 0; i < file_size; i++) {
        if (isalpha(content[i])) {
            char base = islower(content[i]) ? 'a' : 'A';
            content[i] = (content[i] - base + shift) % 26 + base;
        }
    }

    rewind(file);
    fwrite(content, 1, file_size, file);

    free(content);
    fclose(file);
    logcat(logfile, "Caesar cipher applied to file", info);
    logcat(logfile, "File closed", info);
}

void clear_file(const char *file_path, FILE *logfile) {
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        printf("n/a\n");
        logcat(logfile, "Error opening file for clearing", error);
        return;
    }
    logcat(logfile, "File opened for clearing", info);
    fclose(file);
    logcat(logfile, "File cleared", info);
    logcat(logfile, "File closed", info);
}

void process_directory(const char *dir_path, int shift, FILE *logfile) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        printf("n/a\n");
        logcat(logfile, "Error opening directory", error);
        return;
    }
    logcat(logfile, "Directory opened", info);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char *dot = strrchr(entry->d_name, '.');
            if (dot && (strcmp(dot, ".c") == 0 || strcmp(dot, ".h") == 0)) {
                size_t file_path_len = strlen(dir_path) + strlen(entry->d_name) + 2;
                char *file_path = (char *)malloc(file_path_len);
                if (file_path == NULL) {
                    printf("n/a\n");
                    logcat(logfile, "Memory allocation error", error);
                    closedir(dir);
                    return;
                }
                snprintf(file_path, file_path_len, "%s/%s", dir_path, entry->d_name);

                if (strcmp(dot, ".c") == 0) {
                    caesar_cipher_file(file_path, shift, logfile);
                } else if (strcmp(dot, ".h") == 0) {
                    clear_file(file_path, logfile);
                }

                free(file_path);
            }
        }
    }

    closedir(dir);
    logcat(logfile, "Directory closed", info);
}

int main() {
    FILE *logfile = log_init("cipher.log");
    if (logfile == NULL) {
        printf("Ошибка загрузки файла логирования");
    }
    char file_path[255];
    char input_text[1000];
    char dir_path[255];
    int exit_program = 0;
    int file_loaded = 0;

    logcat(logfile, "Program started", info);

    while (!exit_program) {
        printf("======= Меню =======\n");
        printf("1. Загрузить файл\n");
        printf("2. Записать текст в файл\n");
        printf("3. Шифрование файлов в директории\n");
        printf("Введите ваш выбор или -1 для выхода: ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("n/a\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice) {
            case 1:
                printf("Введите путь к файлу: ");
                if (scanf("%254s", file_path) != 1) {
                    printf("n/a\n");
                    logcat(logfile, "Invalid input", error);
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                file_loaded = 1;
                print_file(file_path, logfile);
                printf("\n");
                break;
            case 2:
                if (!file_loaded) {
                    printf("n/a\n");
                    logcat(logfile, "No file loaded", warning);
                } else {
                    printf("Введите текст для записи: ");
                    if (scanf(" %[^\n]", input_text) != 1) {
                        printf("n/a\n");
                        logcat(logfile, "Invalid input", error);
                        while (getchar() != '\n')
                            ;
                        continue;
                    }
                    append_to_file(file_path, input_text, logfile);
                    print_file(file_path, logfile);
                }
                printf("\n");
                break;
            case 3:
                printf("Введите путь к директории: ");
                if (scanf("%254s", dir_path) != 1) {
                    printf("n/a\n");
                    logcat(logfile, "Invalid input", error);
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                printf("Введите сдвиг для шифра Цезаря: ");
                int shift;
                if (scanf("%d", &shift) != 1) {
                    printf("n/a\n");
                    logcat(logfile, "Invalid input", error);
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                process_directory(dir_path, shift, logfile);
                printf("\n");
                break;
            case -1:
                exit_program = 1;
                break;
            default:
                printf("n/a\n");
                break;
        }
    }
    logcat(logfile, "Program closed", info);
    log_close(logfile);
    return 0;
}