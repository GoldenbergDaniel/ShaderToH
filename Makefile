NAME = Parser
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic
CC = cc

all:
	@$(CC) src/*.c $(CFLAGS) -o $(NAME)
	@./$(NAME)

compile:
	@$(CC) src/*.c $(CFLAGS) -o $(NAME)

test:
	cd debug; \
	$(CC) ../src/*.c -g

run:
	@./$(NAME)
