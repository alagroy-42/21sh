/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_chdir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 23:33:01 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/18 23:35:17 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

extern t_env	*g_env;
extern int		g_ischild;

int		builtin_cd_chdir_cdpath(char *path, int follow, t_ast *ast)
{
	char			*str;
	struct stat		buf;

	str = NULL;
	if (!env_get(g_env, "CDPATH")
		|| !(str = ft_strstrjoin(env_get(g_env, "CDPATH")->value, "/", path))
		|| stat(str, &buf) < 0)
	{
		ft_strdel(&str);
		return (0);
	}
	builtin_cd_chdir(str, follow, ast, 1);
	ft_strdel(&str);
	return (1);
}

void	builtin_cd_chdir(char *path, int follow, t_ast *ast, int cdpath)
{
	char			buff[8192];
	struct stat		buf;
	int				c;

	if (follow && (c = readlink(path, buff, 8192)) != -1)
	{
		path = buff;
		path[c] = '\0';
	}
	if (stat(path, &buf) < 0)
	{
		if (builtin_cd_chdir_cdpath(path, follow, ast))
			return ;
		ft_putstr_fd("21sh: cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (!S_ISDIR(buf.st_mode))
		ft_putstr_fd("21sh: cd: not a directory\n", 2);
	else if (access(path, X_OK) == -1)
		ft_putstr_fd("21sh: cd: permission denied\n", 2);
	else if (!g_ischild)
		set_pwd(path, follow, ast, cdpath);
}
