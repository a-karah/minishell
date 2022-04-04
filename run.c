/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:46:39 by ysay              #+#    #+#             */
/*   Updated: 2022/03/29 10:14:47 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	fork_process(int ac, char **ag, t_my_env *e, int p)
{
	int	pid;
	int	io[2];

	e->st.st = 0;
	pipe(io);
	pid = fork();
	if (pid == 0)
	{
		e->st.c_pid = 0;
		e->st.s_pid = 0;
		e->st.pf = 0;
		close(io[0]);
		if (p)
			dup2(io[1], 1);
		exit(init_process(ac, ag, e, 0));
	}
	close(io[1]);
	if (p)
	{	
		dup2(io[0], 0);
		e->st.s_pipe = io[0];
	}
	return (pid);
}

int	init_process(int ac, char **line, t_my_env *e, int f)
{
	int		err_f;
	int		i;

	i = 2;
	err_f = split_cmd(line, ac);
	if (err_f != ac && !ft_strcmp(line[err_f], "|"))
	{
		e->st.c_pid = fork_process(err_f, line, e, 1);
		e->st.s_pid = fork_process(ac - err_f -1, &line[err_f + 1], e, 0);
		err_f = 0;
		close (0);
		while (i--)
		{
			if (e->st.s_pid == waitpid(-1, &err_f, 0))
			{
				e->st.st = err_f;
				close(e->st.s_pipe);
			}
		}		
		return (e->st.st >> 8);
	}
	line = get_ready(line, ac, e);
	err_f = run_process(line, e, f);
	kill_arg(line);
	return (err_f);
}

int	run_process(char **line, t_my_env *e, int f)
{
	int		flag;
	int		err_f;
	char	**arg;
	char	**data;

	err_f = open_folders(arg_len(line), line, f);
	if (err_f)
		return (err_f);
	data = find_cmd(arg_len(line), line);
	if (!data)
		return (0);
	if (is_group(data, 1))
	{
		err_f = run_group(arg_len(data), data, e);
		kill_arg(data);
		return (err_f);
	}
	flag = is_buildin(data, e);
	if (flag)
		return (buildin(data, e, f));
	err_f = give_arg(data, e, &arg);
	if (err_f)
		return (err_f);
	execve(arg[0], &arg[1], e->env);
	return (0);
}

int	command_section(int ac, char **arg, t_my_env *e)
{
	char	*ret_val;
	int		st;

	st = 0;
	e->st.c_pid = fork_process(ac, arg, e, 0);
	waitpid(e->st.c_pid, &e->st.st, 0);
	e->st.c_pid = 0;
	st = e->st.st >> 8;
	if (is_mainin(ac, arg))
		init_process(ac, arg, e, 1);
	ret_val = ft_itoa(st);
	my_chenv("LASTRET", e->env, ret_val);
	free(ret_val);
	return (st);
}

int	run_group(int ac, char **ag, t_my_env *e)
{
	int		st;
	int		p_ac;
	char	**p_arg;
	int		logic;

	p_ac = 0;
	p_arg = NULL;
	st = 0;
	logic = 0;
	signal(SIGINT, sig_in);
	while (ac && st != 130)
	{
		if (logic ^ (st != 0))
		{
			logic = give_new_cmd(&ag, &ac, &p_arg, &p_ac);
			continue ;
		}
		logic = give_new_cmd(&ag, &ac, &p_arg, &p_ac);
		st = command_section(p_ac, p_arg, e);
	}
	signal(SIGINT, sig_in2);
	return (st);
}
