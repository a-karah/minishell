/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:50:12 by ysay              #+#    #+#             */
/*   Updated: 2022/03/31 17:27:59 by akarahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <newshell.h>

void	sig_in(int sig_num)
{
	if (sig_num == SIGINT)
	{
		if (g_e->st.c_pid)
		{
			waitpid(g_e->st.c_pid, &g_e->st.st, 0);
		}
		if (!g_e->st.c_pid && !g_e->st.pf)
			exit(0);
		g_e->st.st = 33280;
	}	
}

void	sig_in2(int sig_num)
{
	char	*hostname;
	char	*prompt;

	hostname = get_host();
	prompt = create_prompt(g_e, hostname);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	ft_printf("\n%s", prompt);
	free(hostname);
	free(prompt);
	prompt = ft_itoa(130);
	my_chenv("LASTRET", g_e->env, prompt);
	free(prompt);
	(void)sig_num;
}

void	sig_in3(int sig_num)
{
	char	*prompt;

	g_e->st.sig = 1;
	close(0);
	ft_printf("\n");
	prompt = ft_itoa(130);
	my_chenv("LASTRET", g_e->env, prompt);
	free(prompt);
	(void)sig_num;
}
