/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 22:01:05 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/25 22:54:28 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <fcntl.h>

void	ft_less(t_redir *redir)
{
	int		fd;

	if ((fd = open(redir->target, O_RDONLY)) == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}
