/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:35:19 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/08 11:58:55 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer_parser.h"

t_ast	*create_ast_node(int piped)
{
	t_ast	*node;

	if (!(node = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	node->cmd = NULL;
	node->args = NULL;
	node->input = NULL;
	node->output = NULL;
	node->sep = NULL;
	node->pipe = NULL;
	node->piped = piped;
	return (node);
}

t_list	*ft_add_redir(t_redir **redir, t_list *tmp)
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
	tmp_redir->type = ((t_token *)tmp->content)->type * -1 - 11;
	tmp = tmp->next;
	tmp_redir->target = ((t_token *)tmp->content)->lexem;
	return (tmp);
}

t_ast	*ast_init(t_list *token_list)
{
	t_ast	*ast;
	t_list	*tmp;

	tmp = token_list;
	ast = create_ast_node(0);
	make_ast(ast, tmp);
	return (ast);
}