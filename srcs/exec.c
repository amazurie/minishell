/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:28:15 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 11:49:25 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <curses.h>
#include <term.h>

static void	fork_exec(char **lstav, char **fullpaths, t_env **env)
{
	pid_t	pid;
	size_t	i;
	size_t	j;
	char	*tmp;

	while ((pid = fork()) == -1)
		sleep(2);
	i = 0;
	j = 0;
	if (pid > 0)
		wait(0);
	else
		while (fullpaths[i])
			if (execve(fullpaths[i++], lstav, NULL) != -1)
				j++;
	tmp = test_absolute(lstav[0]);
	if (j < i && execve(tmp, lstav, NULL) == -1)
	{
		ft_putstr_fd("\e[31mminishell:\e[0m command not found: ", 2);
		ft_putstr_fd(lstav[0], 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	free(tmp);
}

static void		exec2(char **lstav, char **paths, char **fullpaths, t_env **env)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (paths[i])
		i++;
	fullpaths = (char **)ft_memalloc(sizeof(char *) * i + 1);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		fullpaths[i++] = ft_strjoin(tmp, lstav[0]);
		free(tmp);
	}
	fork_exec(lstav, fullpaths, env);
	i = 0;
	while (paths[i])
		free(fullpaths[i++]);
	free(fullpaths);
}

int			exec(t_env **env, char *line, t_hist *hist)
{
	char	**lstav;
	char	**paths;
	char	**fullpaths;
	int		i;

	handbackslash(&line);
	lstav = ft_strsplit(line, ' ');
	line = get_elem(*env, "PATH");
	paths = ft_strsplit(line, ':');
	if ((i = built_in(env, lstav, hist)))
	{
		free_tab(paths);
		free_tab(lstav);
	}
	if (!*env && i == 0)
		ft_putstr_fd("\e[31mNo environnement defined.\e[0m\n", 2);
	if (i || !test_paths(paths) || !*env)
		return (i);
	exec2(lstav, paths, fullpaths, env);
	free_tab(paths);
	free_tab(lstav);
	return (0);
}
