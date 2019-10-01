/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 12:57:30 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/01 13:16:43 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "env.h"

extern t_env	*g_env;

void	load_21shrc(t_line *line)
{
	t_env	*home;
	char	*path;
	int		fd;

	g_filemode = 1;
	if (!(home = env_get(g_env, "HOME")))
	{
		g_filemode = 0;
		return ;
	}
	if (!(path = ft_strjoin(home->value, "/.21shrc")))
	{
		g_filemode = 0;
		return ;
	}
	if ((fd = open(path, O_RDONLY | O_NOFOLLOW)) == -1)
	{
		g_filemode = 0;
		return (ft_strdel(&path));
	}
	line->curr_fd = fd;
	ft_strdel(&path);
	while (gnl_nl(fd, &line->line) == 1)
		core(line);
	close(fd);
	g_filemode = 0;
}

void	exec_file(int ac, char **av, t_line *line)
{
	int		i;
	int		fd;

	i = 0;
	g_filemode = 1;
	while (++i < ac)
	{
		if ((fd = open(av[i], O_RDONLY | O_NOFOLLOW)) == -1)
			exit(EXIT_FAILURE);
		line->curr_fd = fd;
		while (get_next_line(fd, &line->line) == 1)
			core(line);
		close(fd);
	}
	exit(EXIT_SUCCESS);
}
