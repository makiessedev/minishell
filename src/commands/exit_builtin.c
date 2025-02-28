#include "minishell.h"

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

static int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

static int	get_exit_code(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

static bool	is_quiet_mode(t_main *main_data)
{
	t_command	*cmd;

	cmd = main_data->cmd;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (true);
	return (false);
}

int	exit_builtin(t_main *main_data, char **args)
{
	int		exit_code;
	bool	error;
	bool	quiet;

	quiet = is_quiet_mode(main_data);
	error = false;
	if (!quiet)
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		exit_code = g_exit_code;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
			exit_code = throw_command_error("exit", args[1],
					"numeric argument required", 2);
		else if (args[2])
			return (throw_command_error("exit", NULL, "too many arguments", 1));
	}
	erase_and_exit_shell(main_data, exit_code);
	return (2);
}
