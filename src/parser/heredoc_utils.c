/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:54 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:17:42 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_str_from_tab(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			erase_pointer(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			erase_pointer(tmp);
		}
	}
	erase_tab_string(tab);
	return (str);
}

static char	*get_expanded_var_line(t_main *main_data, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = expand_variables_in_heredoc(main_data, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (make_str_from_tab(words));
}

static int	evaluate_heredoc_line(t_main *main_data, char **line, t_io_fds *io,
		int *ret)
{
	if (*line == NULL)
	{
		throw_command_error("warning",
			"here-document delimited by end-of-file: wanted",
			io->heredoc_delimiter, TRUE);
		*ret = TRUE;
		return (FALSE);
	}
	if (ft_strncmp(*line, io->heredoc_delimiter,
			(ft_strlen(io->heredoc_delimiter) + 1)) == 0)
	{
		*ret = TRUE;
		return (FALSE);
	}
	if (io->heredoc_quotes == FALSE && ft_strchr(*line, '$'))
	{
		*line = get_expanded_var_line(main_data, *line);
		if (!(*line))
		{
			erase_pointer(*line);
			*ret = FALSE;
			return (FALSE);
		}
	}
	return (TRUE);
}


void	handle_heredoc_sigint(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_heredoc_signals(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = handle_heredoc_sigint;
	sigaction(SIGINT, &act, NULL);

	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

int	heredoc_child(t_main *main_data, t_io_fds *io, int fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);   // Comportamento padrão: Ctrl-C encerra
	signal(SIGQUIT, SIG_IGN);  // Ignora Ctrl-\"

	while (1)
	{
		line = readline(">");
		if (line == NULL)
		{
			write(1, "\n", 1);
			break ;
		}
		if (!evaluate_heredoc_line(main_data, &line, io, NULL))
			break ;
		ft_putendl_fd(line, fd);
		erase_pointer(line);
	}
	erase_pointer(line);
	close(fd);
	return (0); // sucesso
}

int	fill_heredoc(t_main *main_data, t_io_fds *io, int fd)
{
	(void)fd;
	pid_t	pid;
	int		status;
	int		ret_pipe[2];

	pipe(ret_pipe); // pipe para comunicação
	pid = fork();
	if (pid == 0)
	{
		// Filho: executa o heredoc real
		close(ret_pipe[0]);
		exit(heredoc_child(main_data, io, ret_pipe[1]));
	}
	else if (pid > 0)
	{
		// Pai: espera o filho terminar
		int	ret = FALSE;
		close(ret_pipe[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			ret = TRUE; // foi interrompido com Ctrl-C
		return (ret);
	}
	else
	{
		perror("fork");
		return (TRUE);
	}
}
