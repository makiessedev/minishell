NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c
FILES = $(addprefix ./src/, $(SRC))
OBJ = $(FILES:.c=.o)
HEADER = ./include/minishell.h

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline
all: $(NAME)
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all
