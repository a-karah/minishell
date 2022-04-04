/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:34:17 by akarahan          #+#    #+#             */
/*   Updated: 2022/04/03 16:11:51 by akarahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "newshell.h"

char	*create_prompt(t_my_env *e, char *hostname)
{
	char	*p_tmp;
	char	*p_tmp2;
	char	*prompt;

	p_tmp = ft_strjoin(my_getenv("USER", e->env), "@");
	p_tmp2 = ft_strjoin(my_getenv("PWD", e->env), ": ");
	prompt = my_str3join(p_tmp, hostname, p_tmp2);
	free(p_tmp);
	free(p_tmp2);
	return (prompt);
}

void	ft_print2d(char **s)
{
	char	**p;

	p = s;
	ft_printf("[");
	while (p && *p)
	{
		ft_printf("\"%s\"", *p);
		if (*(p + 1))
			ft_printf(", ");
		++p;
	}
	ft_printf("]\n");
}

char	*join_split(char **s)
{
	char	*join;
	char	*tmp;
	char	*prev;
	int		i;

	i = 0;
	join = NULL;
	while (s[i])
	{
		prev = join;
		if (s[i + 1] && s[i + 1] != NULL)
			tmp = ft_strjoin(s[i], " ");
		else
			tmp = ft_strdup(s[i]);
		join = ft_strjoin(prev, tmp);
		if (prev)
			free(prev);
		++i;
	}
	return (join);
}

void	free_doll(t_doll *doll)
{
	free(doll->get_env);
	free(doll->pre);
	free(doll->post);
}

int	check_dollar_in_dquote(char *s)
{
	int	dquote;
	int	i;

	i = 0;
	dquote = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			++dquote;
		if (s[i] == '\'' && dquote % 2 == 0)
			i += j_squote(s + i + 1) + 1;
		if (s[i] == '$')
			return (i);
		++i;
	}
	return (-1);
}
