NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./libft
SRC = main.c launch_executable.c
FILES = $(addprefix ./src/, $(SRC))
OBJ_DIR = ./obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
HEADER = ./include/minishell.h
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

$(OBJ_DIR)/%.o: ./src/%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -lft -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
