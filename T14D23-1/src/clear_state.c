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

// Функция для сравнения дат
int compare_dates(Record *rec, int year, int month, int day) {
    if (rec->year != year) return rec->year - year;
    if (rec->month != month) return rec->month - month;
    return rec->day - day;
}

// Функция для удаления записей в указанном временном промежутке
void clear_state(const char *file_path, int start_day, int start_month, int start_year, int end_day,
                 int end_month, int end_year) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("n/a\n");
        return;
    }

    FILE *temp_file = fopen("temp_file.bin", "wb");
    if (!temp_file) {
        fclose(file);
        printf("n/a\n");
        return;
    }

    Record record;
    int is_empty = 1;

    while (fread(&record, sizeof(Record), 1, file) == 1) {
        is_empty = 0;
        int cmp_start = compare_dates(&record, start_year, start_month, start_day);
        int cmp_end = compare_dates(&record, end_year, end_month, end_day);

        // Если дата записи вне заданного промежутка, сохраняем её
        if (cmp_start < 0 || cmp_end > 0) {
            fwrite(&record, sizeof(Record), 1, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    // Если файл пустой, или был не найден, или произошла ошибка
    if (is_empty) {
        printf("n/a\n");
        remove("temp_file.bin");
        return;
    }

    // Перемещаем временный файл на место оригинального
    if (remove(file_path) != 0 || rename("temp_file.bin", file_path) != 0) {
        printf("n/a\n");
        return;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("n/a\n");
        return 1;
    }

    const char *file_path = argv[1];
    const char *range_str = argv[2];

    int start_day, start_month, start_year;
    int end_day, end_month, end_year;

    if (sscanf(range_str, "%d.%d.%d %d.%d.%d", &start_day, &start_month, &start_year, &end_day, &end_month,
               &end_year) != 6) {
        printf("n/a\n");
        return 1;
    }

    clear_state(file_path, start_day, start_month, start_year, end_day, end_month, end_year);

    return 0;
}