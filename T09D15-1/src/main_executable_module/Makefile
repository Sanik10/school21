# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -I../data_libs -I../data_module -I../yet_another_decision_module 
BUILD_DIR = ../../build

# --- Цели для каждого квеста ---

quest1: $(BUILD_DIR)/Quest_1
quest2: $(BUILD_DIR)/Quest_2
quest3: $(BUILD_DIR)/Quest_3
quest4: $(BUILD_DIR)/Quest_4
quest5: $(BUILD_DIR)/Quest_5
quest6: $(BUILD_DIR)/Quest_6

# --- Правила сборки ---
$(BUILD_DIR)/Quest_1: ../data_libs/data_io.c ../data_libs/data_stat.c ../data_module/data_process.c ../data_module/data_module_entry.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_2: ../data_libs/data_io.c ../data_libs/data_stat.c ../yet_another_decision_module/yet_another_decision_module_entry.c ../yet_another_decision_module/decision.c 
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_3: main_executable_module.c ../data_libs/data_io.c ../data_libs/data_stat.c ../data_module/data_process.c ../yet_another_decision_module/decision.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_4: CFLAGS += -DUSE_MACRO_IO
$(BUILD_DIR)/Quest_4: main_executable_module.c ../data_libs/data_io.c ../data_libs/data_stat.c ../data_module/data_process.c ../yet_another_decision_module/decision.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/Quest_5: CFLAGS += -DUSE_MACRO_IO
$(BUILD_DIR)/Quest_5: $(BUILD_DIR)/libdata_stat.a main_executable_module.c ../data_libs/data_io.c ../data_module/data_process.c ../yet_another_decision_module/decision.c
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^ $(BUILD_DIR)/libdata_stat.a

$(BUILD_DIR)/libdata_stat.a: $(BUILD_DIR)/data_stat.o 
		ar rcs $@ $^

$(BUILD_DIR)/data_stat.o: ../data_libs/data_stat.c
		$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/Quest_6: CFLAGS += -DUSE_MACRO_IO
$(BUILD_DIR)/Quest_6: $(BUILD_DIR)/libdata_process.so main_executable_module.c ../data_libs/data_io.c ../data_libs/data_stat.c ../yet_another_decision_module/decision.c 
		mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $@ $^ -L$(BUILD_DIR) -ldata_process -ldl

$(BUILD_DIR)/libdata_process.so: ../data_module/data_process.c $(BUILD_DIR)/libdata_stat.a
		$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

# --- Дополнительные цели ---
.PHONY: all clean

all: quest1 quest2 quest3 quest4 quest5 quest6

clean:
		rm -rf $(BUILD_DIR)/*