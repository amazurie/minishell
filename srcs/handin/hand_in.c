/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 12:16:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/07 12:28:56 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		inni(t_data **d, char *tmp, int **i)
{
	(*d)->i = *i;
	get_data(*d);
	read(0, tmp, LIMIT_LINE);
	if (is_siginted(0) == 1)
		sig_reset(d, i);
	if (completion(d, &tmp, i) == -1)
		return ;
	if (is_siginted(0) == 1 && (tmp[0] != 4 || tmp[1]))
		sig_reset(d, i);
	ft_putstr_fd(tgetstr("vi", NULL), 0);
	if (gest_in(d, tmp, i) == -1)
		(*i)[0] = -1;
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	ft_bzero(tmp, ft_strlen(tmp));
}

int			in(t_data **d, char *tmp)
{
	int		*i;
	int		j;

	is_siginted(1);
	if ((i = (int *)ft_memalloc(sizeof(int) * 7)) == NULL)
		return (print_error("allocation error") - 1);
	if (read(0, tmp, 0) == -1)
		return (-1);
	i[6] = 0;
	while (i[0] == 0)
		inni(d, tmp, &i);
	j = i[0];
	ft_putchar_fd('\n', 0);
	free(i);
	return (j);
}
