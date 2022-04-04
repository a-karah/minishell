/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:29:58 by akarahan          #+#    #+#             */
/*   Updated: 2022/04/03 12:10:57 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "newshell.h"

int	check_syntax(char **arg)
{
	char	*s;
	int		i;

	i = 1;
	s = "syntax error near unexpected token";
	if (is_operate(arg[0]))
		return (print_error(arg[0], s));
	while (arg[i] && arg[i + 1])
	{
		while (arg[i] && !is_operate(arg[i]))
			++i;
		if (arg[i] && is_operate(arg[i])
			&& i < arg_len(arg) - 1 && is_operate(arg[i + 1]))
			return (print_error(arg[i + 1], s));
		if (!arg[i])
			break ;
		++i;
	}
	if (arg[arg_len(arg) - 1] && is_operate(arg[arg_len(arg) - 1]))
		return (print_error(arg[arg_len(arg) - 1], s));
	return (0);
}

int	is_folder_sing(char *s)
{
	if (0 == ft_strcmp(s, ">"))
		return (1);
	if (0 == ft_strcmp(s, "<"))
		return (1);
	if (0 == ft_strcmp(s, ">>"))
		return (1);
	if (0 == ft_strcmp(s, "<<"))
		return (1);
	return (0);
}

int	check_folder(char **arg)
{
	char	*s;
	int		i;

	i = 0;
	s = "syntax error near unexpected token";
	while (arg[i])
	{
		while (arg[i] && !is_folder_sing(arg[i]))
			++i;
		if (arg[i] && is_folder_sing(arg[i]) && arg[i + 1]
			&& is_operate(arg[i + 1]))
			return (print_error(arg[i + 1], s));
		else if (arg[i] && is_folder_sing(arg[i]) && !arg[i + 1])
			return (print_error("newline", s));
		if (!arg[i])
			break ;
		++i;
	}
	return (0);
}

int	check_p(char **arg)
{
	int		i;
	char	*s;

	s = "syntax error near unexpected token";
	i = 0;
	while (arg[i])
	{
		if (i && 0 == ft_strcmp("(", arg[i]) && !is_operate(arg[i - 1])
			&& ft_strcmp("(", arg[i - 1]))
		{
			if (!arg[i + 1])
				return (print_error("newline", s));
			else
				return (print_error(arg[i + 1], s));
		}
		i++;
	}
	return (0);
}

int	check(char **arg)
{
	if (check_p(arg))
		return (1);
	if (check_syntax(arg))
		return (1);
	if (check_folder(arg))
		return (1);
	return (0);
}
