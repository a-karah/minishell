/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:19:35 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 12:33:55 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	echo(char **ag, t_my_env *e, int f)
{
	int	i;
	int	flag;

	flag = 1;
	i = 1;
	if (0 == ft_strcmp(ag[1], "-n"))
	{
		flag = 0;
		i++;
	}
	while (ag[i])
	{
		if (!f)
			ft_printf("%s", ag[i++]);
		if (!f && ag[i])
			ft_printf(" ");
	}
	if (!f && flag)
		ft_printf("\n");
	(void)e;
	return (0);
}
