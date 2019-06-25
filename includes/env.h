/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:19:47 by pcharrie          #+#    #+#             */
/*   Updated: 2019/06/25 23:09:01 by pcharrie         ###   ########.fr       */
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

int		env_setup(char **envp);
int		env_setup_setenvptoenv(char *envp, t_env *env);
int		env_set(t_env *env, char *name, char *value);
int		env_set_string(t_env *env, char *s);
int		env_edit(t_env *env, char *name, char *value);
t_env	*env_get(t_env *env, char *name);
int		env_size(t_env *env);
char	**env_toenvp(t_env *env);
void	env_remove(t_env **env, char *name);
void	env_destroy(t_env **env);

#endif