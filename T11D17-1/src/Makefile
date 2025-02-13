CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
BUILD_FOLDER = ../build

# ----- Цели сборки -----
door_struct: $(BUILD_FOLDER)/Quest_1
list_test: $(BUILD_FOLDER)/Quest_2
stack_test: $(BUILD_FOLDER)/Quest_3

# ----- Правила сборки -----
$(BUILD_FOLDER)/Quest_1: dmanager_module.c door_struct.h
		mkdir -p $(BUILD_FOLDER)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_FOLDER)/Quest_2: list.c list_test.c list.h door_struct.h
		mkdir -p $(BUILD_FOLDER)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_FOLDER)/Quest_3: stack.c stack_test.c stack.h
		mkdir -p $(BUILD_FOLDER)
		$(CC) $(CFLAGS) -o $@ $^

all: door_struct list_test stack_test

clean:
		rm -rf $(BUILD_FOLDER)/*

rebuild: clean all