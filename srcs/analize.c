/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 11:52:57 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/26 14:09:11 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer_parser.h"
#include "signal_21sh.h"
#include "ast.h"

extern int	g_ctrlr;

int			ft_check_ast(t_ast *ast)
{
	t_ast	*tmp;
	t_redir	*tmp_r;

	if (!ast)
		return (0);
	tmp = ast;
	while (tmp)
	{
		tmp_r = tmp->redir;
		while (tmp_r)
		{
			if (tmp_r->type == dless && !tmp_r->heredoc_bool)
				return (0);
			tmp_r = tmp_r->next;
		}
		if (tmp->pipe)
			tmp = tmp->pipe;
		else if (tmp->sep && tmp->sep->next)
			tmp = tmp->sep->next;
		else
			break ;
	}
	return (1);
}

static int	lex_routine(t_line *line, char *line_str, t_list **lex)
{
	t_list	*tmp;

	*lex = lex_line(line_str);
	if (!*lex)
		return (0);
	tmp = *lex;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type < -1
				&& ((t_token *)tmp->content)->type > -4)
		{
			readline(line, INCOMPLETE);
			return (g_ctrlr);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			analize_line(t_line *line, t_list **lex)
{
	int		parse_return;
	char	*line_str;
	char	*tmp_str;

	parse_return = 1;
	line_str = ft_strnew(0);
	signal_ctrlr();
	while (parse_return != -42 && parse_return != -1)
	{
		ft_lstdel(lex, ft_del_token);
		parse_return = 1;
		tmp_str = line_str;
		line_str = ft_strjoin(line_str, line->line);
		ft_strdel(&tmp_str);
		ft_strdel(&line->line);
		if (lex_routine(line, line_str, lex))
			continue ;
		parse_return = parse_cmd(*lex);
		if (parse_return == -2 && g_ctrlr)
			readline(line, INCOMPLETE);
	}
	ft_strdel(&line_str);
	ft_strdel(&line->line);
	signal(SIGINT, ft_ctrlc);
	return (parse_return);
}
