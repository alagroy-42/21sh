/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 20:18:49 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/19 13:06:06 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ast.h"
#include "env.h"

extern t_env *g_env;

int		is_cmd_file(char *cmd)
{
	if ((ft_strlen(cmd) >= 1 && cmd[0] == '.')
			|| (ft_strlen(cmd) >= 1 && cmd[0] == '/')
			|| (ft_strlen(cmd) >= 2 && cmd[0] == '.' && cmd[1] == '.')
			|| (ft_strlen(cmd) >= 2 && cmd[0] == '.' && cmd[1] == '/')
			|| (ft_strlen(cmd) >= 3 && cmd[0] == '.'
			&& cmd[1] == '.' && cmd[2] == '/'))
		return (1);
	return (0);
}

int		is_cmd_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "quit")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "setenv")
		|| !ft_strcmp(cmd, "unsetenv"))
		return (1);
	return (0);
}

int		ast_set_path_by_path(char **path, t_ast *ast)
{
	char	*cmd_path;

	while (*path)
	{
		if (!(cmd_path = ft_strstrjoin(*path, "/", ast->cmd)))
			return (0);
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
			ast->path = cmd_path;
			return (1);
		}
		path++;
	}
	return (0);
}

void	ast_set_path(t_ast *ast)
{
	t_env		*env_path;
	struct stat	buf;
	char		**path;

	ast->error = 0;
	if (is_cmd_builtin(ast->cmd))
		ast->path = NULL;
	else if (is_cmd_file(ast->cmd))
	{
		if (access(ast->cmd, F_OK) == -1)
			ast->error = 1;
		else if (access(ast->cmd, X_OK) == -1 || stat(ast->cmd, &buf)
			|| S_ISDIR(buf.st_mode))
			ast->error = 2;
		else
			ast->path = ft_strdup(ast->cmd);
	}
	else
	{
		if (!(env_path = env_get(g_env, "PATH"))
			|| !(path = ft_strsplit(env_path->value, ':'))
			|| !ast_set_path_by_path(path, ast))
			ast->error = 3;
	}
}

void	ast_set(t_ast *ast)
{
	while (ast)
	{
		if (ast->cmd)
			ast_set_path(ast);
		if (ast->pipe)
			ast = ast->pipe;
		else if (ast->sep)
			ast = ast->sep->next;
		else
			ast = NULL;
	}
}
