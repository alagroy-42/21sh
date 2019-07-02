/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:01:05 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/02 21:59:04 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <fcntl.h>

void	ft_less(t_redir *redir)
{
	int		fd;

	if ((fd = open(redir->target, O_RDONLY)) == -1)
		return ;
	if (redir->fd == -42)
		redir->fd = 0;
	dup2(fd, redir->fd);
	close(fd);
}

void	ft_dless(t_redir *redir)
{
	int		fd;
	int		i;

	if ((fd = open("/tmp/heredoc_21sh", O_CREAT | O_WRONLY | O_TRUNC, 0644))
			== -1)
		return ;
	i = -1;
	while (redir->heredoc[++i])
		ft_putendl_fd(redir->heredoc[i], fd);
	close(fd);
	if ((fd = open("/tmp/heredoc_21sh", O_RDONLY)) == -1)
		return ;
	unlink("/tmp/heredoc_21sh");
	dup2(fd, STDIN_FILENO);
	close(fd);
}
