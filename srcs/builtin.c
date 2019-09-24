/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/24 20:49:42 by pcharrie         ###   ########.fr       */
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
	ast->status = 0;
	if (ft_2dstrlen(ast->args) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		ast->status = -1;
		return ;
	}
	else if (ft_2dstrlen(ast->args) == 2)
		ft_quit(ft_atoi(ast->args[1]));
	ft_quit(0);
}

void	builtin_env(t_ast *ast, t_env *env)
{
	t_env		*new_env;
	int			i;
	struct stat	buf;
	int			pid;

	ast->status = 0;
	new_env = NULL;
	i = 0;
	if (ft_2dstrlen(ast->args) == 1)
	{
		while (env)
		{
			ft_putstr(env->name);
			ft_putstr("=");
			ft_putendl(env->value);
			env = env->next;
		}
	}
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
					env_set_string(&new_env, ast->args[i++], 0, 0);
				if (i == ft_2dstrlen(ast->args))
					env_putendl(new_env);
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
							execve(ast->args[i], ast->args + i, env_toenvp(new_env, 0, 0, 0));
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
	if (g_ischild)
		exit(0);
}

void	builtin_setenv(t_ast *ast, t_env *env)
{
	int i;

	ast->status = 0;
	if (ft_2dstrlen(ast->args) == 1)
	{
		ft_putstr_fd("setenv: not enough arguments\n", 2);
		ast->status = -1;
	}
	else
	{
		i = 1;
		while (ast->args[i])
		{
			if (!env_set_string(&env, ast->args[i++], 0, 0))
			{
				ast->status = -1;
				return ft_putstr_fd("setenv: `=': not a valid identifier\n", 2);
			}
		}
	}
	if (g_ischild)
		exit(0);
}

void	builtin_unsetenv(t_ast *ast, t_env **env)
{
	int i;

	(void)env;
	ast->status = 0;
	if (ft_2dstrlen(ast->args) == 1)
	{
		ft_putstr_fd("unsetenv: not enough arguments\n", 2);
		ast->status = -1;
	}
	else
	{
		i = 1;
		while (ast->args[i])
		{
			env_remove(env, ast->args[i]);
			i++;
		}
	}
	if (g_ischild)
		exit(0);
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
	if (g_ischild)
		exit(0);
}
