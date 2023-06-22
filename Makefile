NAME = Parser
CFLAGS = -std=c17 -O0 -Wall -Wpedantic
CC = cc

all:
	@$(CC) src/*.c $(CFLAGS) -o $(NAME)
	@./$(NAME)

compile:
	@$(CC) $(SOURCES) $(CFLAGS) -o $(NAME)

run:
	@./$(NAME)
