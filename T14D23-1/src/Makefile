CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
BUILD_FOLDER = ../build

state_sort: $(BUILD_FOLDER)/Quest_1
state_search: $(BUILD_FOLDER)/Quest_2
clear_state:$(BUILD_FOLDER)/Quest_3

$(BUILD_FOLDER)/Quest_1: state_sort.c
		mkdir -p $(BUILD_FOLDER)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_FOLDER)/Quest_2: state_search.c
		mkdir -p $(BUILD_FOLDER)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_FOLDER)/Quest_3: clear_state.c
		mkdir -p $(BUILD_FOLDER)
		$(CC) $(CFLAGS) -o $@ $^

all: state_sort state_search clear_state

clean:
		rm -rf $(BUILD_FOLDER)/*

rebuild: clean all