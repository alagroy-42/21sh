/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 11:52:57 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/02 19:50:52 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer_parser.h"

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
			return (1);
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
	while (parse_return != -42 && parse_return != -1)
	{
		parse_return = 1;
		tmp_str = line_str;
		line_str = ft_strjoin(line_str, line->line);
		ft_strdel(&tmp_str);
		if (lex_routine(line, line_str, lex))
			continue ;
		parse_return = parse_cmd(*lex);
		if (parse_return == -2)
			readline(line, INCOMPLETE);
	}
	return (parse_return);
}
