/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_macros.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:52:35 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:57:34 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDBOOL_H
#define STDBOOL_H
#define bool int
#define true 1
#define false 0
#endif

#define PROMPT "minishell$ "

#define CHDIR_ERROR -1
#define CMD_NOT_FOUND 127
#define CMD_NOT_EXECUTABLE 126

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

typedef struct s_token {
  char *token;
  char *backup_token;
  bool var_exists;
  int type;
  int status;
  struct s_token *prev;
  struct s_token *next;
} t_token;
typedef struct s_io_fds {
  char *infile;
  char *outfile;
  char *heredoc_delimiter;
  bool heredoc_quotes;
  int fd_in;
  int fd_out;
  int stdin_backup;
  int stdout_backup;
} t_io_fds;
typedef struct s_command {
  char *command;
  char *path;
  char **args;
  bool pipe_output;
  int *pipe_fd;
  t_io_fds *io_fds;
  struct s_command *next;
  struct s_command *prev;
} t_command;

typedef struct s_main {
  t_token *token;
  char *user_input;
  char **env;
  char *working_dir;
  char *old_working_dir;
  t_command *cmd;
  pid_t pid;
} t_main;

typedef enum {
  SPACES_TOKEN = 1, // " "
  WORD_TOKEN,       // ls
  VAR_TOKEN,        // $PATH
  PIPE_TOKEN,       // |
  INPUT_TOKEN,      // <
  REDIRECT_TOKEN,   // >
  HEREDOC_TOKEN,    // <<
  APPEND_TOKEN,     // >>
  END_TOKEN
} e_token_types;

typedef enum {
  NORMAL_MODE,
  DOUBLE_QUOTE,
  SINGLE_QUOTE,
} e_quoting_status;
