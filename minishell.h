/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysay <ysay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:59:49 by ysay              #+#    #+#             */
/*   Updated: 2022/04/03 12:12:53 by ysay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <stddef.h>
# include <fcntl.h>
# include <libft.h>
# include <signal.h>

typedef struct s_p_status
{
	int	pf;
	int	c_pid;
	int	s_pid;
	int	s_pipe;
	int	st;
	int	sig;
}	t_p_status;

typedef struct s_my_env
{
	char		**env;
	char		**exp;
	t_p_status	st;
}	t_my_env;

extern t_my_env	*g_e;

int			kill_arg(char **arg);
int			arg_len(char **arg);
char		*is_argin(char **arg, char *str);
int			give_index(char **arg, char *str);
int			dell_str(char **arg, int index);
char		**add_str(char **arg, char *s);
int			add_str_newarg(char ***arg, char *s);
char		**copy_arg(char **env);

char		*my_chenv(char *s, char	**env, char *new);
int			give_envindex(char **env, char *s);
char		*my_getenv(char	*s, char **env);
int			is_envin(char **env, char *item);
int			my_addexp(t_my_env *e, char *item);
int			my_addenv(t_my_env *e, char *item);
t_my_env	*init_env(char **env);

int			is_valid(char *item);
char		*join_and_free(char *s1, char *s2);
char		*my_str3join(char *s1, char *s2, char *s3);
int			my_perror(char *cmd, char *str, char *opt, int no);
int			print_error(char *arg, char *s);

int			echo(char **ag, t_my_env *e, int f);
int			cd(char **ag, t_my_env *e, int f);
int			pwd(char **ag, t_my_env *e, int f);
int			w_export(t_my_env *e, int f);
int			export(char **ag, t_my_env *e, int f);
int			unset(char **ag, t_my_env *e, int f);
int			envf(char **ag, t_my_env *e, int f);
int			exitf(char **ag, t_my_env *e, int f);
int			is_buildin(char **arg, t_my_env *e);
int			buildin(char **arg, t_my_env *e, int f);

int			is_mainin(int ac, char **arg);
char		**find_cmd(int ac, char **line);
int			is_group(char **arg, int trim);
int			split_cmd(char **arg, int ac);
char		*get_host(void);
int			give_new_cmd(char ***ag, int *ac, char ***nag, int *nac);

char		**ret_val(char *cmd, char **arg);
int			in_path(char *cmd, char **path, char **arg, char ***ret);
int			give_path(char *cmd, char **path, char **arg, char ***ret);
int			give_arg(char **str, t_my_env *e, char ***ret);

int			open_in(char *fd, char *file, int f);
int			open_heredoc(char *fd, char *str, int f);
int			open_appendout(char *fd, char *file, int f);
int			open_out(char *fd, char *file, int f);
int			open_folders(int ac, char **line, int f);

int			is_special(char *s);
int			is_operate(char *s);
int			look_logic(char ***ret, char *s);
char		**my_split_logic(char *s);

int			is_alln(char *s);
int			look_folder(char ***ret, char *s, char *str);
int			if_case_folder(int i, char *s);
char		**my_split_folder(char **arg);

int			j_squote(char *s);
int			j_dquote(char *s);
int			j_bracket(char **arg);
char		*join_quote(char **ss, char	*str);
char		**my_split_quote(char **arg);

char		**get_ready(char **arg, int ac, t_my_env *e);
void		take_heredoc(char **arg);
char		**my_tok(char *s);

void		sig_in(int sig_num);
void		sig_in2(int sig_num);
void		sig_in3(int sig_num);

int			check_syntax(char **arg);
int			is_folder_sing(char *s);
int			check_folder(char **arg);
int			check_p(char **arg);
int			check(char **arg);

int			init_process(int ac, char **line, t_my_env *e, int f);
int			fork_process(int ac, char **ag, t_my_env *e, int p);
int			run_process(char **line, t_my_env *e, int f);
int			command_section(int ac, char **arg, t_my_env *e);
int			run_group(int ac, char **ag, t_my_env *e);

#endif
