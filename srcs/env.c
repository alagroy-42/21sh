/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:24:40 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/22 00:43:47 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

extern t_env *g_env;

int		env_setup(char **envp, t_env *tmp, t_env *tmp2)
{
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
	int i;

	name_len = env_string_namelen(envp);
	if (name_len == ft_strlen(envp))
		return (0);
	if (!(env->name = ft_strnew(name_len)))
		return (0);
	if (!(env->value = ft_strnew(env_string_valuelen(envp))))
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

int		env_set(t_env **env, char *name, char *value)
{
	t_env *tmp;

	if (!*env)
		return ((*env = env_new(name, value)) ? 1 : 0);
	if (env_edit(*env, name, value))
		return (1);
	tmp = env_get_last(*env);
	if (!(tmp->next = env_new(name, value)))
		return (0);
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
