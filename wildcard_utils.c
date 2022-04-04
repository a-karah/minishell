/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:33:50 by akarahan          #+#    #+#             */
/*   Updated: 2022/03/29 22:33:59 by akarahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "newshell.h"

int	handle_dir_error(char *path)
{
	printf("Cannot open directory %s\n", path);
	return (-1);
}

int	count_dir(char *path, char *s, char *pre, char *post)
{
	struct dirent	*r_dir;
	DIR				*o_dir;
	char			*found;
	int				count;

	count = 0;
	o_dir = opendir(path);
	if (o_dir == NULL)
		return (handle_dir_error(path));
	r_dir = readdir(o_dir);
	while (r_dir)
	{
		found = ft_strnstr(r_dir->d_name, post, 1024);
		if ((pre && post && *r_dir->d_name == *pre
				&& ft_strnstr(r_dir->d_name, pre, 1024) && found)
			|| (pre && !post && ft_strnstr(r_dir->d_name, pre, 1024))
			|| (!pre && post && found && ft_strcmp(found, post) == 0)
			|| (*s == '*' && *(s + 1) == 0 && *r_dir->d_name != '.'
				&& !ft_strnstr(r_dir->d_name, "..", 1024)))
			++count;
		r_dir = readdir(o_dir);
	}
	closedir(o_dir);
	return (count);
}
