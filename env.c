/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:19:40 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 12:35:34 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*my_chenv(char *s, char **env, char *new)
{
	int		d;
	int		i;
	char	*tmp;

	i = 0;
	if (!s || !env || !new)
		return (NULL);
	d = ft_strlen(s);
	while (env[i] && !(0 == ft_strncmp(env[i], s, d) && '=' == env[i][d]))
		i++;
	if (!env[i])
		return (NULL);
	free(env[i]);
	tmp = ft_strjoin(s, "=");
	env[i] = ft_strjoin(tmp, new);
	free(tmp);
	return (env[i]);
}

int	give_envindex(char **env, char *s)
{
	int	d;
	int	i;

	i = 0;
	if (!s || !env)
		return (-1);
	d = ft_strlen(s);
	while (env[i] && !(0 == ft_strncmp(env[i], s, d) && '=' == env[i][d]))
		i++;
	if (!env[i])
		return (-1);
	return (i);
}

char	*my_getenv(char	*s, char **env)
{
	int	d;
	int	i;

	i = 0;
	if (!s || !env)
		return (NULL);
	d = ft_strlen(s);
	while (env[i] && !(0 == ft_strncmp(env[i], s, d) && '=' == env[i][d]))
		i++;
	if (!env[i])
		return (NULL);
	return (&env[i][d + 1]);
}

int	is_envin(char **env, char *item)
{
	char	*tmp;
	int		f;

	f = 0;
	while (item)
	{
		tmp = ft_strchr(item, '=');
		tmp = ft_substr(item, 0, ft_strlen(item) - ft_strlen(tmp));
		if (my_getenv(tmp, env))
			f = 1;
		if (f && !ft_strchr(item, '='))
			f = -2;
		else if (!f && !ft_strchr(item, '='))
			f = -1;
		free(tmp);
		break ;
	}
	return (f);
}

int	my_addexp(t_my_env *e, char *item)
{
	if (!item)
		return (0);
	if (is_argin(e->exp, item))
		return (0);
	add_str_newarg(&e->exp, item);
	return (1);
}
