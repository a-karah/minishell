/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:20:33 by ysay              #+#    #+#             */
/*   Updated: 2022/04/03 12:09:37 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid(char *item)
{
	if (!ft_isalpha(*item))
		return (0);
	item++;
	while (*item && ft_isalpha(*item))
		item++;
	if (*item && *item != '=')
		return (0);
	return (1);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

char	*my_str3join(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	return (ret);
}

int	my_perror(char *cmd, char *str, char *opt, int no)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (opt)
		ft_putstr_fd(opt, 2);
	else
		ft_putstr_fd(strerror(no), 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int	print_error(char *arg, char *s)
{
	char	*str;

	str = my_str3join("`", arg, "\'");
	my_perror("bash", s, str, 0);
	free(str);
	return (1);
}
