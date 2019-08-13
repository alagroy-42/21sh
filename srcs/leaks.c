/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:16:55 by alagroy-          #+#    #+#             */
/*   Updated: 2019/08/13 18:52:56 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer_parser.h"

static void	ft_del_redir(t_redir **redir)
{
	if (!redir || !*redir)
		return ;
	ft_del_redir(&(*redir)->next);
	ft_strdel(&(*redir)->target);
	ft_free_2dstr((*redir)->heredoc);
	free(*redir);
	*redir = NULL;
}

void		ft_ast_del(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	ft_ast_del(&(*ast)->pipe);
	ft_free_2dstr((*ast)->args);
	ft_strdel(&(*ast)->path);
	ft_del_redir(&(*ast)->redir);
	if ((*ast)->sep)
	{
		ft_ast_del(&(*ast)->sep->next);
		free((*ast)->sep);
	}
	free(*ast);
	*ast = NULL;
}
