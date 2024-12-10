#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	launch_executable(char *cmd)
{
	char	**cmds;
	char	**envp;
	pid_t	pid;

	cmds = ft_split(cmd, ' ');
	envp = ft_split(getenv("PATH"), ':');
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmds[0], X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(cmds[0], cmds, envp);
				printf("minishell: %s: Execution failed\n", cmd);
				exit(EXIT_FAILURE);
			}
			else if (pid > 0)
				waitpid(pid, NULL, 0);
			else
				printf("minishell: %s: Fork failed\n", cmd);
		}
		else
		{
			printf("minishell: %s: No such file or directory\n", cmd);
		}
	}
	else
	{
		int	i;

		i = 0;
		while (envp[i])
		{
			char	*path;
			char	*tmp;

			tmp = ft_strjoin(envp[i], "/");
			path = ft_strjoin(tmp, cmds[0]);
			free(tmp);
			if (access(path, X_OK) == 0)
			{
				pid = fork();
				if (pid == 0)
				{
					execve(path, cmds, envp);
					printf("minishell: %s: Execution failed\n", cmd);
					exit(EXIT_FAILURE);
				}
				else if (pid > 0)
					waitpid(pid, NULL, 0);
				else
					printf("minishell: %s: Fork failed\n", cmd);
				break ;
			}
			free(path);
			i++;
		}
		if (!envp[i])
			printf("minishell: %s: Command not found\n", cmd);
	}
}