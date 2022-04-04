/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:20:29 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 15:08:56 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pwd(char **ag, t_my_env *e, int f)
{
	if (!f)
		ft_printf("%s\n", my_getenv("PWD", e->env));
	(void)ag;
	return (0);
}

int	unset(char **ag, t_my_env *e, int f)
{
	int	i;

	i = 1;
	while (ag[i])
	{
		dell_str(e->env, give_envindex(e->env, ag[i]));
		dell_str(e->exp, give_index(e->exp, ag[i]));
		i++;
	}
	(void)f;
	return (0);
}

int	envf(char **ag, t_my_env *e, int f)
{
	int		i;
	char	*ret;

	i = 0;
	while (ag[i])
		i++;
	if (i > 1)
	{
		ret = my_str3join("‘", ag[1], "‘");
		if (!f)
			my_perror(ag[0], ret, "No such file or directory", 0);
		free(ret);
		return (127);
	}
	while (!f && *e->env)
		ft_printf("%s\n", *(e->env++));
	(void)ag;
	return (0);
}

int	exitf(char **ag, t_my_env *e, int f)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (ag[i])
		i++;
	if (i > 2)
	{
		if (!f)
			my_perror("bash", *ag, "too many arguments", 0);
		return (130);
	}
	if (i == 2)
		ret = ft_atoi(ag[1]);
	if (!f)
		ft_printf("%s\n", ag[0]);
	kill_arg(ag);
	kill_arg(e->env);
	kill_arg(e->exp);
	free(e);
	exit(ret);
	return (0);
}
