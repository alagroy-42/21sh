/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_generate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 08:22:40 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/23 14:35:20 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "ast.h"

static void		make_sep(t_ast *ast, t_list *tmp)
{
	if (!tmp || !(((t_token *)tmp->content)->type == OR_IF
			|| ((t_token *)tmp->content)->type == AND_IF
			|| ((t_token *)tmp->content)->type == SEMICOL))
		return ;
	if (!(ast->sep = (t_sep *)malloc(sizeof(t_sep))))
		return ;
	((t_token *)tmp->content)->type == OR_IF ? ast->sep->sep = or_if : 0;
	((t_token *)tmp->content)->type == AND_IF ? ast->sep->sep = and_if : 0;
	((t_token *)tmp->content)->type == SEMICOL ? ast->sep->sep = semicol : 0;
	tmp = tmp->next;
	ast->sep->next = create_ast_node(0);
	make_ast(ast->sep->next, tmp);
}

static t_list	*make_pipe(t_ast *ast, t_list *tmp)
{
	if (((t_token *)tmp->content)->type != PIPE)
		return (tmp);
	ast->pipe = create_ast_node(1);
	tmp = tmp->next;
	make_ast(ast->pipe, tmp);
	return (tmp);
}

static t_list	*make_redir(t_ast *ast, t_list *tmp)
{
	while (tmp && ((((t_token *)tmp->content)->type >= GREATAND
			&& ((t_token *)tmp->content)->type <= LESS)
			|| ((t_token *)tmp->content)->type == FD))
	{
			tmp = ft_add_redir(&ast->redir, tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

static t_list	*make_cmd(t_ast *ast, t_list *tmp)
{
	while (tmp && ((t_token *)tmp->content)->type == WORD)
	{
		ast->args = ft_expend_2dstr(ast->args,
				((t_token *)tmp->content)->lexem);
		tmp = tmp->next;
	}
	if (ast->args)
		ast->cmd = ast->args[0];
	return (tmp);
}

void			make_ast(t_ast *ast, t_list *tmp)
{
	while (((t_token *)tmp->content)->type != PIPE
			&& ((t_token *)tmp->content)->type != OR_IF
			&& ((t_token *)tmp->content)->type != AND_IF
			&& ((t_token *)tmp->content)->type != SEMICOL
			&& ((t_token *)tmp->content)->type != EOI)
	{
		tmp = make_cmd(ast, tmp);
		tmp = make_redir(ast, tmp);
	}
	tmp = make_pipe(ast, tmp);
	make_sep(ast, tmp);
}
