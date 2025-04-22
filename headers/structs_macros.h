/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_macros.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:52:35 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/22 07:47:00 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MACROS_H
# define STRUCTS_MACROS_H
# ifndef STDBOOL_H
#  define STDBOOL_H
#  define TRUE 1
#  define FALSE 0
# endif

# define PROMPT "minishell$ "

# define CHDIR_ERROR -1
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_token
{
	char				*token;
	char				*backup_token;
	int					var_exists;
	int					type;
	int					status;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;
typedef struct s_io_fds
{
	char				*infile;
	char				*outfile;
	char				*heredoc_delimiter;
	int					heredoc_quotes;
	int					fd_in;
	int					fd_out;
	int					stdin_backup;
	int					stdout_backup;
}						t_io_fds;
typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	int					pipe_output;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_main
{
	t_token				*token;
	char				*user_input;
	char				**env;
	char				*working_dir;
	char				*old_working_dir;
	t_command			*cmd;
	pid_t				pid;
}						t_main;

typedef enum e_token_types
{
	SPACES_TOKEN = 1,
	WORD_TOKEN,
	VAR_TOKEN,
	PIPE_TOKEN,
	INPUT_TOKEN,
	REDIRECT_TOKEN,
	HEREDOC_TOKEN,
	APPEND_TOKEN,
	END_TOKEN
}						t_token_types;

typedef enum e_quoting_status
{
	NORMAL_MODE,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
}						t_quoting_status;
#endif
