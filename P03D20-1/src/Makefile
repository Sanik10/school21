.SILENT:

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
OBJ_DIR = ./binaries
BUILD_DIR = ../build

$(shell mkdir -p $(OBJ_DIR) $(BUILD_DIR))

all: graph

graph: calc.o list.o parser_alb.o PRN_calc.o stack.o input_alb.o graph.c
	$(CC) $(CFLAGS) graph.c $(OBJ_DIR)/calc.o $(OBJ_DIR)/list.o $(OBJ_DIR)/parser_alb.o $(OBJ_DIR)/PRN_calc.o $(OBJ_DIR)/stack.o $(OBJ_DIR)/input_alb.o -o $(BUILD_DIR)/graph

calc.o: calc.c
	$(CC) $(CFLAGS) -c calc.c -o $(OBJ_DIR)/calc.o

input_alb.o: input_alb.c
	$(CC) $(CFLAGS) -c input_alb.c -o $(OBJ_DIR)/input_alb.o

list.o: list.c
	$(CC) $(CFLAGS) -c list.c -o $(OBJ_DIR)/list.o

parser_alb.o: parser_alb.c
	$(CC) $(CFLAGS) -c parser_alb.c -o $(OBJ_DIR)/parser_alb.o

PRN_calc.o: PRN_calc.c
	$(CC) $(CFLAGS) -c PRN_calc.c -o $(OBJ_DIR)/PRN_calc.o

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c -o $(OBJ_DIR)/stack.o

clean:
	rm -rf $(OBJ_DIR)/*.o $(BUILD_DIR)/*

rebuild: clean all