/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:20:37 by ysay              #+#    #+#             */
/*   Updated: 2022/04/03 16:01:14 by akarahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ret_val(char *cmd, char **arg)
{
	int		i;
	char	**ret;
	int		sz;

	sz = 0;
	while (arg[sz])
		sz++;
	ret = (char **)malloc(sizeof(char *) * (sz + 2));
	ret[sz + 1] = NULL;
	ret[0] = ft_strdup(cmd);
	i = 0;
	while (i < sz)
	{
		ret[i + 1] = ft_strdup(arg[i]);
		i++;
	}
	free(cmd);
	return (ret);
}

int	in_path(char *cmd, char **path, char **arg, char ***ret)
{
	char		*pcmd;
	int			i;
	int			f;
	struct stat	st;

	(void)path;
	(void)cmd;
	f = 0;
	pcmd = ft_strdup(*arg);
	if (access(pcmd, X_OK) == 0)
		f = 1;
	i = 0;
	if (!f)
	{
		i = 127;
		my_perror("bash", *arg, "command not found", 0);
	}
	if (f && 0 == stat(pcmd, &st) && st.st_mode & S_IFDIR)
	{
		i = 126;
		my_perror("bash", *arg, NULL, EISDIR);
	}
	if (f && !(st.st_mode & S_IFDIR))
		*ret = ret_val(pcmd, arg);
	return (i);
}

int	give_path(char *cmd, char **path, char **arg, char ***ret)
{
	char		*pcmd;
	int			i;
	int			f;
	struct stat	st;

	if (ft_strnstr(*arg, "./", 2) || ft_strnstr(*arg, "/", 1))
		return (in_path(cmd, path, arg, ret));
	i = 0;
	f = 0;
	pcmd = ft_strdup("");
	while (!f && path[i])
	{
		free(pcmd);
		pcmd = ft_strjoin(path[i++], cmd);
		if (access(pcmd, X_OK) == 0)
			f = 1;
	}
	if (!f)
		return (my_perror("bash", *arg, "command not found", 0) + 127);
	if (f && 0 == stat(pcmd, &st) && st.st_mode & S_IFDIR)
		return (my_perror("bash", *arg, NULL, EISDIR) + 126);
	if (f && !(st.st_mode & S_IFDIR))
		*ret = ret_val(pcmd, arg);
	return (0);
}

int	give_arg(char **str, t_my_env *e, char ***ret)
{
	char	**path;
	char	*cmd;
	int		i;

	i = 0;
	path = ft_split(my_getenv("PATH", e->env), ':');
	if (!path)
		return (my_perror("bash", *str, "No such file or directory", 0) + 127);
	cmd = ft_strjoin("/", *str);
	i = give_path(cmd, path, str, ret);
	free(cmd);
	kill_arg(path);
	if (i)
		return (i);
	my_chenv("_", e->env, **ret);
	return (0);
}
