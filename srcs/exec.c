/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/02 13:45:16 by alagroy-         ###   ########.fr       */
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
	if (!ft_strcmp(ast->cmd, "cd"))
		builtin_cd(ast, g_env);
	else if (!ft_strcmp(ast->cmd, "echo"))
		builtin_echo(ast);
	else if (!ft_strcmp(ast->cmd, "exit"))
		builtin_exit(ast);
	else if (!ft_strcmp(ast->cmd, "env"))
		builtin_env(ast);
	else if (!ft_strcmp(ast->cmd, "setenv"))
		builtin_setenv(ast);
	else if (!ft_strcmp(ast->cmd, "unsetenv"))
		builtin_unsetenv(ast);
	else if (g_ischild)
		exit(ast->status);
	else
		return (0);
	return (1);
}

void	ast_pipes_end(t_ast **ast)
{
	while ((*ast)->pipe)
		*ast = (*ast)->pipe;
}

int		exec_error(t_ast *ast)
{

	while (ast)
	{
		if (!ast->error)
		{
			ast = ast->pipe;
			continue ;
		}
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
		return (1);
	}
	return (0);
}

void	exec_ast_child(t_ast *ast, char **envp)
{
	if (!ft_redir_router(ast->redir))
		exit(EXIT_FAILURE);
	if (!ast->path)
		exec_builtin(ast);
	else
		execve(ast->path, ast->args, envp);
	exit(1);
}

void	exec_ast_single(t_ast *ast, char **envp)
{
	int pid;

	pid = fork();
	g_lastpid = pid;
	if (!pid)
	{
		if (!ft_redir_router(ast->redir))
			exit(EXIT_FAILURE);
		exec_ast_child(ast, envp);
	}
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
	int	ast_size;
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

void	exec(t_ast *ast)
{
	ast_set(ast);
	while (ast)
	{
		expansions_handle(ast);
		if (exec_error(ast))
			ast_pipes_end(&ast);
		else if (ast->cmd)
		{
			if (!ast->pipe)
			{
				if (!exec_builtin(ast))
					exec_ast_fork(&ast);
			}
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
