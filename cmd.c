/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:34:27 by ysay              #+#    #+#             */
/*   Updated: 2022/03/29 22:52:06 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**find_cmd(int ac, char **line)
{
	char	**ret;
	int		k;
	int		i;

	i = 0;
	k = 0;
	ret = copy_arg(NULL);
	while (i < ac)
	{
		if (i >= k)
			k = j_bracket(&line[i]) + i;
		if ((2 < ac - i) && i >= k
			&& (!ft_strcmp(line[i + 1], "<<") || !ft_strcmp(line[i + 1], "<")
				|| !ft_strcmp(line[i + 1], ">>")
				|| !ft_strcmp(line[i + 1], ">")))
			i += 3;
		else
			add_str_newarg(&ret, line[i++]);
	}
	if (!ret || !*ret)
	{
		kill_arg(ret);
		ret = NULL;
	}
	return (ret);
}

int	is_group(char **arg, int trim)
{
	int	i;

	i = arg_len(arg);
	if (0 != ft_strcmp(arg[0], "(") || 0 != ft_strcmp(arg[i - 1], ")"))
		return (0);
	if (!trim)
		return (1);
	dell_str(arg, i - 1);
	dell_str(arg, 0);
	return (1);
}

int	split_cmd(char **arg, int ac)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (0 == ft_strcmp(arg[i], "("))
			i += j_bracket(&arg[i]);
		if (0 == ft_strcmp(arg[i], "|"))
			return (i);
		i++;
	}
	return (i);
}

char	*get_host(void)
{
	int		i;
	char	**arg;
	char	*str;
	char	*tmp;

	str = my_str3join("hostname>", my_getenv("HOME", g_e->env), "/.shell.tmp");
	arg = my_tok(str);
	free(str);
	str = ft_strjoin(my_getenv("HOME", g_e->env), "/.shell.tmp");
	run_group(arg_len(arg), arg, g_e);
	kill_arg(arg);
	i = open(str, 0);
	free(str);
	if (0 > i)
		return (ft_strdup("unkown_pc"));
	tmp = get_next_line(i);
	str = ft_strtrim(tmp, " \n");
	free(tmp);
	return (str);
}

int	give_new_cmd(char ***ag, int *ac, char ***nag, int *nac)
{
	int		i;
	int		k;
	char	**arg;

	arg = *ag;
	i = 0;
	k = 0;
	while (i < *ac && !k)
	{
		if (0 == ft_strcmp(arg[i], "("))
			i += j_bracket(&arg[i]);
		if (arg[i + 1] && 0 == ft_strcmp(arg[i + 1], "||"))
			k = 1;
		if (arg[i + 1] && 0 == ft_strcmp(arg[i + 1], "&&"))
			k = 1;
		i++;
	}
	(*ac) -= i + k;
	*nac = i;
	*nag = *ag;
	*ag = &arg[i + k];
	if (k && 0 == ft_strcmp(arg[i], "||"))
		return (1);
	else
		return (0);
}
