#include "minishell.h"

int		main(int ac, char **av)
{
	char	*line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		launch_executable(line);
		free(line);
	}
	return (0);
}