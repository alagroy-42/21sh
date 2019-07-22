/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/07/22 19:27:02 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include <stdio.h>

extern t_env *g_env;

void	term_setup(void);
void	term_unsetup(void);

char	*ft_strstrjoin(char *s1, char *s2, char *s3)
{
	char *tmp;
	char *str;

	if (!(tmp = ft_strjoin(s1, s2)))
		return (NULL);
	str = ft_strjoin(tmp, s3);
	free(tmp);
	return (str);
}

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

int		is_cmd_file(char *cmd)
{
	if ((ft_strlen(cmd) >= 1 && cmd[0] == '.')
			|| (ft_strlen(cmd) >= 1 && cmd[0] == '/')
			|| (ft_strlen(cmd) >= 2 && cmd[0] == '.' && cmd[1] == '.')
			|| (ft_strlen(cmd) >= 2 && cmd[0] == '.' && cmd[1] == '/')
			|| (ft_strlen(cmd) >= 3 && cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
		return (1);
	return (0);
}

int		is_cmd_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "quit")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "setenv")
		|| !ft_strcmp(cmd, "unsetenv"))
		return (1);
	return (0);
}

void 	exec_error(t_ast *ast)
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

void	exec_ast(t_ast **ast)
{
	char **envp;
	int pipefds[2];
	int pid;
	int lastfd;

	if (!(envp = env_toenvp(g_env)))
		return ;
	lastfd = 0;
	while (*ast)
	{
		term_unsetup();
		pipe(pipefds);
		pid = fork();
		if (!pid)
		{
			if (!ft_redir_router((*ast)->input) || !ft_redir_router((*ast)->output))
				exit(EXIT_FAILURE);
			dup2(lastfd, 0);
			if ((*ast)->pipe != NULL) {
				dup2(pipefds[1], 1);
			}
			close(pipefds[0]);
			if ((*ast)->error)
				exec_error(*ast);
			else if (!(*ast)->path)
				exec_builtin(*ast);
			else
				execve((*ast)->path, (*ast)->args, envp);
			exit(1);
		}
		else {
			term_setup();
			waitpid(pid, &(*ast)->status, 0);
			close(pipefds[1]);
			lastfd = pipefds[0];
			if (!(*ast)->pipe)
				return ;
			*ast = (*ast)->pipe;
		}
	}
	term_setup();
}

int		ast_set_path_by_path(char **path, t_ast *ast)
{
	char	*cmd_path;

	while (*path)
	{
		if (!(cmd_path = ft_strstrjoin(*path, "/", ast->cmd)))
			return (0);
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
			ast->path = cmd_path;
			return (1);
		}
		path++;
	}
	return (0);
}

void	ast_set_path(t_ast *ast)
{
	t_env	*env_path;
	struct stat buf;
	char **path;
	
	while (ast)
	{
		ast->error = 0;
		if (is_cmd_builtin(ast->cmd))
			ast->path = NULL;
		else if (is_cmd_file(ast->cmd))
		{
			if (access(ast->cmd, F_OK) == -1)
				ast->error = 1;
			else if (access(ast->cmd, X_OK) == -1 || stat(ast->cmd, &buf) || S_ISDIR(buf.st_mode))
				ast->error = 2;
			else
				ast->path = ft_strdup(ast->cmd);
		}
		else
		{
			if (!(env_path = env_get(g_env, "PATH"))
				|| !(path = ft_strsplit(env_path->value, ':'))
				|| !ast_set_path_by_path(path, ast))
				ast->error = 3;
		}
		if (ast->pipe)
			ast = ast->pipe;
		else if (ast->sep)
			ast = ast->sep->next;
		else
			ast = NULL;
	}
}

void	exec(t_ast *ast)
{
	ast_set_path(ast);
	while (ast)
	{
		if (!ast->pipe && !ft_strcmp(ast->cmd, "exit"))
			return builtin_exit(ast);
		exec_ast(&ast);
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
