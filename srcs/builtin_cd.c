/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 05:17:44 by pcharrie          #+#    #+#             */
/*   Updated: 2019/07/23 05:18:01 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

void	builtin_cd_chdir()
{

}

void	builtin_cd(t_ast *ast, t_env *env)
{
	if (ft_2dstrlen(ast->args) == 1)
	{
		if (env_get(env, "HOME"))
		{

		}
		else
			ft_putendl("cd: HOME not set");
	}
}
