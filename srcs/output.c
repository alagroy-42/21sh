/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:53:28 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/19 14:21:58 by alagroy-         ###   ########.fr       */
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
		return (0);
	}
	ft_printf("|%s|\n", redir->target);
	if (ft_strlen(redir->target) == 1 && ft_isdigit(redir->target[0]))
	{
		dup2(redir->target[0] - '0', redir->fd);
		return (0);
	}
	if ((redir->fd_target = open(redir->target,
					O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		return (0);
	dup2(redir->fd_target, redir->fd);
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
