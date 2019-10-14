/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/09 18:44:31 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/wait.h>
#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

extern t_env	*g_env;
extern int		g_ischild;

int		exec_builtin(t_ast *ast)
{
	if (!ft_strcmp(ast->cmd, "cd"))
		builtin_cd(ast);
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
	else
		return (0);
	return (1);
}

void	builtin_exit(t_ast *ast)
{
	if (ft_2dstrlen(ast->args) > 2)
	{
		return (ft_putstr_fd("21sh: exit: too many arguments\n", 2));
	}
	else if (ft_2dstrlen(ast->args) == 2)
		ft_quit(ft_atoi(ast->args[1]));
	ft_quit(0);
}

void	builtin_setenv(t_ast *ast)
{
	int i;

	if (ft_2dstrlen(ast->args) < 2)
		return (ft_putstr_fd("21sh: setenv: not enough arguments\n", 2));
	else
	{
		i = 1;
		while (ast->args[i])
			if (!env_import_string(&g_env, ast->args[i++]))
				return (ft_putstr_fd("21sh: setenv: assignment error\n", 2));
	}
	ast->status = 0;
}

void	builtin_unsetenv(t_ast *ast)
{
	int i;

	if (ft_2dstrlen(ast->args) < 2)
		return (ft_putstr_fd("21sh: unsetenv: not enough arguments\n", 2));
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
