/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 12:57:30 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/25 11:16:40 by alagroy-         ###   ########.fr       */
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

	if (!(home = env_get(g_env, "HOME")))
		return ;
	if (!(path = ft_strjoin(home->value, "/.21shrc")))
		return ;
	if ((fd = open(path, O_RDONLY | O_NOFOLLOW)) == -1)
		return (ft_strdel(&path));
	ft_strdel(&path);
	while (gnl_nl(fd, &line->line) == 1)
		core(line);
	close(fd);
}

void	exec_file(int ac, char **av, t_line *line)
{
	int		i;
	int		fd;

	i = 0;
	while (++i < ac)
	{
		if ((fd = open(av[i], O_RDONLY | O_NOFOLLOW)) == -1)
			exit(EXIT_FAILURE);
		while (get_next_line(fd, &line->line) == 1)
			core(line);
		close(fd);
	}
	exit(EXIT_SUCCESS);
}
