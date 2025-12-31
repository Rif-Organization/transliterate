CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

# Separate sources for main and test
MAIN_SRCS = src/main.c src/transliterate.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

TEST_SRCS = src/test_transliterate.c src/transliterate.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

TARGET = main
TEST_TARGET = test_transliterate

# -- Rules --

all: $(TARGET)

run:
	@./$(TARGET)

$(TARGET): $(MAIN_OBJS)
	@mkdir -p bin
	@$(CC) $(CFLAGS) -o bin/$@ $^
	@./bin/$(TARGET)

test: $(TEST_TARGET)
	@./bin/$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	@mkdir -p bin
	@$(CC) $(CFLAGS) -o bin/$@ $^
	@echo "Built test executable: bin/$(TEST_TARGET)"

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) bin/$(TARGET) bin/$(TEST_TARGET)
	@echo removed $(OBJS) bin/$(TARGET) bin/$(TEST_TARGET)
