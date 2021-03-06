/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:35:19 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/09 16:41:20 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer_parser.h"
#include "signal_21sh.h"

extern t_line	*g_line;
extern int		g_ctrlr;

t_ast		*create_ast_node(int piped)
{
	t_ast	*node;

	if (!(node = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	node->cmd = NULL;
	node->args = NULL;
	node->redir = NULL;
	node->sep = NULL;
	node->pipe = NULL;
	node->path = NULL;
	node->piped = piped;
	return (node);
}

static char	**ft_heredoc(t_list *tmp)
{
	char	**heredoc;
	char	*limit;
	t_line	*line;

	line = g_line;
	limit = ft_strjoin(((t_token *)tmp->next->content)->lexem, "\n");
	heredoc = NULL;
	if (!isatty(STDIN_FILENO))
		return (heredoc);
	g_ctrlr = 1;
	readline(line, INCOMPLETE);
	while (line->line && limit && ft_strcmp(line->line, limit) && g_ctrlr)
	{
		heredoc = ft_expend_2dstr(heredoc, line->line);
		ft_strdel(&line->line);
		readline(line, INCOMPLETE);
		if (!line->line)
		{
			ft_strdel(&limit);
			return (heredoc);
		}
	}
	ft_strdel(&limit);
	ft_strdel(&line->line);
	return (heredoc);
}

t_list		*ft_create_redir(t_redir *redir, t_list *tmp)
{
	if (((t_token *)tmp->content)->type == FD)
	{
		redir->fd = ft_atoi(((t_token *)tmp->content)->lexem);
		tmp = tmp->next;
	}
	else
		redir->fd = -42;
	redir->type = ((t_token *)tmp->content)->type * -1 - 10;
	signal_ctrlr();
	if (((t_token *)tmp->content)->type == DLESS)
		redir->heredoc = ft_heredoc(tmp);
	else
		redir->heredoc = NULL;
	signal(SIGINT, ft_ctrlc);
	redir->heredoc_bool = g_ctrlr;
	g_ctrlr = 0;
	redir->next = NULL;
	tmp = tmp->next;
	redir->target = ft_strdup(((t_token *)tmp->content)->lexem);
	return (tmp);
}

t_list		*ft_add_redir(t_redir **redir, t_list *tmp)
{
	t_redir	*tmp_redir;

	tmp_redir = *redir;
	while (tmp_redir && tmp_redir->next)
		tmp_redir = tmp_redir->next;
	if (!*redir)
	{
		if (!(*redir = (t_redir *)malloc(sizeof(t_redir))))
			return (NULL);
		tmp_redir = *redir;
	}
	else if (!(tmp_redir->next = (t_redir *)malloc(sizeof(t_redir))))
		return (NULL);
	else if (tmp_redir->next)
		tmp_redir = tmp_redir->next;
	return (ft_create_redir(tmp_redir, tmp));
}

t_ast		*ast_init(t_list *token_list)
{
	t_ast	*ast;
	t_list	*tmp;

	tmp = token_list;
	ast = create_ast_node(0);
	make_ast(ast, tmp);
	return (ast);
}
