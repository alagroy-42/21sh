/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:24:40 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/30 17:05:54 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

extern t_env *g_env;

t_env	*env_new(char *name, char *value)
{
	t_env *env;

	if (!(env = malloc(sizeof(t_env))))
	{
		env_free(&env);
		return (NULL);
	}
	env->name = ft_strdup(name);
	env->value = ft_strdup(value);
	if (!env->name || !env->value)
	{
		env_free(&env);
		return (NULL);
	}
	env->next = NULL;
	return (env);
}

void	env_free(t_env **env)
{
	if (env && *env)
	{
		if ((*env)->name)
		{
			free((*env)->name);
			(*env)->name = NULL;
		}
		if ((*env)->value)
		{
			free((*env)->value);
			(*env)->value = NULL;
		}
		(*env)->next = NULL;
		free(*env);
		*env = NULL;
	}
}

void	env_destroy(t_env **env)
{
	t_env *tmp;

	if (env)
	{
		while (*env)
		{
			tmp = (*env)->next;
			env_free(env);
			*env = tmp;
		}
	}
}

t_env	*env_set(t_env **env, char *name, char *value)
{
	t_env *tmp;
	t_env *tmp2;

	if (!env)
		return (NULL);
	if (!*env)
		return ((*env = env_new(name, value)));
	if ((tmp = env_get(*env, name)))
	{
		ft_strdel(&tmp->value);
		return ((tmp->value = ft_strdup(value)) ? tmp : NULL);
	}
	tmp = env_new(name, value);
	tmp2 = *env;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
	return (tmp);
}

void	env_remove(t_env **env, char *name)
{
	t_env *curr;
	t_env *prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			if (!prev)
				*env = curr->next;
			else
				prev->next = curr->next;
			env_free(&curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
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

	if (!(str = ft_2dstrnew((env_size(env)))))
		return (NULL);
	i = 0;
	while (env)
	{
		if (!(str[i] = ft_strnew(ft_strlen(env->name) + ft_strlen(env->value) + 1)))
		{
			ft_2dstrdel(str);
			return (NULL);
		}
		ft_strcpy(str[i], env->name);
		str[i][ft_strlen(env->name)] = '=';
		ft_strcpy(str[i] + ft_strlen(env->name) + 1, env->value);
		env = env->next;
		i++;
	}
	return (str);
}

void	env_putendl(t_env *env)
{
	while (env)
	{
		ft_putstr(env->name);
		ft_putstr("=");
		ft_putendl(env->value);
		env = env->next;
	}
}
