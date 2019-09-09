/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 12:57:30 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/09 15:17:57 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
