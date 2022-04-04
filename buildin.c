/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:19:21 by ysay              #+#    #+#             */
/*   Updated: 2022/03/29 10:14:28 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_mainin(int ac, char **arg)
{
	int			i;
	const char	*build[] = {"cd", "export", "unset", "exit", NULL};
	char		**data;

	i = 0;
	while (i < ac && 0 != ft_strcmp(arg[i], "|"))
		i++;
	if (arg[i] && 0 == ft_strcmp(arg[i], "|"))
		return (0);
	data = find_cmd(i, arg);
	if (!data)
		return (0);
	if (is_group(data, 0))
	{
		kill_arg(data);
		return (0);
	}
	i = 0;
	while (build[i] && 0 != ft_strcmp(*data, build[i]))
		i++;
	kill_arg(data);
	if (!build[i])
		return (0);
	return (1);
}

int	is_buildin(char **arg, t_my_env *e)
{
	int			i;
	const char	*build[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit", NULL};

	(void)e;
	i = 0;
	while (build[i] && 0 != ft_strcmp(*arg, build[i]))
		i++;
	if (!build[i])
		return (0);
	return (1);
}

int	buildin(char **arg, t_my_env *e, int f)
{
	int			i;
	const char	*build[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit", NULL};
	const void	*vf[] = {echo, cd, pwd, export, unset, envf, exitf};
	int			(*fp)(char **, t_my_env *, int);

	i = 0;
	while (build[i] && 0 != ft_strcmp(*arg, build[i]))
		i++;
	if (!build[i])
		return (0);
	fp = vf[i];
	my_chenv("_", e->env, *arg);
	i = fp(arg, e, f);
	kill_arg(arg);
	return (i);
}
