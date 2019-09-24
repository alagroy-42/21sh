/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 05:17:44 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/24 17:02:22 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ast.h"
#include "exec.h"
#include "env.h"
#include "libft.h"

extern t_env *g_env;
extern char *g_pwd;
extern char *g_oldpwd;

int		builtin_cd_chdir_cdpath(char *path, int follow, t_ast *ast)
{
	char			*str;
	struct	stat	buf;

	if (!env_get(g_env, "CDPATH")
		|| !(str = ft_strstrjoin(env_get(g_env, "CDPATH")->value, "/", path))
		|| stat(str, &buf) < 0)
		return (0);
	builtin_cd_chdir(str, follow, ast);
	return (1);
}

char *ft_2dstr_to_path(char **tab)
{
	int		total_len;
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	total_len = 0;
	while (tab[i])
		total_len += ft_strlen(tab[i++]);
	if (!(str = ft_strnew(total_len + ft_2dstrlen(tab))))
		return (NULL);
	i = 0;
	j = 0;
	while (tab[i])
	{
		k = 0;
		str[j++] = '/';
		while (tab[i][k])
			str[j++] = tab[i][k++];
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_2dstrjoin_path(char **tab1, char **tab2)
{
	char	**new_tab;
	int		i;
	int		j;
	int		len;

	len = ft_2dstrlen(tab1) + ft_2dstrlen(tab2);
	if (!(new_tab = (char **)malloc((len + 1) * sizeof(char *))))
		return (NULL);
	i = -1;
	j = -1;
	while (tab1 && tab1[++i])
		new_tab[++j] = tab1[i];
	i = -1;
	while (tab2 && tab2[++i])
	{
		if (ft_strcmp(tab2[i], "..") && ft_strcmp(tab2[i], "."))
			new_tab[++j] = tab2[i];
	}
	new_tab[len] = NULL;
	return (new_tab);
}


void	set_pwd(char *path, int follow, t_ast *ast)
{
	char	buff[8192];
	char	**pwd_tab;
	char	**path_tab;
	int		i;
	int		j;
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strdup(g_pwd);
	oldpwd = ft_strdup(g_pwd);

	if (path[0] == '/')
	{
		ft_strdel(&pwd);
		pwd = ft_strdup(path);
	}
	else
	{
		pwd_tab = ft_strsplit(pwd, '/');
		path_tab = ft_strsplit(path, '/');
		i = ft_2dstrlen(pwd_tab) - 1;
		j = 0;

		while (path_tab[j])
		{
			while (path_tab[j] && (!ft_strcmp(path_tab[j], "..") || !ft_strcmp(path_tab[j], ".")))
			{
				if (!ft_strcmp(path_tab[j], ".."))
					pwd_tab[i--] = NULL;
				j++;
			}
			pwd_tab = ft_2dstrjoin_path(pwd_tab, path_tab + j);
			i = ft_2dstrlen(pwd_tab) - 1;
			if (path_tab[j])
				j++;
		}

		pwd = ft_2dstr_to_path(ft_2dstrjoin(pwd_tab, path_tab + j));
		if (!ft_strlen(pwd))
		{
			ft_strdel(&pwd);
			pwd = ft_strdup("/");
		}
	}

	if (chdir(pwd) < 0)
		ft_putstr_fd("cd: error\n", 2);
	else
	{
		if (follow)
		{
			getcwd(buff, 8192);
			ft_strdel(&pwd);
			pwd = ft_strdup(buff);
		}
		ast->status = 0;
		env_set(&g_env, "PWD", pwd);
		env_set(&g_env, "OLDPWD", oldpwd);
		ft_strdel(&g_pwd);
		ft_strdel(&g_oldpwd);
		g_pwd = ft_strdup(pwd);
		g_oldpwd = ft_strdup(oldpwd);
		ft_strdel(&pwd);
		ft_strdel(&oldpwd);
	}
}

void	builtin_cd_chdir(char *path, int follow, t_ast *ast)
{
	char			buff[8192];
	struct	stat	buf;
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
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (!S_ISDIR(buf.st_mode))
		ft_putstr_fd("cd: not a directory\n", 2);
	else if (access(path, X_OK) == -1)
		ft_putstr_fd("cd: permission denied\n", 2);
	else
		set_pwd(path, follow, ast);	
}

int		builtin_cd_options(t_ast *ast)
{
	char	**tab;
	int		i;
	int		j;
	int		follow;

	follow = 0;
	if (ft_2dstrlen(ast->args) >= 2 && (!ft_strcmp(ast->args[1], "-P")
		|| !ft_strcmp(ast->args[1], "-L")
		|| !ft_strcmp(ast->args[1], "-PL")
		|| !ft_strcmp(ast->args[1], "-LP")))
	{
		if (!(tab = malloc(sizeof(char**) * (ft_2dstrlen(ast->args)))))
			return (0);	
		i = 0;
		j = 0;
		while (i < ft_2dstrlen(ast->args))
		{
			if (i == 1)
			{
				i++;
				continue;
			}
			tab[j++] = ft_strdup(ast->args[i++]);
		}
		tab[j] = NULL;

		if (!ft_strcmp(ast->args[1], "-P")
			|| !ft_strcmp(ast->args[1], "-LP"))
			follow = 1;
		// free ast args
		ast->args = tab;
	}
	return (follow);
}

void	builtin_cd(t_ast *ast, t_env *env)
{
	int follow;

	ast->status = -1;
	follow = builtin_cd_options(ast);
	if (ft_2dstrlen(ast->args) == 1)
	{
		if (env_get(env, "HOME"))
			builtin_cd_chdir(env_get(env, "HOME")->value, follow, ast);
		else
			ft_putstr_fd("cd: HOME not set\n", 2);
	}
	else if (ft_2dstrlen(ast->args) > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else
	{
		if (builtin_cd_options(ast))
			return ;
		if (!ft_strcmp(ast->args[1], "--"))
		{
			if (env_get(env, "HOME"))
				builtin_cd_chdir(env_get(env, "HOME")->value, follow, ast);
			else
				ft_putstr_fd("cd: HOME not set\n", 2);
		}
		else if (!ft_strcmp(ast->args[1], "-"))
		{
			if (env_get(env, "OLDPWD"))
			{
				ft_putendl(env_get(env, "OLDPWD")->value);
				builtin_cd_chdir(env_get(env, "OLDPWD")->value, follow, ast);
			}
			else
				ft_putstr_fd("cd: OLDPWD not set\n", 2);
		}
		else
			builtin_cd_chdir(ast->args[1], follow, ast);
	}
}
