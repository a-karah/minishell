/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:18:51 by ysay              #+#    #+#             */
/*   Updated: 2022/03/31 17:22:23 by akarahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <newshell.h>

t_my_env	*g_e;

void	free_me(char *cmd, char *dt, char *prompt)
{
	free(cmd);
	free(dt);
	free(prompt);
}

void	exec_loop(t_my_env *e, char *hostname)
{
	char	**vv;
	char	*prompt;
	char	*dt;
	char	*cmd;

	while (1)
	{
		e->st.sig = 0;
		prompt = create_prompt(e, hostname);
		dt = readline(prompt);
		if (!dt)
			break ;
		cmd = ft_strtrim(dt, " \n");
		if (*cmd)
		{
			add_history(cmd);
			vv = my_tok(cmd);
			if (vv && !e->st.sig)
				run_group(arg_len(vv), vv, e);
			if (vv)
				kill_arg(vv);
		}
		free_me(cmd, dt, prompt);
	}
	free(prompt);
}

int	main(int ac, char **ag, char **env)
{
	char		*hostname;
	t_my_env	*e;

	(void)ac;
	(void)ag;
	signal(SIGQUIT, SIG_IGN);
	g_e = init_env(env);
	e = g_e;
	signal(SIGINT, sig_in2);
	hostname = get_host();
	exec_loop(e, hostname);
	kill_arg(e->env);
	kill_arg(e->exp);
	free(e);
	return (0);
}
