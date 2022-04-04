/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:43:38 by akarahan          #+#    #+#             */
/*   Updated: 2022/03/31 12:08:25 by akarahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "newshell.h"

void	copy_dir(t_dir *dir, t_wcard *wc, char *s, char **out)
{
	struct dirent	*r_dir;
	char			**tmp;
	char			*found;

	r_dir = readdir(dir->o_dir);
	tmp = out;
	while (r_dir)
	{
		found = ft_strnstr(r_dir->d_name, wc->post, 1024);
		if (wc->pre && wc->post && *r_dir->d_name == *wc->pre
			&& ft_strnstr(r_dir->d_name, wc->pre, 1024) && found)
			*tmp++ = ft_strdup(r_dir->d_name);
		else if (wc->pre && !wc->post
			&& ft_strnstr(r_dir->d_name, wc->pre, 1024))
			*tmp++ = ft_strdup(r_dir->d_name);
		else if (!wc->pre && wc->post && found
			&& ft_strcmp(found, wc->post) == 0)
			*tmp++ = ft_strdup(r_dir->d_name);
		else if (*s == '*' && *(s + 1) == 0 && *r_dir->d_name != '.'
			&& !ft_strnstr(r_dir->d_name, "..", 1024))
			*tmp++ = ft_strdup(r_dir->d_name);
		r_dir = readdir(dir->o_dir);
	}
	*tmp = NULL;
}

char	**wildcard(char *path, char *s)
{
	char	**out;
	t_dir	dir;
	t_wcard	wc;
	int		i;

	i = 0;
	wc.pre = NULL;
	wc.post = NULL;
	while (s[i] != '*')
		++i;
	if (i)
		wc.pre = ft_substr(s, 0, i);
	wc.post = ft_strdup(s + i + 1);
	wc.len = count_dir(path, s, wc.pre, wc.post);
	out = (char **)malloc(sizeof(char *) * (wc.len + 1));
	if (!out)
		return (NULL);
	if (wc.len == -1)
		return (NULL);
	dir.o_dir = opendir(path);
	copy_dir(&dir, &wc, s, out);
	closedir(dir.o_dir);
	return (out);
}

char	**copy_after(char **arg, int i)
{
	char	**new;
	int		j;

	j = 0;
	while (arg[i + j])
		++j;
	new = (char **)malloc(sizeof(char *) * (j + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (arg[i])
	{
		new[j] = ft_strdup(arg[i]);
		++i;
		++j;
	}
	new[j] = NULL;
	return (new);
}

char	**prepare_ret(char **arg, int *i)
{
	char	**found;
	char	**post;
	char	**ret;
	int		j;

	j = -1;
	found = wildcard("./", arg[*i]);
	post = copy_after(arg, *i + 1);
	ret = copy_arg(arg);
	if (!*found)
		return (ret);
	while (ret[*i])
		dell_str(ret, *i);
	while (found[++j])
		add_str_newarg(&ret, found[j]);
	if (post && *post)
	{
		j = -1;
		while (post[++j])
			add_str_newarg(&ret, post[j]);
		kill_arg(post);
		++j;
	}
	*i += j - 1;
	return (ret);
}

char	**my_split_wildcard(char **arg)
{
	char	**ret;
	char	**tmp;
	int		i;

	i = 0;
	ret = copy_arg(arg);
	while (ret[i])
	{
		if (!ft_strcmp(ret[i], "("))
			i += j_bracket(ret);
		if (ft_strchr(ret[i], '*'))
		{
			tmp = ret;
			ret = prepare_ret(ret, &i);
			kill_arg(tmp);
		}
		++i;
	}
	return (ret);
}
