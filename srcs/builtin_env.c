/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:44:31 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/30 15:23:24 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/wait.h>
#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

extern t_env	*g_env;

// char	*get_cmd_path(char *cmd)
// {

// }

// void	builtin_env_exec(t_ast *ast)
// {

// }

void	builtin_env(t_ast *ast)
{
	// t_env	*tmp;
	// int		i;

	// struct stat	buf;
	// int			pid;

	// i = 0;
	// tmp = NULL;

	if (ft_2dstrlen(ast->args) == 1)
		env_putendl(g_env);
	// else if (ft_2dstrlen(ast->args) >= 2)
	// {
	// 	if (ast->args[1][0] == '-' && ft_strcmp(ast->args[1], "-i"))
	// 	{
	// 		ft_putstr_fd("env: illegal option -- ", 2);
	// 	}
	// 	else if (ast->args[1][0] == '-')
	// 	{
	// 		if (ft_2dstrlen(ast->args) >= 3)
	// 		{
	// 			i = 2;
	// 			while (ast->args[i] && ft_strchr(ast->args[i], '='))
	// 				env_import_string(&tmp, ast->args[i++]);
	// 			if (i == ft_2dstrlen(ast->args))
	// 				env_putendl(tmp);
	// 			else
	// 			{
	// 				if (access(ast->args[i], F_OK) == -1)
	// 				{
	// 					ft_putstr_fd("env: ", 2);
	// 					ft_putstr_fd(ast->args[i], 2);
	// 					ft_putstr_fd(": no such file or directory\n", 2);
	// 				}
	// 				else if (access(ast->args[i], X_OK) == -1 || stat(ast->args[i], &buf)
	// 					|| S_ISDIR(buf.st_mode))
	// 				{
	// 					ft_putstr_fd("env: ", 2);
	// 					ft_putstr_fd(ast->args[i], 2);
	// 					ft_putstr_fd(": permission denied\n", 2);
	// 				}
	// 				else
	// 				{
	// 					pid = fork();
	// 					if (!pid)
	// 						execve(ast->args[i], ast->args + i, env_export_envp(g_env));
	// 					else if (pid != 1)
	// 						waitpid(pid, NULL, 0);
	// 					else
	// 						ft_putstr_fd("env: fork error\n", 2);
	// 				}
	// 			}
	// 		}
	// 	}
	// }
}