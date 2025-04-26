NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRC_PATH = ./src/
OBJ_PATH = ./temp/
INC_PATH = ./headers/
LIBFT_PATH = ./libs/libft/
LIBFT = $(LIBFT_PATH)libft.a

SRC		= ./src/app.c			\
		./src/commands/exec_cd.c				\
		./src/commands/exec_cd_utils.c			\
		./src/commands/exec_echo.c			\
		./src/commands/exec_echo_utils.c			\
		./src/commands/exec_env.c			\
		./src/commands/exec_exit.c			\
		./src/commands/exec_exit_utils.c			\
		./src/commands/exec_export.c			\
		./src/commands/exec_export_utils.c			\
		./src/commands/exec_pwd.c			\
		./src/commands/exec_unset.c			\
		./src/environment/env_utils1.c			\
		./src/environment/env_utils2.c			\
		./src/erase/close_fds.c			\
		./src/erase/erase_command.c			\
		./src/erase/erase_input_output.c			\
		./src/erase/erase_main_data.c			\
		./src/erase/erase_pointer.c			\
		./src/erase/erase_tab_string.c			\
		./src/error/throw_command_error.c			\
		./src/error/throw_message_error.c			\
		./src/error/util.c			\
		./src/expansion/expand_variables.c			\
		./src/expansion/process_variables.c			\
		./src/expansion/utils.c			\
		./src/expansion/utils2.c			\
		./src/expansion/utils3.c			\
		./src/io/file.c			\
		./src/io/pipe.c			\
		./src/main.c			\
		./src/parser/args_utils.c			\
		./src/parser/command_utils.c			\
		./src/parser/create_commands.c			\
		./src/parser/heredoc_parser.c			\
		./src/parser/heredoc_utils.c			\
		./src/parser/parse_tokens_to_args.c			\
		./src/parser/parsers.c			\
		./src/parser/parsers_util.c			\
		./src/parser/heredoc_signal_manager.c \
		./src/quotes_remover/quotes_remover.c			\
		./src/quotes_remover/utils.c			\
		./src/run/parse_path.c			\
		./src/run/run.c			\
		./src/run/run_cmd.c			\
		./src/run/run_utils.c			\
		./src/tokenization/lst_utils_1.c			\
		./src/tokenization/process_user_command.c			\
		./src/tokenization/tokenization.c			\
		./src/tokenization/utils_1.c			\
		./src/tokenization/validate_syntax_and_variables.c			\
		./src/utils/exit.c			\
		./src/utils/ft_is_space.c			\
		./src/utils/initial_configs.c \
		./src/utils/count_tab.c

OBJ		= $(patsubst $(SRC_PATH)%, $(OBJ_PATH)%, $(SRC:.c=.o))

INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(shell find $(SRC_PATH) -type d | sed "s|$(SRC_PATH)|$(OBJ_PATH)|")

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "\033[33mCompiling: \033[34m$<\033[33m... \033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@printf "\033[32mOK!\033[0m\n"

$(NAME): $(OBJ)
	@printf "\n"
	@bash -c ' \
		spin_chars="🔧 🔩 🛠️ ⚙️"; \
		for i in $$(seq 1 5); do \
			for char in $$spin_chars; do \
				printf "\r%s \033[33mLinking \033[34m$(NAME)\033[33m...\033[0m" "$$char"; \
				sleep 0.2; \
			done; \
		done; \
		printf "\033[K" \
	'
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC) $(LIBFT) -l readline
	@printf "\r✅ \033[32mCompilation Done!\033[0m"
	@sleep 1
	@printf "\033c"

$(LIBFT):
	@printf "\r📦\033[33m Compiling libft...\033[0m\n"
	@make -C $(LIBFT_PATH) --no-print-directory
	@printf "\033c"

clean:
	@rm -rf $(OBJ_PATH) 2>/dev/null
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@sleep 0.5
	@printf "\033c"
	@printf "🗑 \033[31mObjects Cleaned...\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@sleep 0.5
	@printf "\033c"
	@echo "🗑r  \033[1;31mRemoved \033[33m$(NAME)...\033[0m"

re: fclean all

.PHONY: all clean fclean re
