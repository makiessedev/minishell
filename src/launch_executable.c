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
}