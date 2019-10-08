/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:44:31 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/08 16:37:12 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/wait.h>
#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

extern t_env	*g_env;

char	*builtin_env_getpath(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	if (is_cmd_file(cmd))
		return (ft_strdup(cmd));
	if (!env_get(g_env, "PATH")
		|| !(paths = ft_strsplit(env_get(g_env, "PATH")->value, ':')))
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (!(path = ft_strstrjoin(paths[i], "/", cmd)))
			continue ;
		if (access(path, F_OK | X_OK) != -1)
		{
			ft_2dstrdel(paths);
			return (path);
		}
		ft_strdel(&path);
		i++;
	}
	ft_2dstrdel(paths);
	return (NULL);
}

int		builtin_env_exec_error(t_ast *ast, char *path, int i)
{
	struct stat	buf;

	if (!path || access(path, F_OK) == -1)
	{
		ft_putstr_fd("21sh: env: ", 2);
		ft_putstr_fd(ast->args[i], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		return (0);
	}
	if (access(path, X_OK) == -1 || stat(path, &buf) || S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("21sh: env: ", 2);
		ft_putstr_fd(ast->args[i], 2);
		ft_putstr_fd(": permission denied\n", 2);
		return (0);
	}
	return (1);
}

void	builtin_env_exec_fork(t_ast *ast, t_env *env, int i)
{
	int			pid;
	char		*path;
	char		**envp;

	path = builtin_env_getpath(ast->args[i]);
	if (!builtin_env_exec_error(ast, path, i))
		return (ft_strdel(&path));
	else
	{
		envp = env_export_envp(env);
		pid = fork();
		if (!pid)
		{
			execve(path, ast->args + i, envp);
			exit(0);
		}
		else if (pid != 1)
			waitpid(pid, NULL, 0);
		else
			ft_putstr_fd("21sh: env: fork error\n", 2);
		ft_2dstrdel(envp);
	}
	ft_strdel(&path);
}

void	builtin_env_exec(t_ast *ast)
{
	t_env	*env;
	int		i;

	i = 2;
	env = NULL;
	while (ast->args[i] && ft_strchr(ast->args[i], '='))
		env_import_string(&env, ast->args[i++]);
	if (i == ft_2dstrlen(ast->args))
	{
		while (env)
		{
			ft_putstr(env->name);
			ft_putchar('=');
			ft_putendl(env->value);
			env = env->next;
		}
	}
	else
		builtin_env_exec_fork(ast, env, i);
	env_destroy(&env);
}

void	builtin_env(t_ast *ast)
{
	t_env	*env;

	if (ft_2dstrlen(ast->args) == 1)
	{
		env = g_env;
		while (env)
		{
			ft_putstr(env->name);
			ft_putchar('=');
			ft_putendl(env->value);
			env = env->next;
		}
	}
	else if (ft_2dstrlen(ast->args) >= 2)
	{
		if (ast->args[1][0] == '-' && ft_strcmp(ast->args[1], "-i"))
			ft_putstr_fd("21sh: env: illegal option -- ", 2);
		else if (ast->args[1][0] == '-' && ft_2dstrlen(ast->args) >= 3)
			builtin_env_exec(ast);
	}
}
