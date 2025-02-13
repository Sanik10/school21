# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
BUILD_DIR = ../build

# --- Цели для каждого квеста ---
strlen_tests: $(BUILD_DIR)/Quest_1
strcmp_tests: $(BUILD_DIR)/Quest_2
strcpy_tests: $(BUILD_DIR)/Quest_3
strcat_tests: $(BUILD_DIR)/Quest_4
strchr_tests: $(BUILD_DIR)/Quest_5
strstr_tests: $(BUILD_DIR)/Quest_6
strtok_tests: $(BUILD_DIR)/Quest_7
text_pro: $(BUILD_DIR)/Quest_8

# --- Правила сборки ---
$(BUILD_DIR)/Quest_1: CFLAGS += -DSTRELEN_TESTS
$(BUILD_DIR)/Quest_1: s21_string.c s21_string_test.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_2: CFLAGS += -DSTRCMP_TESTS
$(BUILD_DIR)/Quest_2: s21_string.c s21_string_test.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_3: CFLAGS += -DSTRCPY_TESTS
$(BUILD_DIR)/Quest_3: s21_string.c s21_string_test.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_4: CFLAGS += -DSTRCAT_TESTS
$(BUILD_DIR)/Quest_4: s21_string.c s21_string_test.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_5: CFLAGS += -DSTRCHR_TESTS
$(BUILD_DIR)/Quest_5: s21_string.c s21_string_test.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_6: CFLAGS += -DSTRSTR_TESTS
$(BUILD_DIR)/Quest_6: s21_string.c s21_string_test.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_7: CFLAGS += -DSTRTOK_TESTS
$(BUILD_DIR)/Quest_7: s21_string.c s21_string_test.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_8: text_processor.c s21_string.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests strtok_tests text_pro

clean:
		rm -rf $(BUILD_DIR)/*