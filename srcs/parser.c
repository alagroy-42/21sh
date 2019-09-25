/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:15:08 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/25 11:32:05 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"

int			g_sym_tab[NBR_SYMBOL] =\
{
	WORD,
	FD,
	PIPE,
	OR_IF,
	AND_IF,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	GREATAND,
	LESSAND,
	SEMICOL,
	EOI,
};

int			g_parse_tab[7][NBR_SYMBOL] =\
{
	{1, 6, -1, -1, -1, 2, 2, 2, 2, -1, 2, -1, -42},
	{1, 6, 3, 4, 4, 2, 2, 2, 2, 2, 2, 0, -42},
	{5, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2},
	{1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2},
	{1, 6, 3, 4, 4, 2, 2, 2, 2, 2, 2, 0, -42},
	{-1, -1, -1, -1, -1, 2, 2, -1, 2, 2, 2, -1, -1},
};

static int	is_redir(t_list *token)
{
	if (!token)
		return (0);
	if (((t_token *)token->content)->type < -9
			&& ((t_token *)token->content)->type > -16)
		return (1);
	return (0);
}

static void	check_fd(t_list *token_list)
{
	t_list	*tmp;

	tmp = token_list;
	if (((t_token *)tmp->content)->type == FD && !is_redir(tmp->next))
		((t_token *)tmp->next->content)->type = WORD;
	while (tmp && tmp->next)
	{
		if (((t_token *)tmp->next->content)->type == FD && !is_redir(tmp)
				&& !is_redir(tmp->next->next))
			((t_token *)tmp->next->content)->type = WORD;
		tmp = tmp->next;
	}
}

int			parse_cmd(t_list *token_list)
{
	t_list	*tmp;
	int		i;
	int		state;
	int		symbol;

	state = 0;
	if (!token_list)
		return (-1);
	check_fd(token_list);
	tmp = token_list;
	while (state >= 0)
	{
		i = -1;
		tmp = tmp == token_list && state == 0 ? tmp : tmp->next;
		if (!tmp)
			return (-1);
		while (++i < NBR_SYMBOL)
			if (g_sym_tab[i] == ((t_token *)tmp->content)->type)
				symbol = i;
		state = g_parse_tab[state][symbol];
	}
	if (state == -1)
		ft_dprintf(2, "21sh: Parse error near '%s'\n",
				((t_token *)tmp->content)->lexem);
	return (state);
}
