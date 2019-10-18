/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 05:17:44 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/18 23:27:51 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

extern t_env	*g_env;
extern char		*g_pwd;
extern char		*g_oldpwd;
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

int		builtin_cd_resizeargs(t_ast *ast, int size)
{
	char	**tab;
	int		i;

	if (!(tab = ft_2dstrnew(ft_2dstrlen(ast->args) - size + 1)) || !(tab[0] = ft_strdup(ast->args[0])))
	{
		ft_2dstrdel(tab);
		return (0);
	}
	i = 1;
	while (ast->args[size])
	{
		if (!(tab[i++] = ft_strdup(ast->args[size++])))
		{
			ft_2dstrdel(tab);
			return (0);
		}
	}
	ft_2dstrdel(ast->args);
	ast->args = tab;
	return (1);
}

int		builtin_cd_options(t_ast *ast, int i, int j, int follow)
{
	i = 1;
	while (ast->args[i] && ft_strlen(ast->args[i]) > 1 && ast->args[i][0] == '-' && ft_isalpha(ast->args[i][1]))
	{
		j = 1;
		while (ast->args[i][j])
		{
			if (ast->args[i][j] != 'L' && ast->args[i][j] != 'P')
			{
				ft_putstr_fd("21sh: cd: -", 2);
				ft_putchar_fd(ast->args[i][j], 2);
				ft_putstr_fd(": invalid option\n", 2);
				ft_putstr_fd("cd: usage: cd [-L|-P] [dir]\n", 2);
				return (-1);
			}
			follow = (ast->args[i][j] == 'L' ? 0 : 1);
			j++;
		}
		i++;
	}
	if (i > 1 && !(builtin_cd_resizeargs(ast, i)))
		return (-1);
	return (follow);
}

void	builtin_cd_nooptions(t_ast *ast, int follow)
{
	if (!ft_strcmp(ast->args[1], "--"))
	{
		if (env_get(g_env, "HOME"))
			builtin_cd_chdir(env_get(g_env, "HOME")->value, follow, ast, 0);
		else
			ft_putstr_fd("21sh: cd: HOME not set\n", 2);
	}
	else if (!ft_strcmp(ast->args[1], "-"))
	{
		if (env_get(g_env, "OLDPWD"))
		{
			ft_putendl(env_get(g_env, "OLDPWD")->value);
			builtin_cd_chdir(env_get(g_env, "OLDPWD")->value, follow, ast, 0);
		}
		else
			ft_putstr_fd("21sh: cd: OLDPWD not set\n", 2);
	}
	else
		builtin_cd_chdir(ast->args[1], follow, ast, 0);
}

void	builtin_cd(t_ast *ast)
{
	int follow;

	if ((follow = builtin_cd_options(ast, 0, 0, 0)) < 0)
		return ;
	if (ft_2dstrlen(ast->args) == 1)
	{
		if (env_get(g_env, "HOME"))
			builtin_cd_chdir(env_get(g_env, "HOME")->value, follow, ast, 0);
		else
			ft_putstr_fd("21sh: cd: HOME not set\n", 2);
	}
	else if (ft_2dstrlen(ast->args) > 2)
		ft_putstr_fd("21sh: cd: too many arguments\n", 2);
	else if (!builtin_cd_options(ast, 0, 0, 0))
		builtin_cd_nooptions(ast, follow);
}
