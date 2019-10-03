/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 04:10:37 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/03 13:18:24 by pcharrie         ###   ########.fr       */
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

void	exec_error_put(t_ast *ast)
{
	if (!ast->error)
		return ;
	if (g_ischild && !ft_redir_router(ast->redir))
		exit(EXIT_FAILURE);
	ft_putstr_fd(ast->cmd, 2);
	ft_putstr_fd(": ", 2);
	if (ast->error == 1)
		ft_putstr_fd("no such file or directory\n", 2);
	else if (ast->error == 2)
		ft_putstr_fd("permission denied\n", 2);
	else if (ast->error == 3)
		ft_putstr_fd("command not found\n", 2);
	else
		ft_putstr_fd("unknown error\n", 2);
}

int		exec_error(t_ast *ast)
{
	int pid;

	while (ast)
	{
		if (!ast->error)
		{
			ast = ast->pipe;
			continue ;
		}
		if (ast->pipe)
		{
			pid = fork();
			if (!pid)
			{
				g_ischild = 1;
				exec_error_put(ast);
			}
			else if (pid != -1)
				wait(NULL);
		}
		else
			exec_error_put(ast);
		return (1);
	}
	return (0);
}
