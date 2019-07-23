/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 11:48:40 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/23 14:36:40 by alagroy-         ###   ########.fr       */
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
			ft_dprintf(0, "type:%d\nfd:%d\ntarget:%s\nfd_target:%d\n",
					redir->type, redir->fd, redir->target, redir->fd_target);
		tmp = tmp->next;
	}
}

void		display_ast(t_ast *ast)
{
	ft_putendl("\ncmd :");
	ft_print_2da(ast->args);
	ft_putendl("redir :");
	ft_aff_redir(ast->redir);
	ft_putendl("pipe :");
	if (ast->pipe)
		display_ast(ast->pipe);
	if (ast->sep)
	{
		ft_putendl("sep :");
		display_ast(ast->sep->next);
	}
}
