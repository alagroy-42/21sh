/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 04:55:11 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/04 09:57:18 by pcharrie         ###   ########.fr       */
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

void	set_pwd_nofollow_del(char **pwd, char **pwd_tab, char **path_tab, int j)
{
	char **join_tab;

	join_tab = ft_2dstrjoin_nodel(pwd_tab, &path_tab[j]);
	ft_strdel(pwd);
	*pwd = ft_2dstr_to_path(join_tab);
	ft_2dstrdel(join_tab);
	ft_2dstrdel(pwd_tab);
	ft_2dstrdel(path_tab);
	if (!ft_strlen(*pwd))
	{
		ft_strdel(pwd);
		*pwd = ft_strdup("/");
	}
}

void	set_pwd_nofollow(char *path, char **pwd, char **pwd_tab, int i)
{
	char	**path_tab;
	char	**join_tab;
	int		j;

	pwd_tab = ft_strsplit(*pwd, '/');
	path_tab = ft_strsplit(path, '/');
	i = ft_2dstrlen(pwd_tab) - 1;
	j = 0;
	while (path_tab[j])
	{
		while (path_tab[j] && (!ft_strcmp(path_tab[j], "..")
			|| !ft_strcmp(path_tab[j], ".")))
			if (!ft_strcmp(path_tab[j++], ".."))
				ft_strdel(&pwd_tab[i--]);
		join_tab = ft_2dstrjoin_path(pwd_tab, path_tab, &j);
		ft_2dstrdel(pwd_tab);
		pwd_tab = join_tab;
		i = ft_2dstrlen(pwd_tab) - 1;
		if (path_tab[j])
			j++;
	}
	set_pwd_nofollow_del(pwd, pwd_tab, path_tab, j);
}

void	set_pwd_chdir(char **pwd, char **oldpwd, int cdpath, int follow)
{
	char	buff[8192];

	ft_strdel(&g_pwd);
	ft_strdel(&g_oldpwd);
	if (follow)
	{
		getcwd(buff, 8192);
		ft_strdel(pwd);
		*pwd = ft_strdup(buff);
	}
	env_set(&g_env, "PWD", *pwd);
	env_set(&g_env, "OLDPWD", *oldpwd);
	if (cdpath)
		ft_putendl(*pwd);
	g_pwd = ft_strdup(*pwd);
	g_oldpwd = ft_strdup(*oldpwd);
}

void	set_pwd(char *path, int follow, t_ast *ast, int cdpath)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strdup(g_pwd);
	oldpwd = ft_strdup(g_pwd);
	if (path[0] == '/' || follow)
	{
		ft_strdel(&pwd);
		pwd = ft_strdup(path);
	}
	else if (!follow)
		set_pwd_nofollow(path, &pwd, NULL, 0);
	if (chdir(pwd) < 0)
		ft_putstr_fd("cd: error\n", 2);
	else
	{
		ast->status = 0;
		set_pwd_chdir(&pwd, &oldpwd, cdpath, follow);
	}
	ft_strdel(&pwd);
	ft_strdel(&oldpwd);
}
