/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 09:53:09 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/09 15:22:28 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"

int		(*g_func[NBR_FUNC])(char) =\
{
	ft_is_whitespace,
	ft_is_eoi,
	ft_is_dquote,
	ft_is_quote,
	ft_is_alpha,
	ft_is_digit,
	ft_is_pipe,
	ft_is_amper,
	ft_is_less,
	ft_is_great,
	ft_is_semicol
};

int		g_state_tab[10][NBR_FUNC] =\
{
	{0, -17, 3, 2, 1, 9, 4, 5, 6, 7, -16},
	{-25, -25, -26, -26, 1, 1, -25, -25, -25, -25, -25},
	{2, -2, 2, 8, 2, 2, 2, 2, 2, 2, 2},
	{3, -3, 8, 3, 3, 3, 3, 3, 3, 3, 3},
	{-27, -4, -27, -27, -27, -27, -8, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -9, -1, -1, -1},
	{-30, -1, -30, -30, -30, -30, -1, -14, -12, -1, -1},
	{-31, -1, -31, -31, -31, -31, -1, -15, -1, -13, -1},
	{-65, -65, -66, -66, -66, -66, -65, -65, -65, -65, -65},
	{-24, -25, -26, -26, 1, 1, -25, -25, -24, -24, -25}
};

int				ft_is_digit(char c)
{
	return (ft_isdigit((int)c));
}

void			ft_del_token(void *content, size_t content_size)
{
	free(((t_token *)content)->lexem);
	((t_token *)content)->lexem = NULL;
	free(content);
	content = NULL;
	(void)content_size;
}

static t_list	*merge_token(t_list *token_list)
{
	t_list	*tmp;
	t_list	*tmp_free;
	char	*lexem_free;

	tmp = token_list;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == WORD_JOIN)
		{
			tmp_free = tmp->next;
			lexem_free = ((t_token *)tmp->content)->lexem;
			((t_token *)tmp->content)->lexem =
				ft_strjoin(lexem_free, ((t_token *)tmp->next->content)->lexem);
			if (!((t_token *)tmp->content)->lexem)
				return (NULL);
			((t_token *)tmp->content)->type =
				((t_token *)tmp->next->content)->type;
			tmp->next = tmp->next->next;
			ft_lstdelone(&tmp_free, ft_del_token);
		}
		else
			tmp = tmp->next;
	}
	return (token_list);
}

static void		make_next_token(t_token *token, char *line)
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
	i -= (state < -60 ? 1 : 0);
	begin += (state < -40 ? 1 : 0);
	token->lexem = ft_strsub(line, begin, i - begin);
	state < -40 ? i++ : 0;
	token->type = state % 20;
}

static t_list	*lex_error_handle(t_list *token_list)
{
	t_list	*tmp;

	tmp = token_list;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == ERROR)
		{
			ft_printf("21sh: parse error near '%s'\n",
					((t_token *)tmp->content)->lexem);
			ft_lstdel(&token_list, ft_del_token);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (token_list);
}

t_list			*lex_line(char *line)
{
	t_list	*begin;
	t_list	*elem;
	t_token	*token;

	begin = NULL;
	elem = NULL;
	if (!(token = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	token->type = -42;
	while (token->type != EOI && token->type < -3 && line)
	{
		make_next_token(token, line);
		if (!(elem = ft_lstnew(token, sizeof(t_token))))
			return (NULL);
		if (!begin)
			begin = elem;
		else
			ft_lstend(&begin, elem);
	}
	free(token);
	merge_token(begin);
	begin = lex_error_handle(begin);
	return (begin);
}
