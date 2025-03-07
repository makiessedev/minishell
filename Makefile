NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRC_PATH = ./src/
OBJ_PATH = ./temp/
INC_PATH = ./headers/
LIBFT_PATH = ./libs/libft/
LIBFT = $(LIBFT_PATH)libft.a

# Encontrar todos os arquivos .c automaticamente
SRC		= $(shell find $(SRC_PATH) -name "*.c")
OBJ		= $(patsubst $(SRC_PATH)%, $(OBJ_PATH)%, $(SRC:.c=.o))

INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(shell find $(SRC_PATH) -type d | sed "s|$(SRC_PATH)|$(OBJ_PATH)|")

# Compila arquivos .c -> .o
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "\033[33mCompiling: \033[34m$<\033[33m... \033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@printf "\033[32mOK!\033[0m\n"

# Cria o executável com uma animacao louca no final
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

# Compila a Libft
$(LIBFT):
	@printf "\r📦\033[33m Compiling libft...\033[0m\n"
	@make -C $(LIBFT_PATH) --no-print-directory
	@printf "\033c"

# Limpa os arquivos objetos
clean:
	@rm -rf $(OBJ_PATH) 2>/dev/null
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@sleep 0.5
	@printf "\033c"
	@printf "🗑 \033[31mObjects Cleaned...\033[0m\n"

# Limpa completamente (inclui o binário final(obvio))
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@sleep 0.5
	@printf "\033c"
	@echo "🗑r  \033[1;31mRemoved \033[33m$(NAME)...\033[0m"

# Recompilar tudo
re: fclean all

.PHONY: all clean fclean re
