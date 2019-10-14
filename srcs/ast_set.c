/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 20:18:49 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/10 15:29:13 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		i;

	i = 0;
	while (path[i])
	{
		if (!(cmd_path = ft_strstrjoin(path[i], "/", ast->cmd)))
			return (0);
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
			ast->path = ft_strdup(cmd_path);
			ft_strdel(&cmd_path);
			return (1);
		}
		ft_strdel(&cmd_path);
		i++;
	}
	return (0);
}

void	ast_set_path(t_ast *ast)
{
	t_env		*env_path;
	char		**path;

	ast->error = 0;
	ast->status = -1;
	path = NULL;
	if (is_cmd_builtin(ast->cmd))
		ast->path = NULL;
	else if (is_cmd_file(ast->cmd))
		ast_set_file_errors(ast);
	else if (!(env_path = env_get(g_env, "PATH"))
		|| !(path = ft_strsplit(env_path->value, ':'))
		|| !ast_set_path_by_path(path, ast))
		ast->error = 3;
	if (path != NULL)
		ft_2dstrdel(path);
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
