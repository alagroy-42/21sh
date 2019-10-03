/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:53:28 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/03 17:55:57 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <fcntl.h>

int		ft_greatand(t_redir *redir)
{
	if (redir->fd == -42)
		redir->fd = 1;
	if (!ft_strcmp(redir->target, "-"))
	{
		close(redir->fd);
		return (1);
	}
	if (ft_strlen(redir->target) == 1 && ft_isdigit(redir->target[0]))
	{
		if (dup2(redir->target[0] - '0', redir->fd) == -1 && ft_dprintf(2,
					"21sh: %d: bad file descriptor\n", redir->target[0] - '0'))
			return (0);
		return (1);
	}
	if ((redir->fd_target = open(redir->target,
					O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		return (0);
	if (dup2(redir->fd_target, redir->fd) == -1 && ft_dprintf(2,
				"21sh: %d: bad file descriptor\n", redir->fd_target))
		return (close(redir->fd_target));
	return (1);
}

int		ft_dgreat(t_redir *redir)
{
	if ((redir->fd_target = open(redir->target, O_CREAT | O_WRONLY | O_APPEND,
					0644)) == -1)
		return (0);
	if (redir->fd == -42)
		redir->fd = 1;
	dup2(redir->fd_target, redir->fd);
	return (1);
}

int		ft_great(t_redir *redir)
{
	if ((redir->fd_target = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC,
					0644)) == -1)
		return (0);
	if (redir->fd == -42)
		redir->fd = 1;
	dup2(redir->fd_target, redir->fd);
	return (1);
}
