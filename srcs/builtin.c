/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/28 22:50:24 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

extern t_env	*g_env;
extern int		g_ischild;

void	builtin_exit(t_ast *ast)
{
	if (ft_2dstrlen(ast->args) > 2)
	{
		return (ft_putstr_fd("exit: too many arguments\n", 2));
	}
	else if (ft_2dstrlen(ast->args) == 2)
		ft_quit(ft_atoi(ast->args[1]));
	ft_quit(0);
}

void	builtin_env(t_ast *ast)
{
	t_env	*tmp;
	int		i;

	struct stat	buf;
	int			pid;

	i = 0;
	tmp = NULL;

	if (ft_2dstrlen(ast->args) == 1)
		env_putendl(g_env);
	else if (ft_2dstrlen(ast->args) >= 2)
	{
		if (ast->args[1][0] == '-' && ft_strcmp(ast->args[1], "-i"))
		{
			ft_putstr_fd("env: illegal option -- ", 2);
		}
		else if (ast->args[1][0] == '-')
		{
			if (ft_2dstrlen(ast->args) >= 3)
			{
				i = 2;
				while (ast->args[i] && ft_strchr(ast->args[i], '='))
					env_import_string(&tmp, ast->args[i++]);
				if (i == ft_2dstrlen(ast->args))
					env_putendl(tmp);
				else
				{
					if (access(ast->args[i], F_OK) == -1)
					{
						ft_putstr_fd("env: ", 2);
						ft_putstr_fd(ast->args[i], 2);
						ft_putstr_fd(": no such file or directory\n", 2);
					}
					else if (access(ast->args[i], X_OK) == -1 || stat(ast->args[i], &buf)
						|| S_ISDIR(buf.st_mode))
					{
						ft_putstr_fd("env: ", 2);
						ft_putstr_fd(ast->args[i], 2);
						ft_putstr_fd(": permission denied\n", 2);
					}
					else
					{
						pid = fork();
						if (!pid)
							execve(ast->args[i], ast->args + i, env_export_envp(g_env));
						else if (pid != 1)
							waitpid(pid, NULL, 0);
						else
							ft_putstr_fd("env: fork error\n", 2);
					}
				}
			}
		}
		else
		{
			//ft_putendl(ast->args[1]);
		}
	}
}

void	builtin_setenv(t_ast *ast)
{
	int i;

	if (ft_2dstrlen(ast->args) < 2)
		return ft_putstr_fd("setenv: not enough arguments\n", 2);
	else
	{
		i = 1;
		while (ast->args[i])
			if (!env_import_string(&g_env, ast->args[i++]))
				return (ft_putstr_fd("setenv: assignment error\n", 2));
	}
	ast->status = 0;
}

void	builtin_unsetenv(t_ast *ast)
{
	int i;

	if (ft_2dstrlen(ast->args) < 2)
		return ft_putstr_fd("unsetenv: not enough arguments\n", 2);
	else
	{
		i = 1;
		while (ast->args[i])
			env_remove(&g_env, ast->args[i++]);
	}
	ast->status = 0;
}

void	builtin_echo(t_ast *ast)
{
	int i;

	if (ft_2dstrlen(ast->args) > 1)
	{
		i = 1;
		if (!ft_strcmp(ast->args[1], "-n"))
			i++;
		while (ast->args[i])
		{
			ft_putstr(ast->args[i]);
			if (ast->args[i + 1])
				ft_putstr(" ");
			i++;
		}
		if (ft_strcmp(ast->args[1], "-n"))
			ft_putstr("\n");
	}
	ast->status = 0;
}
