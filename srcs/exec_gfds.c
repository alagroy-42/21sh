/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_gfds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:40:36 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/09 15:45:24 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

extern int	**g_fds;

void	exec_gfds_free(int size)
{
	int i;

	i = 0;
	while (i < size)
		free(g_fds[i++]);
	free(g_fds);
}

int		exec_gfds_malloc(int size)
{
	int i;

	if (!(g_fds = malloc(sizeof(int*) * size)))
		return (0);
	i = 0;
	while (i < size)
	{
		if (!(g_fds[i] = malloc(sizeof(int) * 2)))
		{
			exec_gfds_free(i);
			return (0);
		}
		pipe(g_fds[i]);
		i++;
	}
	return (1);
}
