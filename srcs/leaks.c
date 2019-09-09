/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:16:55 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/09 16:39:59 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer_parser.h"

void			ft_del_token(void *content, size_t content_size)
{
	free(((t_token *)content)->lexem);
	((t_token *)content)->lexem = NULL;
	free(content);
	content = NULL;
	(void)content_size;
}

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
