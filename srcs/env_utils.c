/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 02:40:24 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/03 03:10:45 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

extern t_env *g_env;

t_env	*env_get(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*env_import_string(t_env **env, char *str)
{
	int		i;
	char	*name;
	t_env	*tmp;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i] || !(name = ft_strnew(i)))
		return (NULL);
	ft_strncpy(name, str, i);
	tmp = env_set(env, name, str + i + 1);
	ft_strdel(&name);
	return (tmp);
}

void	env_import_envp(t_env **env, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		env_import_string(env, envp[i++]);
}

char	**env_export_envp(t_env *env)
{
	char	**str;
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp && i++ > -1)
		tmp = tmp->next;
	if (!(str = ft_2dstrnew(i)))
		return (NULL);
	i = 0;
	while (env)
	{
		if (!(str[i] = ft_strnew(ft_strlen(env->name) +
			ft_strlen(env->value) + 1)))
		{
			ft_2dstrdel(str);
			return (NULL);
		}
		ft_strcpy(str[i], env->name);
		str[i][ft_strlen(env->name)] = '=';
		ft_strcpy(str[i++] + ft_strlen(env->name) + 1, env->value);
		env = env->next;
	}
	return (str);
}
