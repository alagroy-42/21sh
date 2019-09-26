/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/26 19:17:37 by pcharrie         ###   ########.fr       */
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

extern t_env	*g_env;
int				g_status = 0;
int				g_lastpid = 42424242;
int				g_ischild = 0;

int g_pipefds[2];
int g_lastpipefd;

int		exec_builtin(t_ast *ast)
{
	if (!ft_strcmp(ast->cmd, "exit") || !ft_strcmp(ast->cmd, "quit"))
		builtin_exit(ast);
	else if (!ft_strcmp(ast->cmd, "env"))
		builtin_env(ast, g_env);
	else if (!ft_strcmp(ast->cmd, "cd"))
		builtin_cd(ast, g_env);
	else if (!ft_strcmp(ast->cmd, "echo"))
		builtin_echo(ast);
	else if (!ft_strcmp(ast->cmd, "setenv"))
		builtin_setenv(ast, g_env);
	else if (!ft_strcmp(ast->cmd, "unsetenv"))
		builtin_unsetenv(ast, &g_env);
	else
		return (0);
	return (1);
}

void	exec_error(t_ast *ast)
{
	if (!ast->error)
		return ;
	ft_putstr_fd(ast->cmd, 2);
	ft_putstr_fd(": ", 2);
	if (ast->error == 1)
		ft_putstr_fd("no such file or directory", 2);
	else if (ast->error == 2)
		ft_putstr_fd("permission denied", 2);
	else if (ast->error == 3)
		ft_putstr_fd("command not found", 2);
	ft_putstr_fd("\n", 2);
}

void	exec_ast_child(t_ast *ast)
{
	char	**envp;

	if (!(envp = env_toenvp(g_env, 0, 0, 0)))
		return ;
	if (!ft_redir_router(ast->redir))
		exit(EXIT_FAILURE);
	if (!ast->path)
		exec_builtin(ast);
	else
		execve(ast->path, ast->args, envp);
	exit(1);
}


int		ast_pipe_size(t_ast *ast)
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

void	exec_ast_single(t_ast *ast)
{
	int pid;

	pid = fork();
	if (!pid)
		exec_ast_child(ast);
	else if (pid == -1)
		ft_putstr_fd("fork error", 2);
	else
	{
		waitpid(pid, &ast->status, 0);
		g_status = WIFSIGNALED(ast->status) ?
			child_crash(ast->status, ast) : WEXITSTATUS(ast->status);
	}
}

void	exec_ast_pipes(t_ast **ast, int size)
{
	int **fds;
	int pid;
	int last_read_fd;
	int i;
	int j;
	t_ast *tmp;

	tmp = *ast;
	while (tmp)
	{
		if (tmp->error)
		{
			exec_error(tmp);
			while ((*ast)->pipe)
				*ast = (*ast)->pipe;
			(*ast)->status = -1;
			return ;
		}
		tmp = tmp->pipe;
	}
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
			exec_ast_child(ast_get_index(*ast, i));
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
	while (*ast)
	{
		if ((*ast)->pipe)
			*ast = (*ast)->pipe;
		else
			break;
	}
	while (wait(&(*ast)->status) != -1)
		continue;
}

void	exec_ast_fork(t_ast **ast)
{
	int	ast_size;

	term_unsetup();
	ast_size = ast_pipe_size(*ast);
	if (ast_size == 1)
		exec_ast_single(*ast);
	else if (ast_size > 1)
		exec_ast_pipes(ast, ast_size);
	term_setup();
}

void	exec(t_ast *ast)
{
	ast_set(ast);
	while (ast)
	{
		expansions_handle(ast);
		if (ast->error)
			exec_error(ast);
		else if (ast->cmd)
		{
			if (!ast->pipe && !ft_strcmp(ast->cmd, "exit"))
				return (builtin_exit(ast));
			else if (is_cmd_builtin(ast->cmd) && !ast->pipe)
				exec_builtin(ast);
			else
				exec_ast_fork(&ast);
		}
		if (ast->sep)
		{
			if (ast->sep->sep == semicol
				|| (ast->sep->sep == and_if && ast->status == 0 && !ast->error)
				|| (ast->sep->sep == or_if && ast->status != 0))
			{
				ast = ast->sep->next;
			}
			else
				ast = NULL;
		}
		else
			ast = NULL;
	}
}
