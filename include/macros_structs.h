#ifndef STDBOOL_H
#define STDBOOL_H
# define bool int
# define true 1
# define false 0
#endif

# ifndef PATH_SIZE
#  define PATH_SIZE (1024*4)
# endif

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*heredoc_delimiter;
	bool	heredoc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
}	t_io_fds;
typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;


typedef struct s_token
{
	char			*token;
	char			*backup_token;
	bool			var_exists;
	int				type;
	int				status;
	bool			join;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell
{
    char    **envp;
    char    *current_workdir;
    char    *old_workdir;
    int     last_command_exit_code;
    char    *input_user;
    t_token *token;
    t_command	*cmd;
	pid_t		pid;
}	t_minishell;

typedef enum {
    NORMAL_MODE,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
}   e_quote_controller;

typedef enum {
    SPACE_TOKEN,
    PIPE_TOKEN,
    HEREDOC_TOKEN,
    APPEND_TOKEN,
    INPUT_TOKEN,
    REDIRECT_TOKEN,
    WORD_TOKEN,
    VAR_TOKEN,
    END_TOKEN,
}   e_tokens;
