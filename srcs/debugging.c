/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 11:48:40 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/08 13:09:39 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "ast.h"

void		aff_token(t_list *token)
{
	t_list	*tmp;

	tmp = token;
	while (tmp)
	{
		ft_printf("lexem : |%s|, type : %d\n", ((t_token *)tmp->content)->lexem,
				((t_token *)tmp->content)->type);
		tmp = tmp->next;
	}
}

void		ft_aff_redir(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp && tmp->target)
			ft_putendl(tmp->target);
		tmp = tmp->next;
	}
}

void		display_ast(t_ast *ast)
{
	ft_putendl("\ncmd :");
	ft_print_2da(ast->args);
	ft_putendl("input :");
	ft_aff_redir(ast->input);
	ft_putendl("output :");
	ft_aff_redir(ast->output);
	ft_putendl("pipe :");
	if (ast->pipe)
		display_ast(ast->pipe);
	if (ast->sep)
	{
		ft_putendl("sep :");
		display_ast(ast->sep->next);
	}
}
