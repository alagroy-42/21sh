/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 05:17:44 by pcharrie          #+#    #+#             */
/*   Updated: 2019/07/23 18:48:53 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

extern t_env *g_env;

void	builtin_cd_chdir(char *path)
{
	char			buff[8192];
	struct	stat	buf;

	if (stat(path, &buf) < 0)
		ft_putstr_fd("cd: no such file or directory\n", 2);
	else if (!S_ISDIR(buf.st_mode))
		ft_putstr_fd("cd: not a directory\n", 2);
	else if (access(path, X_OK) == -1)
		ft_putstr_fd("cd: permission denied\n", 2);
	else if (chdir(path) < 0)
		ft_putstr_fd("cd: error\n", 2);
	else
	{
		env_set(&g_env, "OLDPWD", env_get(g_env, "PWD")->value);
		getcwd(buff, 8192);
		env_set(&g_env, "PWD", buff);
	}
}

void	builtin_cd(t_ast *ast, t_env *env)
{
	if (ft_2dstrlen(ast->args) == 1)
	{
		if (env_get(env, "HOME"))
			builtin_cd_chdir(env_get(env, "HOME")->value);
		else
			ft_putstr_fd("cd: HOME not set\n", 2);
	}
	else if (ft_2dstrlen(ast->args) > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else
	{
		if (!ft_strcmp(ast->args[1], "--"))
		{
			if (env_get(env, "HOME"))
			builtin_cd_chdir(env_get(env, "HOME")->value);
			else
				ft_putstr_fd("cd: HOME not set\n", 2);
		}
		else if (!ft_strcmp(ast->args[1], "-"))
		{
			if (env_get(env, "OLDPWD"))
			{
				ft_putendl(env_get(env, "OLDPWD")->value);
				builtin_cd_chdir(env_get(env, "OLDPWD")->value);
			}
			else
				ft_putstr_fd("cd: OLDPWD not set\n", 2);
		}
		else
			builtin_cd_chdir(ast->args[1]);
	}
}
