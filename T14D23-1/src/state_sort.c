#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Функция для вывода записи на экран
void print_record(const Record *record) {
    printf("%d %d %d %d %d %d %d %d\n", record->year, record->month, record->day, record->hour,
           record->minute, record->second, record->status, record->code);
}

// Функция для сравнения двух записей
int compare_records(const void *a, const void *b) {
    const Record *recordA = (const Record *)a;
    const Record *recordB = (const Record *)b;

    if (recordA->year != recordB->year) return recordA->year - recordB->year;
    if (recordA->month != recordB->month) return recordA->month - recordB->month;
    if (recordA->day != recordB->day) return recordA->day - recordB->day;
    if (recordA->hour != recordB->hour) return recordA->hour - recordB->hour;
    if (recordA->minute != recordB->minute) return recordA->minute - recordB->minute;
    return recordA->second - recordB->second;
}

// Функция для сортировки части файла
void sort_chunk(FILE *file, long start, long end) {
    long size = end - start;
    Record *records = malloc(size * sizeof(Record));
    if (!records) {
        printf("n/a\n");
        return;
    }

    fseek(file, start * sizeof(Record), SEEK_SET);
    fread(records, sizeof(Record), size, file);
    qsort(records, size, sizeof(Record), compare_records);

    fseek(file, start * sizeof(Record), SEEK_SET);
    fwrite(records, sizeof(Record), size, file);

    free(records);
}

// Функция для слияния отсортированных частей
void merge_chunks(FILE *file, long total_records, long chunk_size) {
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        printf("n/a\n");
        return;
    }

    long chunks = (total_records + chunk_size - 1) / chunk_size;
    long *indices = calloc(chunks, sizeof(long));
    Record *buffer = malloc(chunks * sizeof(Record));
    int *active = calloc(chunks, sizeof(int));

    // Инициализация буферов
    for (long i = 0; i < chunks; i++) {
        fseek(file, i * chunk_size * sizeof(Record), SEEK_SET);
        if (fread(&buffer[i], sizeof(Record), 1, file) == 1)
            active[i] = 1;
        else
            active[i] = 0;  // Если не удалось прочитать, деактивируем
    }

    // Основной цикл слияния
    for (long i = 0; i < total_records; i++) {
        int min_index = -1;
        for (long j = 0; j < chunks; j++) {
            if (active[j] && (min_index == -1 || compare_records(&buffer[j], &buffer[min_index]) < 0)) {
                min_index = j;
            }
        }

        if (min_index == -1) {
            break;  // Все активные индексы неактивны
        }

        fwrite(&buffer[min_index], sizeof(Record), 1, temp_file);

        // Обновление буфера
        if (++indices[min_index] < chunk_size &&
            indices[min_index] < total_records - min_index * chunk_size) {
            fseek(file, (min_index * chunk_size + indices[min_index]) * sizeof(Record), SEEK_SET);
            if (fread(&buffer[min_index], sizeof(Record), 1, file) != 1) {
                active[min_index] = 0;  // Деактивируем, если не удалось прочитать
            }
        } else {
            active[min_index] = 0;
        }
    }

    fseek(temp_file, 0, SEEK_SET);
    fseek(file, 0, SEEK_SET);

    // Копирование отсортированных данных обратно в файл
    for (long i = 0; i < total_records; i++) {
        Record record;
        fread(&record, sizeof(Record), 1, temp_file);
        fwrite(&record, sizeof(Record), 1, file);
    }

    free(indices);
    free(buffer);
    free(active);
    fclose(temp_file);
}

// Функция для сортировки файла
void sort_file(const char *file_path) {
    FILE *file = fopen(file_path, "r+b");
    if (!file) {
        printf("n/a\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long total_records = ftell(file) / sizeof(Record);
    rewind(file);

    const long chunk_size = 100;  // Количество записей в одном блоке
    long chunks = (total_records + chunk_size - 1) / chunk_size;

    for (long i = 0; i < chunks; i++) {
        long start = i * chunk_size;
        long end = (i + 1) * chunk_size;
        if (end > total_records) end = total_records;
        sort_chunk(file, start, end);
    }

    merge_chunks(file, total_records, chunk_size);

    fclose(file);
}

// Функция для вывода содержимого файла
void display_file(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("n/a\n");
        return;
    }

    Record record;
    while (fread(&record, sizeof(Record), 1, file) == 1) {
        print_record(&record);
    }

    fclose(file);
}

// Функция для добавления записи в файл
void add_record(const char *file_path) {
    Record new_record;
    printf("Введите запись (год месяц день час минута секунда статус код): ");
    if (scanf("%d %d %d %d %d %d %d %d", &new_record.year, &new_record.month, &new_record.day,
              &new_record.hour, &new_record.minute, &new_record.second, &new_record.status,
              &new_record.code) != 8) {
        printf("n/a\n");
        return;
    }

    FILE *file = fopen(file_path, "ab");
    if (!file) {
        printf("n/a\n");
        return;
    }

    fwrite(&new_record, sizeof(Record), 1, file);
    fclose(file);

    sort_file(file_path);
}

int main() {
    char file_path[256];
    printf("Введите путь к файлу: ");
    if (scanf("%255s", file_path) != 1) {
        printf("n/a\n");
        return 1;
    }

    int exit_program = 0;
    while (!exit_program) {
        printf("======= Меню =======\n");
        printf("0. Вывести содержимое файла\n");
        printf("1. Сортировать файл и вывести\n");
        printf("2. Добавить запись, сортировать и вывести\n");
        printf("Введите ваш выбор или -1 для выхода: ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("n/a\n");
            break;
        }

        switch (choice) {
            case 0:
                display_file(file_path);
                printf("\n");
                break;
            case 1:
                sort_file(file_path);
                display_file(file_path);
                printf("\n");
                break;
            case 2:
                add_record(file_path);
                display_file(file_path);
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

    return 0;
}