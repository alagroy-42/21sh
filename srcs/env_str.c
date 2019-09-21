/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 00:33:42 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/22 00:33:42 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

extern t_env *g_env;

char	**env_toenvp(t_env *env, int i, int j, int k)
{
	char	**envp;

	if (!(envp = (char **)malloc(sizeof(char *) * (env_size(env) + 1))))
		return (NULL);
	while (env)
	{
		if (!(envp[i] = ft_strnew(ft_strlen(env->name) + ft_strlen(env->value) + 1)))
		{
			ft_free_2dstr(envp);
			return (NULL);
		}
		k = 0;
		j = 0;
		while (env->name[j])
			envp[i][k++] = env->name[j++];
		envp[i][k++] = '=';
		j = 0;
		while (env->value[j])
			envp[i][k++] = env->value[j++];
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int		env_string_namelen(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

int		env_string_valuelen(char *s)
{
	int i;
	int value_len;

	value_len = 0;
	i = env_string_namelen(s);
	if (s[i])
		i++;
	while (s[i])
	{
		i++;
		value_len++;
	}
	return (value_len);
}

int		env_set_string(t_env *env, char *s, int i, int j)
{
	int name_len;
	char *name;
	char *value;

	if (!(name_len = env_string_namelen(s)))
		return (0);
	if (!(name = ft_strnew(name_len)))
		return (0);
	if (!(value = ft_strnew(env_string_valuelen(s))))
	{
		free(name);
		return (0);
	}
	ft_strncpy(name, s, name_len);
	i = name_len + 1;
	while (s[i - 1] && s[i])
		value[j++] = s[i++];
	i = env_set(&env, name, value);
	free(name);
	free(value);
	return (i);
}
