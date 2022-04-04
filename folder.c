/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:20:15 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 15:07:13 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_in(char *fd, char *file, int f)
{
	int	fd2;
	int	io;

	if (f)
		return (0);
	io = atoi(fd);
	if (access(file, F_OK) == 0 && access(file, R_OK) != 0)
	{
		my_perror("bash", file, NULL, errno);
		return (1);
	}
	fd2 = open(file, O_RDONLY);
	if (fd2 == -1)
	{
		my_perror("bash", file, NULL, errno);
		return (1);
	}
	dup2(fd2, io);
	return (0);
}

int	open_heredoc(char *fd, char *str, int f)
{
	int	io;
	int	p[2];

	if (f)
		return (0);
	pipe(p);
	io = atoi(fd);
	ft_putstr_fd(str, p[1]);
	dup2(p[0], io);
	close(p[1]);
	return (0);
}

int	open_appendout(char *fd, char *file, int f)
{
	int	fd2;
	int	io;

	if (f)
		return (0);
	io = atoi(fd);
	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
	{
		my_perror("bash", file, NULL, errno);
		return (1);
	}
	fd2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd2 == -1)
	{
		my_perror("bash", file, NULL, errno);
		return (1);
	}
	dup2(fd2, io);
	return (0);
}

int	open_out(char *fd, char *file, int f)
{
	int	fd2;
	int	io;

	if (f)
		return (0);
	io = atoi(fd);
	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
	{
		my_perror("bash", file, NULL, errno);
		return (1);
	}
	fd2 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd2 == -1)
	{
		my_perror("bash", file, NULL, errno);
		return (1);
	}
	dup2(fd2, io);
	return (0);
}

int	open_folders(int ac, char **line, int f)
{
	int	st;
	int	i;

	st = 0;
	i = 0;
	while (i < ac && !st)
	{
		if (0 == ft_strcmp(line[i], "("))
			i += j_bracket(&line[i]);
		if ((2 < ac - i) && !ft_strcmp(line[i + 1], "<<"))
			st = open_heredoc(line[i], line[i + 2], f);
		else if ((2 < ac - i) && !ft_strcmp(line[i + 1], "<"))
			st = open_in(line[i], line[i + 2], f);
		else if ((2 < ac - i) && !ft_strcmp(line[i + 1], ">>"))
			st = open_appendout(line[i], line[i + 2], f);
		else if ((2 < ac - i) && !ft_strcmp(line[i + 1], ">"))
			st = open_out(line[i], line[i + 2], f);
		else
		{
			i++;
			continue ;
		}
		i += 3;
	}
	return (st);
}
