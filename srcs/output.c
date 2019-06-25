/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:53:28 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/25 23:51:11 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <fcntl.h>

void	ft_dgreat(t_redir *redir)
{
	if ((redir->fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644))
			== -1)
		return ;
	dup2(redir->fd, STDOUT_FILENO);
}

void	ft_great(t_redir *redir)
{
	if ((redir->fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644))
			== -1)
		return ;
	dup2(redir->fd, STDOUT_FILENO);
}
