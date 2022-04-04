/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:18:35 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 12:21:30 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	kill_arg(char **arg)
{
	size_t	i;

	if (!arg)
		return (0);
	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
	return (0);
}

int	arg_len(char **arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
		i++;
	return (i);
}

char	**copy_arg(char **env)
{
	char	**my_env;
	int		i;

	i = 0;
	while (env && env[i])
		i++;
	my_env = malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (env && env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}
