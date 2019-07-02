/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:15:08 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/02 19:57:16 by alagroy-         ###   ########.fr       */
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
	{-1, 6, 3, 4, 4, 2, 2, 2, 2, 2, 2, 0, -42},
	{-1, -1, -1, -1, -1, 2, 2, -1, 2, 2, 2, -1, -1},
};

int			parse_cmd(t_list *token_list)
{
	t_list	*tmp;
	int		i;
	int		state;
	int		symbol;

	state = 0;
	if (!token_list)
		return (-1);
	tmp = token_list;
	while (state >= 0)
	{
		i = -1;
		tmp = tmp == token_list && state == 0 ? tmp : tmp->next;
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
