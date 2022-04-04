/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:19:16 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 12:22:34 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*is_argin(char **arg, char *str)
{
	int	i;

	if (!arg || str)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (0 == ft_strcmp(arg[i], str))
			return (arg[i]);
		i++;
	}
	return (NULL);
}

int	give_index(char **arg, char *str)
{
	int	i;

	if (!arg || !str)
		return (-1);
	i = 0;
	while (arg[i])
	{
		if (0 == ft_strcmp(arg[i], str))
			return (i);
		i++;
	}
	return (-1);
}

int	dell_str(char **arg, int index)
{
	int	i;

	if (!arg)
		return (-1);
	i = 0;
	while (arg[i])
		i++;
	if (i <= index || index < 0)
		return (-1);
	free(arg[index]);
	while (index < i)
	{
		arg[index] = arg[index + 1];
		index++;
	}
	return (0);
}

char	**add_str(char **arg, char *s)
{
	char	**tmp;
	int		i;

	i = 0;
	while (arg && arg[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (arg && arg[i])
	{
		tmp[i] = ft_strdup(arg[i]);
		i++;
	}
	tmp[i++] = ft_strdup(s);
	tmp[i] = NULL;
	return (tmp);
}

int	add_str_newarg(char ***arg, char *s)
{
	char	**tmp;

	tmp = add_str(*arg, s);
	kill_arg(*arg);
	*arg = tmp;
	return (ft_strlen(s));
}
