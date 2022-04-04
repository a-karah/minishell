/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:19:51 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 16:37:38 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	w_export(t_my_env *e, int f)
{
	char	*tmp;
	int		i;

	i = 0;
	while (e->env[i] && !f)
	{
		tmp = ft_strchr(e->env[i], '=');
		tmp = ft_substr(e->env[i], 0, ft_strlen(e->env[i]) - ft_strlen(tmp));
		ft_printf("declare -x %s=", tmp);
		ft_printf("\"%s\"\n", my_getenv(tmp, e->env));
		i++;
	}
	i = 0;
	while (e->exp[i] && !f)
		ft_printf("declare -x %s\n", e->exp[i++]);
	return (0);
}

int	export(char **ag, t_my_env *e, int f)
{
	int		i;
	int		flag;

	flag = 0;
		i = arg_len(ag);
	if (i == 1)
		return (w_export(e, f));
	i = 0;
	while (ag[++i])
	{
		if (!is_valid(ag[i]))
		{
			flag = 1;
			if (!f)
				my_perror("bash: export", ag[i], "not a valid identifier", 0);
		}
		else
			my_addenv(e, ag[i]);
	}
	return (flag);
}
