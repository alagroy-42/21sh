/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:01:05 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/01 16:56:05 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <fcntl.h>

int		ft_less(t_redir *redir)
{
	int		fd;

	if ((fd = open(redir->target, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "21sh: %s: no such file or directory\n", redir->target);
		return (0);
	}
	if (redir->fd == -42)
		redir->fd = 0;
	dup2(fd, redir->fd);
	close(fd);
	return (1);
}

int		ft_dless(t_redir *redir)
{
	int		fd;
	int		i;

	if ((fd = open("/tmp/heredoc_21sh", O_CREAT | O_WRONLY | O_TRUNC, 0644))
			== -1)
		return (0);
	i = -1;
	while (redir->heredoc && redir->heredoc[++i])
		ft_putstr_fd(redir->heredoc[i], fd);
	close(fd);
	if ((fd = open("/tmp/heredoc_21sh", O_RDONLY)) == -1)
		return (0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}
