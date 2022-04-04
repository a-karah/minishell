/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:19:24 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 16:36:15 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cd(char **ag, t_my_env *e, int f)
{
	int		i;
	char	*tmp;
	int		flag;
	char	s[400];

	i = 0;
	while (ag[i])
		i++;
	if (i > 2 && !f)
		return (!my_perror("bash", *ag, "too many arguments", 0));
	if (i == 1)
		tmp = ft_strdup(my_getenv("HOME", e->env));
	else if (0 == ft_strcmp(ag[1], "-"))
		tmp = ft_strdup(my_getenv("OLDPWD", e->env));
	else
		tmp = ft_strdup(ag[1]);
	flag = chdir(tmp);
	if (flag != 0 && !f)
		return (!my_perror("bash: cd", ag[1], NULL, errno));
	my_chenv("OLDPWD", e->env, my_getenv("PWD", e->env));
	my_chenv("PWD", e->env, getcwd(s, 400));
	if (!f && 0 == flag && 0 == ft_strcmp(ag[1], "-"))
		ft_printf("%s\n", tmp);
	free(tmp);
	return (0);
}
