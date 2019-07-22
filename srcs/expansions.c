/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:32:33 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/22 17:39:33 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "env.h"

extern t_env	*g_env;

static char	*env_var_replace(char *str)
{
	int		i;
	int		j;
	t_env	*env;
	char	*sub;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
		{
			j = i + 1;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			while (--j > i)
			{
				env = NULL;
				sub = ft_strsub(str, i + 1, j - i);
				env = env_get(g_env, sub);
				if (env)
				{
					str = ft_delete_flags(str, i, ft_strlen(sub) + 1);
					str = ft_insert_str(str, ft_strdup(env->value), i);
					i += ft_strlen(env->value) - 1;
				}
				ft_strdel(&sub);
			}
		}
	return (str);
}

static char	*tilde_replace(char *str)
{
	int		i;
	t_env	*env;

	env = env_get(g_env, "HOME");
	i = -1;
	if (!env)
		return (str);
	while (str[++i])
		if (str[i] == '~')
		{
			str = ft_delete_flags(str, i, 1);
			str = ft_insert_str(str, ft_strdup(env->value), i);
			i += ft_strlen(env->value);
		}
	return (str);
}

static void	redir_expansions(t_redir *redir)
{
	t_redir	*tmp;
	int		i;

	i = -1;
	tmp = redir;
	while (tmp)
	{
		if (tmp->target)
		{
			if (ft_strchr(tmp->target, '~'))
				tmp->target = tilde_replace(tmp->target);
			if (ft_strchr(tmp->target, '$'))
				tmp->target = env_var_replace(tmp->target);
		}
		while (tmp->heredoc && tmp->heredoc[++i])
		{
			if (ft_strchr(tmp->heredoc[i], '~'))
				tmp->heredoc[i] = tilde_replace(tmp->heredoc[i]);
			if (ft_strchr(tmp->heredoc[i], '$'))
				tmp->heredoc[i] = env_var_replace(tmp->heredoc[i]);
		}
		tmp = tmp->next;
	}
}

void		expansions_handle(t_ast *ast)
{
	int		i;

	if (!ast)
		return ;
	i = -1;
	while (ast->args && ast->args[++i])
	{
		if (ft_strchr(ast->args[i], '~'))
			ast->args[i] = tilde_replace(ast->args[i]);
		if (ft_strchr(ast->args[i], '$'))
			ast->args[i] = env_var_replace(ast->args[i]);
	}
	if (ast->input)
		redir_expansions(ast->input);
	if (ast->output)
		redir_expansions(ast->input);
}
