NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./libs/libft

ENVIRONMENTS_FILES = get_var_index.c get_var_value.c is_existing_var.c \
											env_set.c env.c

EXPANSION = identify_var.c quotes_handler.c quotes_remover.c recover_value.c \
						replace_var.c var_expander.c var_expander_utils.c

TOKENIZATION_FILES = is_only_space.c

RUN_FILES = parse_path.c run_command.c run_utils.c run.c

LEXER_FILES = check_if_var.c lexer_grammar.c parse_user_input.c \
							token_lst_utils_2.c token_lst_utils.c tokenization.c

PARSER_FILES = cmd_lst_utils_cleanup.c cmd_lst_utils.c create_commands.c \
					fill_args_default.c fill_args_echo_utils.c fill_args_echo.c \
					parse_append.c parse_heredoc_utils.c parse_heredoc.c parse_input.c \
					parse_pipe.c parse_trunc.c parse_word.c

BUILTINS_FILES = cd.c echo.c env.c exit.c export.c pwd.c unset.c

REDIRECT_FILES = file_io.c pipes.c

SIGNALS_FILES = signal.c

UTILS_FILES = cleanup.c error.c exit.c init_data.c

SRC = main.c launch_executable.c \
	parse_input_and_execute.c token_utils.c \
	$(addprefix run/, $(RUN_FILES)) \
	$(addprefix environment/, $(ENVIRONMENTS_FILES)) \
	$(addprefix tokenization/, $(TOKENIZATION_FILES)) \
	$(addprefix expansion/, $(EXPANSION)) \
	$(addprefix lexer/, $(LEXER_FILES)) \
	$(addprefix parser/, $(PARSER_FILES)) \
	$(addprefix redirect/, $(REDIRECT_FILES)) \
	$(addprefix signals/, $(SIGNALS_FILES)) \
	$(addprefix utils/, $(UTILS_FILES)) \
	$(addprefix builtins/, $(BUILTINS_FILES)) \

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
