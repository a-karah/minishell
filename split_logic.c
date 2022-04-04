/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:20:45 by ysay              #+#    #+#             */
/*   Updated: 2022/03/30 14:09:08 by akarahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_operate(char *s)
{
	if (ft_strnstr(s, "||", 2))
		return (1);
	else if (ft_strnstr(s, "&&", 2))
		return (1);
	else if (*s == '|')
		return (1);
	return (0);
}

int	is_special(char *s)
{
	if (*s == '(')
		return (1);
	else if (*s == ')')
		return (1);
	else if (ft_strnstr(s, "||", 2))
		return (1);
	else if (ft_strnstr(s, "&&", 2))
		return (1);
	else if (*s == '|')
		return (1);
	return (0);
}

int	look_logic(char ***ret, char *s)
{
	int	f;

	f = 0;
	if (*s == '(')
		f = add_str_newarg(ret, "(");
	else if (*s == ')')
		f = add_str_newarg(ret, ")");
	else if (ft_strnstr(s, "||", 2))
		f = add_str_newarg(ret, "||");
	else if (ft_strnstr(s, "&&", 2))
		f = add_str_newarg(ret, "&&");
	else if (*s == '|')
		f = add_str_newarg(ret, "|");
	return (f);
}

char	**my_split_logic(char *s)
{
	char	**ret;
	int		i;
	char	*tmp;

	ret = copy_arg(NULL);
	while (s && *s)
	{
		while (s && ft_isspace(*s))
			s++;
		i = 0;
		while (s[i] && !ft_isspace(s[i]) && !is_special(&s[i]))
		{
			if (s[i] == '\'')
				i += j_squote(s + i + 1) + 1;
			if (s[i] == '\"')
				i += j_dquote(s + i + 1) + 1;
			i++;
		}
		tmp = ft_substr(s, 0, i);
		if (*tmp)
			add_str_newarg(&ret, tmp);
		free(tmp);
		s += look_logic(&ret, s) + i;
	}		
	return (ret);
}
