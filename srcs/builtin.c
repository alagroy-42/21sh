/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:14:55 by pcharrie          #+#    #+#             */
/*   Updated: 2019/06/25 22:12:15 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

#include <stdio.h>

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

void	builtin_cd_chdir()
{

}

void	builtin_cd(t_ast *ast, t_env *env)
{
	// if (ft_tablen(ast->args) == 1)
	// {
	// 	if ()
	// }
	(void)ast;
	(void)env;
}
