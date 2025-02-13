CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
BUILD_FOLDER = ../build

cipher: $(BUILD_FOLDER)/cipher
logging_cipher: $(BUILD_FOLDER)/logging_cipher

$(BUILD_FOLDER)/cipher: cipher.c
		mkdir -p $(BUILD_FOLDER)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_FOLDER)/logging_cipher: cipher.c logger.c logger.h log_levels.h 
		mkdir -p $(BUILD_FOLDER)
		$(CC) $(CFLAGS) -o $@ $^

all: cipher logging_cipher

clean:
		rm -rf $(BUILD_FOLDER)/*

rebuild: clean all