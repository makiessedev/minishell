#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

static void	launch_absolute_or_relative_path(char	**splited_cmds, char	**envp);
static void	launch_path_from_envp(char	**splited_cmds, char	**envp);

void	launch_executable(char *full_cmds)
{
	char	**splited_cmds;
	char	**envp;

	splited_cmds = ft_split(full_cmds, ' ');
	envp = ft_split(getenv("PATH"), ':');
	if (full_cmds[0] == '/' || (full_cmds[0] == '.' && full_cmds[1] == '/'))
		launch_absolute_or_relative_path(splited_cmds, envp);
	else
		launch_path_from_envp(splited_cmds, envp);
}

static void	launch_absolute_or_relative_path(char	**splited_cmds, char	**envp)
{
	pid_t	pid;

	if (access(splited_cmds[0], X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(splited_cmds[0], splited_cmds, envp);
			printf("minishell: %s: Execution failed\n", splited_cmds[0]);
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
			waitpid(pid, NULL, 0);
		else
			printf("minishell: %s: Fork failed\n", splited_cmds[0]);
	}
	else
	{
		printf("minishell: %s: No such file or directory\n", splited_cmds[0]);
	}
}

static void	launch_path_from_envp(char	**splited_cmds, char	**envp)
{
	pid_t	pid;
	int	i;
	char	*path;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		tmp = ft_strjoin(envp[i], "/");
		path = ft_strjoin(tmp, splited_cmds[0]);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(path, splited_cmds, envp);
				printf("minishell: %s: Execution failed\n", splited_cmds[0]);
				exit(EXIT_FAILURE);
			}
			else if (pid > 0)
				waitpid(pid, NULL, 0);
			else
				printf("minishell: %s: Fork failed\n", splited_cmds[0]);
			break ;
		}
		free(path);
		i++;
	}
	if (!envp[i])
		printf("minishell: %s: Command not found\n", splited_cmds[0]);
}