NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./libs/libft
ENVIRONMENTS_FILES = get_var_index.c get_var_value.c is_existing_var.c
TOKENIZATION_FILES = is_only_space.c
SRC = main.c launch_executable.c \
	$(addprefix environment/, $(ENVIRONMENTS_FILES)) \
	$(addprefix tokenization/, $(TOKENIZATION_FILES))
FILES = $(addprefix ./src/, $(SRC))
OBJ_DIR = ./obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
HEADER = ./include/minishell.h
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

$(OBJ_DIR)/%.o: ./src/%.c $(HEADER)
	mkdir -p $(dir $@)
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
