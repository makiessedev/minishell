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
			words[i] = var_expander_heredoc(main_data, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (make_str_from_tab(words));
}

static bool	evaluate_heredoc_line(t_main *main_data, char **line,
									t_io_fds *io, bool *ret)
{
	if (*line == NULL)
	{
		throw_command_error("warning", "here-document delimited by end-of-file: wanted",
			io->heredoc_delimiter, true);
		*ret = true;
		return (false);
	}
	if (ft_strncmp(*line, io->heredoc_delimiter, (ft_strlen(io->heredoc_delimiter) + 1)) == 0)
	{
		*ret = true;
		return (false);
	}
	if (io->heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = get_expanded_var_line(main_data, *line);
		if (!(*line))
		{
			erase_pointer(*line);
			*ret = false;
			return (false);
		}
	}
	return (true);
}

bool	fill_heredoc(t_main *main_data, t_io_fds *io, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		signals_manager();
		line = readline(">");
		if (!evaluate_heredoc_line(main_data, &line, io, &ret))
			break ;
		ft_putendl_fd(line, fd);
		erase_pointer(line);
	}
	erase_pointer(line);
	return (ret);
}
