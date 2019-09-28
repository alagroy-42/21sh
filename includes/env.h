/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:19:47 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/28 19:32:17 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

t_env			*env_new(char *name, char *value);
void			env_free(t_env **env);
void			env_destroy(t_env **env);
t_env			*env_set(t_env **env, char *name, char *value);
void			env_remove(t_env **env, char *name);
t_env			*env_get(t_env *env, char *name);
int				env_size(t_env *env);
t_env			*env_import_string(t_env **env, char *str);
void			env_import_envp(t_env **env, char **envp);
char			**env_export_envp(t_env *env);

#endif
