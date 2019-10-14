/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 04:10:37 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/10 15:16:09 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

extern int	g_ischild;

void	ast_pipes_end(t_ast **ast)
{
	while ((*ast)->pipe)
		*ast = (*ast)->pipe;
}

int		exec_error(t_ast *ast)
{
	if (!ast->error || (ast->error < 1 || ast->error > 4))
		return (0);
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(ast->cmd, 2);
	ft_putstr_fd(": ", 2);
	if (ast->error == 1)
		ft_putstr_fd("no such file or directory\n", 2);
	else if (ast->error == 2)
		ft_putstr_fd("permission denied\n", 2);
	else if (ast->error == 3)
		ft_putstr_fd("command not found\n", 2);
	else if (ast->error == 4)
		ft_putstr_fd("is a directory\n", 2);
	else
		ft_putstr_fd("unknown error\n", 2);
	return (1);
}
