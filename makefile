CC = gcc
CFLAGS = -Wall -Wextra -I.

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

TARGET = main

# -- Rules --

run:
	@./$(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^
	@./$(TARGET)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
