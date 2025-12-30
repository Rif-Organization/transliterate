CC = gcc
CFLAGS = -Wall -Wextra -I.

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

TARGET = main

# -- Rules --

run:
	@./$(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p bin
	@$(CC) $(CFLAGS) -o bin/$@ $^
	@./bin/$(TARGET)

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) bin/$(TARGET)
	@echo removed $(OBJS) bin/$(TARGET)
