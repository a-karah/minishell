/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_folder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:20:41 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 21:56:45 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_alln(char *s)
{
	if (!s || !*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	look_folder(char ***ret, char *s, char *str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (ft_strnstr(s, "<<", 2))
		tmp1 = "<<";
	else if (ft_strnstr(s, ">>", 2))
		tmp2 = ">>";
	else if (*s == '<')
		tmp1 = "<";
	else if (*s == '>')
		tmp2 = ">";
	else
		return (0);
	if (!is_alln(str))
	{
		if (tmp1)
			add_str_newarg(ret, "0");
		if (tmp2)
			add_str_newarg(ret, "1");
	}
	if (!tmp1)
		tmp1 = tmp2;
	return (add_str_newarg(ret, tmp1));
}

int	if_case_folder(int i, char *s)
{
	if (s[i] == '\'')
		i += j_squote(s + i + 1) + 1;
	if (s[i] == '\"')
		i += j_dquote(s + i + 1) + 1;
	return (i);
}

char	**my_split_folder(char **arg)
{
	char	**ret;
	int		i;
	char	*tmp;
	char	*s;

	ret = copy_arg(NULL);
	while (arg && *arg)
	{
		s = *(arg++);
		while (s && *s)
		{
			i = 0;
			while (s[i] && !ft_isspace(s[i]) && !ft_strchr("<>", s[i]))
				i = if_case_folder(i, s) + 1;
			tmp = ft_substr(s, 0, i);
			if (*tmp)
				add_str_newarg(&ret, tmp);
			s += look_folder(&ret, s, tmp) + i;
			free(tmp);
		}		
	}
	return (ret);
}
