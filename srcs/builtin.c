/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/24 19:20:15 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	(void)ast;
	while (env)
	{
		ft_putstr(env->name);
		ft_putstr("=");
		ft_putendl(env->value);
		env = env->next;
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
			if (!env_set_string(env, ast->args[i++], 0, 0))
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
