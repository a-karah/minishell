/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:20:49 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 22:20:26 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	j_dquote(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\"')
	{
		if (s[i] == '\'')
			i += j_squote(s + i + 1) + 1;
		i++;
	}
	return (i);
}

int	j_squote(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\'')
	{
		if (s[i] == '\"')
			i += j_dquote(s + i + 1) + 1;
		i++;
	}
	return (i);
}

int	j_bracket(char **arg)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!arg || !arg[i] || 0 != ft_strcmp(arg[i], "("))
		return (0);
	count++;
	while (count && arg[++i])
	{
		if (0 == ft_strcmp(arg[i], "("))
			count++;
		else if (0 == ft_strcmp(arg[i], ")"))
			count--;
	}
	return (i);
}

char	*join_quote(char **ss, char	*str)
{
	int		i;
	char	*tmp;
	char	*s;

	s = *ss;
	i = 0;
	while (s[i] && s[i] != '\'' && s[i] != '\"')
		i++;
	tmp = ft_substr(s, 0, i);
	s += i;
	i = 0;
	str = join_and_free(str, tmp);
	if (*s && s[i] == '\'')
		i += j_squote(s + i + 1) + 1;
	if (*s && s[i] == '\"')
		i += j_dquote(s + i + 1) + 1;
	if (*s && ft_strchr("\"\'", *s))
	{
		tmp = ft_substr(s + 1, 0, i - 1);
		s += i;
		i = 0;
		str = join_and_free(str, tmp);
	}
	*ss = s;
	return (str);
}

char	**my_split_quote(char **arg)
{
	char	**ret;
	char	*s;
	char	*str;

	ret = copy_arg(NULL);
	while (arg && *arg)
	{
		s = *(arg++);
		str = ft_strdup("");
		while (s && *s)
			str = join_quote(&s, str);
		if (*str)
			add_str_newarg(&ret, str);
		free(str);
	}
	return (ret);
}
