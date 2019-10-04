/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:16:55 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/04 16:34:57 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer_parser.h"
#include "readline.h"

void		ft_del_history(void *content, size_t content_size)
{
	ft_strdel((char **)(&content));
	content_size = 0;
}

void		destroy_line(t_line *line)
{
	ft_strdel(&line->line);
	ft_strdel(&line->prompt);
	ft_strdel(&line->history_file);
	ft_lstdel(&line->history, ft_del_history);
	free(line);
	line = NULL;
}

void		ft_del_token(void *content, size_t content_size)
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
