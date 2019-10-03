/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/03 14:18:11 by pcharrie         ###   ########.fr       */
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

void	exec_ast_child(t_ast *ast, char **envp)
{
	if (!ft_redir_router(ast->redir))
		exit(EXIT_FAILURE);
	if (!exec_error(ast))
	{
		if (!ast->path)
			exec_builtin(ast);
		else
			execve(ast->path, ast->args, envp);
	}
	exit(1);
}

void	exec_ast_single(t_ast *ast, char **envp)
{
	int pid;

	pid = fork();
	g_lastpid = pid;
	if (!pid)
		exec_ast_child(ast, envp);
	else if (pid == -1)
		ft_putstr_fd("fork error", 2);
	else
	{
		waitpid(pid, &ast->status, 0);
		g_status = WIFSIGNALED(ast->status) ?
			child_crash(ast->status, ast) : WEXITSTATUS(ast->status);
	}
}

void	exec_ast_fork(t_ast **ast)
{
	int		ast_size;
	char	**envp;

	envp = env_export_envp(g_env);
	term_unsetup();
	ast_size = ast_pipes_size(*ast);
	if (ast_size == 1)
		exec_ast_single(*ast, envp);
	else if (ast_size > 1)
		exec_ast_pipes(ast, ast_size, envp);
	term_setup();
	if (envp)
		ft_2dstrdel(envp);
}

void	exec_ast_next(t_ast **ast)
{
	if ((*ast)->sep)
	{
		if ((*ast)->sep->sep == semicol
			|| ((*ast)->sep->sep == and_if && (*ast)->status == 0
			&& !(*ast)->error) || ((*ast)->sep->sep == or_if
			&& (*ast)->status != 0))
			*ast = (*ast)->sep->next;
		else
			*ast = NULL;
	}
	else
		*ast = NULL;
}

void	exec(t_ast *ast)
{
	ast_set(ast);
	while (ast)
	{
		expansions_handle(ast);
		if (ast->cmd)
		{
			if (!ast->pipe)
			{
				if (!exec_builtin(ast))
					exec_ast_fork(&ast);
			}
			else
				exec_ast_fork(&ast);
		}
		exec_ast_next(&ast);
	}
}

