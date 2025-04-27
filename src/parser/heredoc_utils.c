/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:54 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/27 01:43:45 by mmorais          ###   ########.fr       */
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
			{
				erase_tab_string(words);
				return (NULL);
			}
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

int	fill_heredoc(t_main *main_data, t_io_fds *io, int fd)
{
	char	*line;
	int		ret;
	int		stdin_backup;

	ret = FALSE;
	line = NULL;
	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
		return (1);
	signal(SIGINT, signal_ctlc_heredoc);
	while (1)
	{
		line = readline(">");
		if (check_error(stdin_backup) == FALSE)
			return (FALSE);
		if (!evaluate_heredoc_line(main_data, &line, io, &ret))
			break ;
		ft_putendl_fd(line, fd);
		erase_pointer(line);
	}
	signal(SIGINT, SIG_DFL);
	close(stdin_backup);
	erase_pointer(line);
	return (ret);
}
