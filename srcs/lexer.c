/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 09:53:09 by alagroy-          #+#    #+#             */
/*   Updated: 2019/05/28 07:11:14 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		(*g_func[NBR_FUNC])(char) =\
{
	ft_is_whitespace,
	ft_is_eoi,
	ft_is_dquote,
	ft_is_quote,
	ft_is_alnum,
	ft_is_pipe,
	ft_is_amper,
	ft_is_less,
	ft_is_great,
	ft_is_semicol
};

int		g_state_tab[8][NBR_FUNC] =\
{
	{0, -17, 3, 2, 1, 4, 5, 6, 7, -16},
	{-25, -25, -26, -26, 1, -25, -25, -25, -25},
	{2, -2, 2, -45, 2, 2, 2, 2, 2, 2},
	{3, -3, -45, 3, 3, 3, 3, 3, 3, 3},
	{-7, -1, -27, -27, -27, -8, -1, -1, -1, -1},
	{-8, -1, -8, -8, -8, -1, -9, -1, -1, -1},
	{-10, -1, -30, -30, -30, -1, -14, -12, -1, -1},
	{-11, -1, -31, -31, -31, -1, -15, -1, -13, -1}
};

t_token	*make_next_token(t_token *token, char *line)
{
	static int	i = 0;
	int			j;
	int			state;
	int			begin;

	begin = -1;
	state = 0;
	token->type == -42 ? i = 0 : 0;
	while (state >= 0)
	{
		j = -1;
		while (++j < NBR_FUNC)
			if (g_func[j](line[i]))
				state = g_state_tab[state][j];
		state != 0 && begin == -1 ? begin = i : 0;
		i++;
	}
	i -= (state < -17 ? 1 : 0);
	begin += (state < -40 ? 1 : 0);
	token->lexem = ft_strsub(line, begin, i - begin);
	state < -40 ? i++ : 0;
	token->type = state + (state < -17 ? 20 : 0);
	(state < -40 ? token->type += 20 : 0);
	return (token);
}
#include <stdio.h>
t_list	*lex_line(char *line)
{
	t_list	*begin;
	t_list	*elem;
	t_token	*token;

	begin = NULL;
	elem = NULL;
	if (!(token = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	token->type = -42;
	while (token->type != EOI && token->type < -4)
	{
		token = make_next_token(token, line);
		ft_printf("lexem = %s, type = %d\n", token->lexem, token->type);
		getchar();
		ft_strdel(&token->lexem);
		if (!(elem = ft_lstnew(token, sizeof(token))))
			return (NULL);
		if (!begin)
			begin = elem;
		else
			ft_lstend(&begin, elem);
	}
	free(token);
	return (begin);
}
