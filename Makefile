NAME = Parser
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic
CIGNORE = -Wno-string-compare
CC = gcc

all:
	@$(CC) src/*.c $(CFLAGS) $(CIGNORE) -o $(NAME)
	@./$(NAME)

compile:
	@$(CC) $(SOURCES) $(CFLAGS) $(CIGNORE) -o $(NAME)

test:
	cd debug; \
	cc ../src/*.c -g

run:
	@./$(NAME)
