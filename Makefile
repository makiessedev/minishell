NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./libft
SRC = main.c
FILES = $(addprefix ./src/, $(SRC))
OBJ = $(FILES:.c=.o)
HEADER = ./include/minishell.h
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

$(NAME): $(OBJ) $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -lft -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

clean:
	rm -rf $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
