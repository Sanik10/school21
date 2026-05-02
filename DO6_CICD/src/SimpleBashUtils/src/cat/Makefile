CC = gcc
CFLAGS = -Werror -Wextra -Wall -std=c11
SRCS = s21_cat.c
OBJS = $(SRCS:.c=.o)
EXEC = s21_cat

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

rebuild: clean all