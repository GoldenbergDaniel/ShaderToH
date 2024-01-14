NAME = ShaderToC
CFLAGS = -O1 -std=c17
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
