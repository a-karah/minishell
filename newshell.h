/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:45:05 by akarahan          #+#    #+#             */
/*   Updated: 2022/04/01 22:50:48 by akarahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEWSHELL_H
# define NEWSHELL_H

# include <dirent.h>
# include <stdarg.h>
# include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_dir
{
	DIR				*o_dir;
	struct dirent	*r_dir;
}				t_dir;

typedef struct s_wcard
{
	int		len;
	t_dir	*dir;
	char	*pre;
	char	*post;
}				t_wcard;

typedef struct s_doll
{
	char	*get_env;
	char	*pre;
	char	*post;
}				t_doll;

/* utils.c */
char	*create_prompt(t_my_env *e, char *hostname);
char	*join_split(char **s);
void	ft_print2d(char **s);
void	free_doll(t_doll *doll);
int		check_dollar_in_dquote(char *s);

/* wildcard.c */
char	**wildcard(char *path, char *s);
char	**my_split_wildcard(char **arg);

/* wildcard_utils.c */
int		handle_dir_error(char *path);
int		count_dir(char *path, char *s, char *pre, char *post);

/* dollar.c */
void	my_split_dollar(char **arg, char **env);

/* syntax.c */
int		print_error(char *arg, char *s);
int		check_syntax(char **arg);
int		check_folder(char **arg);
int		check(char **arg);

#endif