/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/06/25 22:57:30 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>

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

int		exec_path(char **path, t_ast *ast)
{
	char	*cmd_path;
	char	**envp;
	int		pid;
	
	while (*path)
	{
		if (!(cmd_path = ft_strstrjoin(*path, "/", ast->cmd)))
			return (0);
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
			if (!(envp = env_toenvp(g_env)))
				return (0);
			pid = fork();
			if (pid < 0)
				return (0);
			term_unsetup();
			if (!pid)
			{
				signal(SIGINT, SIG_DFL);
				execve(cmd_path, ast->args, envp);
			}
			waitpid(pid, NULL, 0);
			term_setup();
			ft_free_2dstr(envp);
			return (1);;
		}
		free(cmd_path);
		path++;
	}
	return (0);
}

int		exec_file(t_ast *ast)
{
	char	**envp;
	int		pid;
	struct stat buf;

	if (access(ast->cmd, F_OK) != -1)
	{
		if (access(ast->cmd, X_OK) != -1 && !stat(ast->cmd, &buf) && !S_ISDIR(buf.st_mode))
		{
			if (!(envp = env_toenvp(g_env)))
				return (0);
			pid = fork();
			if (pid < 0)
				return (0);
			if (!pid)
			{
				ft_redir_router(ast->input);
				ft_redir_router(ast->output);
				execve(ast->cmd, ast->args, envp);
			}
			waitpid(pid, NULL, 0);
			ft_free_2dstr(envp);
		}
		else
		{
			ft_putstr(ast->cmd);
			ft_putendl(": permission denied");
		}
	}
	else
	{
		ft_putstr(ast->cmd);
		ft_putendl(": no such file or directory");
	}
	return (0);
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

int		exec(t_ast *ast)
{
	t_env	*env_path;
	char	**path;

	if (!ast->cmd)
		return (-1);
	if (is_cmd_file(ast->cmd))
		exec_file(ast);
	else
	{
		if (!exec_builtin(ast))
		{
			path = NULL;
			if (!(env_path = env_get(g_env, "PATH"))
				|| !(path = ft_strsplit(env_path->value, ':'))
				|| !exec_path(path, ast))
			{
				ft_putstr(ast->cmd);
				ft_putendl(": command not found");
			}
			if (path)
				ft_free_2dstr(path);
		}
	}
	return (1);
}
