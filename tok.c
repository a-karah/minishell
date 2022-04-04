/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:20:55 by ysay              #+#    #+#             */
/*   Updated: 2022/03/31 17:24:26 by akarahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <newshell.h>

void	take_heredoc(char **arg)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 0;
	while (arg && arg[i] && !g_e->st.sig)
	{
		if (0 == ft_strcmp(arg[i], "<<") && arg[i + 1])
		{
			str = ft_strdup("");
			while (!g_e->st.sig)
			{
				tmp = readline("> ");
				if (g_e->st.sig || !tmp || 0 == ft_strcmp(arg[i + 1], tmp))
					break ;
				tmp = join_and_free(tmp, ft_strdup("\n"));
				str = join_and_free(str, tmp);
			}
			if (tmp)
				free(tmp);
			free(arg[i + 1]);
			arg[1 + (i++)] = str;
		}
		i++;
	}
}

char	**get_ready(char **arg, int ac, t_my_env *e)
{
	char	**ret;
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (ac + 1));
	while (i < ac)
	{
		tmp[i] = ft_strdup(arg[i]);
		i++;
	}	
	tmp[i] = NULL;
	my_split_dollar(tmp, e->env);
	ret = my_split_wildcard(tmp);
	kill_arg(tmp);
	tmp = my_split_quote(ret);
	kill_arg(ret);
	return (tmp);
}

char	**my_tok(char *s)
{
	char	**ret;
	char	**tmp;
	int		fd;

	ret = my_split_logic(s);
	tmp = my_split_folder(ret);
	kill_arg(ret);
	if (check(tmp))
	{
		kill_arg(tmp);
		return (NULL);
	}
	fd = dup(0);
	signal(SIGINT, sig_in3);
	take_heredoc(tmp);
	signal(SIGINT, sig_in2);
	dup2(fd, 0);
	close(fd);
	return (tmp);
}
