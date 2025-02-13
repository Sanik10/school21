#include <stdio.h>
#include <stdlib.h>

// Структура для записи
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
} Record;

// Функция для поиска записи по дате
void search_by_date(const char *file_path, int search_day, int search_month, int search_year) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("n/a\n");
        return;
    }

    Record record;
    int found = 0;

    while (fread(&record, sizeof(Record), 1, file) == 1) {
        if (record.day == search_day && record.month == search_month && record.year == search_year) {
            printf("%d\n", record.code);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("n/a\n");
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("n/a\n");
        return 1;
    }

    const char *file_path = argv[1];
    const char *date_str = argv[2];

    int day, month, year;
    if (sscanf(date_str, "%d.%d.%d", &day, &month, &year) != 3) {
        printf("n/a\n");
        return 1;
    }

    search_by_date(file_path, day, month, year);

    return 0;
}