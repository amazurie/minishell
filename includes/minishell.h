/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:53:03 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/08 15:42:09 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <sys/wait.h>
# include <termios.h>
# include <stdio.h>
# include <signal.h>

# define LIGHT_RED		"\e[1;31m"
# define DEFAULT		"\e[0m"
# define MAX_HISTORY	126

int SIGINTED;
int SIGSTOPED;

typedef struct	hist_list
{
	int					num;
	char				*hist;
	struct hist_list	*next;
}				h_list;

typedef struct	env_list
{
	char			*elem;
	char			*cont;
	struct env_list	*next;
}				e_list;

char			*get_elem(e_list *env, char *elem);
int				exec(e_list *env, char *line, h_list *hist);
e_list			*char_to_lst(char **env);
void			display_env(e_list *env, char *opt);
void			set_env(e_list **env, char *elem, char *cont);
void			unset_env(e_list **env, char *elem);
int				cd(char **path, e_list *env);
void			add_hist(h_list **lst, char *hist);
void			display_hist(h_list *hist);
int				disp_hist_next(h_list *lst, int **i, char **line);
int				disp_hist_prec(h_list *lst, int **i, char **line);
void			ssupprchr(char **s, int pos);
void			saddchr(char **s, char c, int pos);
char			**splitsemicolon(char *s);
void			handbackslash(char **s);
void			get_ch(char **tmp);
int				gest_arrow(char *tmp, h_list *hist, int **i, char **line);
int				in(h_list *hist, char **line);

#endif
