/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:15:08 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/05 18:33:26 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"

int			g_sym_tab[NBR_SYMBOL] =\
{
	WORD,
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

int			g_parse_tab[5][NBR_SYMBOL] =\
{
	{1, -1, -1, -1, 2, 2, 2, 2, -1, 2, -1, -42},
	{1, 3, 4, 4, 2, 2, 2, 2, 2, 2, 1, -42},
	{1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2},
	{1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2},
};

int			parse_cmd(t_list *token_list)
{
	t_list	*tmp;
	int		i;
	int		state;
	int		symbol;

	state = 0;
	tmp = token_list;
	while (state >= 0)
	{
		i = -1;
		tmp = state == 0 ? tmp : tmp->next;
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
