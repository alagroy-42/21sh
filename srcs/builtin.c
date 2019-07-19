/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/07/19 10:35:39 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

extern t_env *g_env;

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	builtin_exit(t_ast *ast)
{
	if (ft_tablen(ast->args) > 2)
		ft_putendl("exit: too many arguments");
	else if (ft_tablen(ast->args) == 2)
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
}

void	builtin_setenv(t_ast *ast, t_env *env)
{
	int i;
	
	if (ft_tablen(ast->args) == 1)
		ft_putendl("setenv: not enough arguments");
	else
	{
		i = 1;
		while (ast->args[i])
			env_set_string(env, ast->args[i++]);
	}
}

void	builtin_unsetenv(t_ast *ast, t_env **env)
{
	int i;

	(void)env;
	if (ft_tablen(ast->args) == 1)
		ft_putendl("unsetenv: not enough arguments");
	else
	{
		i = 1;
		while (ast->args[i])
		{
			env_remove(env, ast->args[i]);
			i++;
		}
	}
}

void	builtin_echo(t_ast *ast)
{
	int i;
	
	if (ft_tablen(ast->args) > 1)
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
}

void	builtin_cd_chdir()
{

}

void	builtin_cd(t_ast *ast, t_env *env)
{
	if (ft_tablen(ast->args) == 1)
	{
		if (env_get(env, "HOME"))
		{

		}
		else
			ft_putendl("cd: HOME not set");
	}
}
