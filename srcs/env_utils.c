/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 00:35:05 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/22 00:35:05 by pcharrie         ###   ########.fr       */
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

t_env	 *env_get_last(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}
