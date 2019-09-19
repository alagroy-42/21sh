/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:24:40 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/19 14:12:11 by pcharrie         ###   ########.fr       */
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

int		env_edit(t_env *env, char *name, char *value)
{
	t_env *tmp;

	if ((tmp = env_get(env, name)))
	{
		ft_strdel(&tmp->value);
		if (!(tmp->value = ft_strnew(ft_strlen(value))))
			return (1);
		ft_strcpy(tmp->value, value);
		return (1);
	}
	return (0);
}

int		env_set_string(t_env *env, char *s)
{
	int i;
	int j;
	int name_len;
	int value_len;
	char *name;
	char *value;

	if (!(name_len = env_string_namelen(s)))
		return (0);
	value_len = env_string_valuelen(s);
	if (!(name = ft_strnew(name_len)))
		return (0);
	if (!(value = ft_strnew(value_len)))
	{
		free(name);
		return (0);
	}
	ft_strncpy(name, s, name_len);
	i = name_len + 1;
	j = 0;
	while (s[i])
	{
		value[j] = s[i];
		j++;
		i++;
	}
	i = env_set(&env, name, value);
	free(name);
	free(value);
	return (i);
}

t_env	*env_new(char *name, char *value)
{
	t_env *env;

	if (!(env = malloc(sizeof(t_env))))
	{
		env_destroy(&env);
		return (NULL);
	}
	if (!(env->name = ft_strdup(name)))
	{
		env_destroy(&env);
		return (NULL);
	}
	if (!(env->value = ft_strdup(value)))
	{
		env_destroy(&env);
		return (NULL);
	}
	env->next = NULL;
	return (env);
}

int		env_set(t_env **env, char *name, char *value)
{
	t_env *tmp;

	if (!*env)
	{
		if ((*env = env_new(name, value)))
			return (1);
		return (0);
	}
	tmp = *env;
	if (env_edit(tmp, name, value))
		return (1);
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = malloc(sizeof(t_env))))
		return (0);
	tmp->next->next = NULL;
	if (!(tmp->next->name = ft_strnew(ft_strlen(name))))
	{
		free(tmp->next);
		tmp->next = NULL;
		return (0);
	}
	if (!(tmp->next->value = ft_strnew(ft_strlen(value))))
	{
		free(tmp->next->name);
		free(tmp->next);
		tmp->next = NULL;
		return (0);
	}
	ft_strcpy(tmp->next->name, name);
	ft_strcpy(tmp->next->value, value);
	return (1);
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
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
