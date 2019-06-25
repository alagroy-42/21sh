/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:24:40 by pcharrie          #+#    #+#             */
/*   Updated: 2019/06/25 20:49:18 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

extern t_env *g_env;

int		env_setup(char **envp)
{
	t_env *tmp;
	t_env *tmp2;
	
	while (*envp)
	{
		if (!(tmp = malloc(sizeof(t_env))))
		{
			env_destroy(&g_env);
			return (0);
		}
		if (!(env_setup_setenvptoenv(*envp, tmp)))
		{
			env_destroy(&g_env);
			return (0);
		}
		tmp->next = NULL;
		if (!g_env)
			g_env = tmp;
		else
		{
			tmp2 = g_env;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->next = tmp;
		}
		envp++;
	}
	return (1);
}

int		env_setup_setenvptoenv(char *envp, t_env *env)
{
	size_t name_len;
	int value_len;
	int i;

	name_len = 0;
	while (envp[name_len] && envp[name_len] != '=')
		name_len++;
	if (name_len == ft_strlen(envp))
		return (0);
	i = name_len + 1;
	value_len = 0;
	while (envp[i])
	{
		value_len++;
		i++;
	}
	if (!(env->name = ft_strnew(name_len)))
		return (0);
	if (!(env->value = ft_strnew(value_len)))
	{
		ft_strdel(&env->name);
		return (0);
	}
	i = 0;
	while (envp[i] && envp[i] != '=')
	{
		env->name[i] = envp[i];
		i++;
	}
	i++;
	name_len = 0;
	while (envp[i])
		env->value[name_len++] = envp[i++];
	return (1);
}

void	env_destroy(t_env **env)
{
	t_env *tmp;
	
	if (env)
	{
		while (*env)
		{
			if ((*env)->name)
				free((*env)->name);
			if ((*env)->value)
				free((*env)->value);
			tmp = (*env)->next;
			free(*env);
			*env = tmp;
		}
	}
}

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

int		env_size(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_toenvp(t_env *env)
{
	char	**envp;
	int		i;
	int		j;
	int		k;

	if (!(envp = (char **)malloc(sizeof(char *) * (env_size(env) + 1))))
		return (NULL);
	i = 0;
	while (env)
	{
		if (!(envp[i] = ft_strnew(ft_strlen(env->name) + ft_strlen(env->value))))
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