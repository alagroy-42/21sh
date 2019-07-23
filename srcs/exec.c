/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/07/23 16:49:49 by pcharrie         ###   ########.fr       */
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

extern t_env *g_env;

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

void	exec_ast_child(t_ast **ast, int lastfd, int pipefds[2])
{
	char	**envp;

	if (!(envp = env_toenvp(g_env)))
		return ;
	if (!ft_redir_router((*ast)->redir))
		exit(EXIT_FAILURE);
	dup2(lastfd, 0);
	if ((*ast)->pipe != NULL)
		dup2(pipefds[1], 1);
	close(pipefds[0]);
	if ((*ast)->error)
		exec_error(*ast);
	else if (!(*ast)->path)
		exec_builtin(*ast);
	else
		execve((*ast)->path, (*ast)->args, envp);
	exit(1);
}

void	exec_ast(t_ast **ast)
{
	int		pid;

	g_lastpipefd = 0;
	while (*ast)
	{
		term_unsetup();
		pipe(g_pipefds);
		pid = fork();
		if (!pid)
			exec_ast_child(ast, g_lastpipefd, g_pipefds);
		else if (pid != -1)
		{
			waitpid(pid, &(*ast)->status, 0);
			close(g_pipefds[1]);
			if (g_lastpipefd)
				close(g_lastpipefd);
			g_lastpipefd = g_pipefds[0];
			if (!(*ast)->pipe && close(g_lastpipefd) < 1)
				return (term_setup());
			*ast = (*ast)->pipe;
		}
		term_setup();
	}
}

void	exec(t_ast *ast)
{
	ast_set(ast);
	while (ast)
	{
		if (ast->cmd)
		{
			if (!ast->pipe && !ft_strcmp(ast->cmd, "exit"))
				return (builtin_exit(ast));
			exec_ast(&ast);
		}
		if (ast->sep)
		{
			if (ast->sep->sep == semicol
					|| (ast->sep->sep == and_if && !ast->status)
					|| (ast->sep->sep == or_if && ast->status))
				ast = ast->sep->next;
			else
				ast = NULL;
		}
		else
			ast = NULL;
	}
}
