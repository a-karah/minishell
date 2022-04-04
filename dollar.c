/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:34:46 by akarahan          #+#    #+#             */
/*   Updated: 2022/04/02 20:44:44 by akarahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "newshell.h"

int	skip_pre(char *s, t_doll *doll)
{
	int	j;
	int	k;

	j = 0;
	k = j;
	doll->pre = NULL;
	doll->get_env = NULL;
	doll->post = NULL;
	while (s[j] && s[j] != '$')
	{
		if (s[j] == '\'')
			j += j_squote(s + j + 1) + 1;
		++j;
	}
	if (j)
		doll->pre = ft_substr(s, k, j - k);
	return (j);
}

char	*replace_dollar(char *s, char **env)
{
	t_doll	doll;
	char	*tmp;
	int		j;
	int		k;

	j = skip_pre(s, &doll);
	if (s[j] == '$')
	{
		k = ++j;
		while (ft_isalpha(s[j]) || (s[j] == '?' && s[j - 1] == '$'))
			++j;
		tmp = ft_substr(s, k, j - k);
		if (tmp && *tmp)
		{
			if (ft_strcmp(tmp, "?") == 0)
				doll.get_env = ft_strdup(my_getenv("LASTRET", env));
			else
				doll.get_env = ft_strdup(my_getenv(tmp, env));
			free(tmp);
		}
	}
	doll.post = ft_strdup(s + j);
	tmp = my_str3join(doll.pre, doll.get_env, doll.post);
	free_doll(&doll);
	return (tmp);
}

char	*replace_dquote_dollar(char *s, char **env, int *eof)
{
	char	*dquote;
	char	*pre;
	char	*out;
	int		j;
	int		i;

	i = 0;
	out = NULL;
	j = check_dollar_in_dquote(s);
	if (j > 0)
	{
		i = j;
		while (s[i] != '$')
			++i;
		pre = ft_substr(s, 0, i);
		dquote = replace_dollar((s + j), env);
		out = ft_strjoin(pre, dquote);
		free(dquote);
		free(pre);
	}
	if (j == -1)
		*eof = j;
	return (out);
}

int	check_dollar(int j, char *arg, char **dollar, char **env)
{
	char	*tmp;
	int		reach_eof;

	reach_eof = 0;
	tmp = replace_dquote_dollar(*dollar, env, &reach_eof);
	if (tmp)
		tmp = replace_dollar(tmp, env);
	else
		tmp = replace_dollar(*dollar, env);
	if (tmp)
		*dollar = ft_strdup(tmp);
	if (tmp)
		free(tmp);
	if (reach_eof)
		return (reach_eof);
	else if (ft_strchr(arg + j, '$'))
		return (ft_strchr(arg + j, '$') - arg + 1);
	else
		return (-1);
}

void	my_split_dollar(char **arg, char **env)
{
	char	*dollar;
	int		i;
	int		j;

	i = -1;
	while (arg[++i])
	{
		j = 0;
		dollar = arg[i];
		while (j != -1 && ft_strchr(dollar + j, '$'))
			j = check_dollar(j, arg[i], &dollar, env);
		if (dollar && ft_strcmp(arg[i], dollar) != 0)
		{
			free(arg[i]);
			arg[i] = dollar;
		}
	}
}
