/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:32:33 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/08 12:54:47 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "env.h"

extern t_env	*g_env;

static char	*dollar_handle(char *str, int *i, int j, int *bool)
{
	t_env	*env;
	char	*sub;

	while (--j > *i)
	{
		env = NULL;
		sub = ft_strsub(str, *i + 1, j - *i);
		env = env_get(g_env, sub);
		if (env)
		{
			str = ft_delete_flags(str, *i, ft_strlen(sub) + 1);
			str = ft_insert_str(str, ft_strdup(env->value), *i);
			*i += ft_strlen(env->value) - 1;
			env = NULL;
			*bool = 0;
		}
		ft_strdel(&sub);
	}
	return (str);
}

static char	*env_var_replace(char *str)
{
	int		i;
	int		j;
	int		len_var;
	int		bool;

	i = -1;
	while (str && str[++i])
		if (str[i] == '$' && (bool = 1))
		{
			if (is_special_param(str[i + 1]))
			{
				str = special_param_replace(str, &i);
				continue ;
			}
			j = i + 1;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			len_var = j - i;
			if ((str = dollar_handle(str, &i, j, &bool)) && bool)
			{
				str = ft_delete_flags(str, i, len_var);
				i--;
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
	if (!env || !str)
		return (str);
	while (str[++i])
		if (str[i] == '~')
		{
			str = ft_delete_flags(str, i, 1);
			str = ft_insert_str(str, ft_strdup(env->value), i);
			i += ft_strlen(env->value) - 1;
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
	if (ast->redir)
		redir_expansions(ast->redir);
	ast->cmd = ast->args[0];
}
