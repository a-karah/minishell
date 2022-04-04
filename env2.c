/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:19:45 by ysay              #+#    #+#             */
/*   Updated: 2022/03/28 14:46:50 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	my_addenv(t_my_env *e, char *item)
{
	int		f;
	char	*tmp;

	tmp = ft_strchr(item, '=');
	tmp = ft_substr(item, 0, ft_strlen(item) - ft_strlen(tmp));
	f = is_envin(e->env, item);
	if (f == 0)
	{
		add_str_newarg(&e->env, item);
		dell_str(e->exp, give_index(e->exp, tmp));
	}
	if (f == 1)
	{
		my_chenv(tmp, e->env, ft_strchr(item, '=') + 1);
		f = 0;
	}
	if (f == -1)
		my_addexp(e, item);
	free(tmp);
	return (f);
}

t_my_env	*init_env(char **env)
{
	char		*pwd;
	t_my_env	*e;

	e = malloc(sizeof(t_my_env));
	e->env = copy_arg(env);
	e->exp = copy_arg(NULL);
	pwd = ft_strjoin("OLDPWD=", my_getenv("PWD", e->env));
	if (!is_envin(e->env, pwd))
		my_addenv(e, pwd);
	if (!is_envin(e->env, "LASTRET=0"))
		my_addenv(e, "LASTRET=0");
	free(pwd);
	e->st.pf = 1;
	e->st.c_pid = 0;
	return (e);
}
