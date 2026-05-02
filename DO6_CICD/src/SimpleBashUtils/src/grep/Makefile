CC = gcc
CFLAGS = -Werror -Wextra -Wall -std=c11
SRCS = s21_grep.c
OBJS = $(SRCS:.c=.o)
EXEC = s21_grep

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

rebuild: clean all