/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:12:24 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/20 16:52:24 by pcharrie         ###   ########.fr       */
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
extern int	g_lastpid;
extern int	g_status;
extern int	**g_fds;
int			g_last_read_fd;

int		ast_pipes_size(t_ast *ast)
{
	int i;

	i = 0;
	while (ast)
	{
		i++;
		ast = ast->pipe;
	}
	return (i);
}

t_ast	*ast_get_index(t_ast *ast, int index)
{
	int i;

	i = 0;
	while (ast)
	{
		if (i == index)
			return (ast);
		i++;
		ast = ast->pipe;
	}
	return (NULL);
}

void	exec_ast_pipes_closefds(int size)
{
	int j;

	j = -1;
	while (++j < size)
	{
		close(g_fds[j][0]);
		close(g_fds[j][1]);
	}
}

void	exec_ast_pipes_fork(t_ast **ast, int i, char **envp, int size)
{
	int pid;

	pid = fork();
	g_lastpid = pid;
	if (!pid)
	{
		dup2(g_last_read_fd, 0);
		if (i != size - 1)
			dup2(g_fds[i][1], 1);
		exec_ast_pipes_closefds(size);
		close(g_fds[i][0]);
		exec_ast_child(ast_get_index(*ast, i), envp);
	}
	else if (pid != -1)
	{
		if (ast_get_index(*ast, i))
			ast_get_index(*ast, i)->pid = pid;
		close(g_fds[i][1]);
		if (g_last_read_fd)
			close(g_last_read_fd);
		g_last_read_fd = g_fds[i][0];
	}
}

void	exec_ast_pipes(t_ast **ast, int size, char **envp)
{
	int i;
	int pid;
	int status;

	if (!(exec_gfds_malloc(size)))
		return ;
	g_last_read_fd = 0;
	i = 0;
	while (i < size)
	{
		exec_ast_pipes_fork(ast, i, envp, size);
		i++;
	}
	i = -1;
	while ((pid = wait(&status)) != -1)
		exec_wait_set_status(*ast, pid, status);
	ast_pipes_end(ast);
	g_status = (*ast)->status;
	exec_ast_pipes_closefds(size);
	exec_gfds_free(size);
}
