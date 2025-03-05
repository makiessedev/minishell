NAME	= minishell

CC		= cc
CFLAGS	= -Werror -Wextra -Wall

SRC_PATH = ./src/
OBJ_PATH = ./temp/
INC_PATH = ./headers/
SRC		= 	main.c app.c \
			utils/initial_configs.c \
			env/env.c \
			env/env_set.c \
			error/throw_command_error.c \
			error/throw_message_error.c \
			error/util.c \
			tokenization/process_user_command.c \
			tokenization/tokenization.c \
			tokenization/utils_1.c \
			tokenization/validate_syntax_and_variables.c \
			tokenization/lst_utils_1.c \
			expansion/expand_variables.c \
			expansion/var_expander_utils.c \
			expansion/identify_var.c \
			expansion/quotes_handler.c \
			expansion/quotes_remover.c \
			expansion/process_variables.c \
			expansion/utils.c \
			parser/create_commands.c \
			parser/parse_word.c \
			parser/fill_args_echo.c \
			parser/fill_args_echo_utils.c \
			parser/fill_args_default.c \
			parser/parse_input.c \
			parser/parse_trunc.c \
			parser/parse_append.c \
			parser/parse_heredoc.c \
			parser/parse_heredoc_utils.c \
			parser/parse_pipe.c \
			parser/cmd_lst_utils.c \
			parser/cmd_lst_utils_cleanup.c \
			commands/export_builtin.c \
			commands/unset_builtin.c \
			commands/cd_builtin.c \
			commands/env_builtin.c \
			commands/pwd_builtin.c \
			commands/echo_builtin.c \
			commands/exit_builtin.c \
			run/run.c \
			run/run_cmd.c \
			run/run_utils.c \
			run/parse_path.c \
			redirections/pipe.c \
			redirections/file_io.c \
			utils/exit.c \
			utils/ft_is_space.c \
			erase/close_fds.c \
			erase/erase_input_output.c \
			erase/erase_main_data.c \
			erase/erase_pointer.c \
			erase/erase_tab_string.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

LIBFT_PATH = ./libs/libft/
LIBFT = ./libs/libft/libft.a

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/commands
	mkdir -p $(OBJ_PATH)/tokenization
	mkdir -p $(OBJ_PATH)/expansion
	mkdir -p $(OBJ_PATH)/parser
	mkdir -p $(OBJ_PATH)/env
	mkdir -p $(OBJ_PATH)/run
	mkdir -p $(OBJ_PATH)/utils
	mkdir -p $(OBJ_PATH)/redirections
	mkdir -p $(OBJ_PATH)/error
	mkdir -p $(OBJ_PATH)/erase

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) -l readline

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
