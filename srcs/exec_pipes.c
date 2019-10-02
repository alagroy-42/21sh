/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:12:24 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/02 13:50:48 by alagroy-         ###   ########.fr       */
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


void	exec_ast_pipes(t_ast **ast, int size, char **envp)
{
	int **fds;
	int pid;
	int last_read_fd;
	int i;
	int j;

	fds = malloc(sizeof(int*) * size);
	i = 0;
	while (i < size)
	{
		fds[i] = malloc(sizeof(int) * 2);
		pipe(fds[i]);
		i++;
	}
	last_read_fd = 0;
	i = 0;
	while (i < size)
	{
		pid = fork();
		g_lastpid = pid;
		if (!pid)
		{
			g_ischild = 1;
			dup2(last_read_fd, 0);
			if (i != size - 1)
				dup2(fds[i][1], 1);
			j = 0;
			while (j < size)
			{
				close(fds[j][0]);
				close(fds[j][1]);
				j++;
			}
			close(fds[i][0]);
			exec_ast_child(ast_get_index(*ast, i), envp);
			exit(1);
		}
		else
		{
			close(fds[i][1]);
			if (last_read_fd)
				close(last_read_fd);
			last_read_fd = fds[i][0];
		}
		i++;
	}
	i = -1;
	while (++i < size)
		free(fds[i]);
	free(fds);
	ast_pipes_end(ast);
	while (wait(&(*ast)->status) != -1)
		continue;
}
