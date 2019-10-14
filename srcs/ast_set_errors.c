/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_set_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:27:19 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/10 15:29:16 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ast.h"

void	ast_set_file_errors(t_ast *ast)
{
	struct stat	buf;

	if (!ft_strcmp(ast->cmd, ".") || !ft_strcmp(ast->cmd, ".."))
		ast->error = 3;
	else if (access(ast->cmd, F_OK) == -1)
		ast->error = 1;
	else if (access(ast->cmd, X_OK) == -1 || stat(ast->cmd, &buf))
		ast->error = 2;
	else if (!stat(ast->cmd, &buf) && S_ISDIR(buf.st_mode))
		ast->error = 4;
	else
		ast->path = ft_strdup(ast->cmd);
}
