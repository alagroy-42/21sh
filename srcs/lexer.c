/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 09:53:09 by alagroy-          #+#    #+#             */
/*   Updated: 2019/05/24 14:01:56 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		is_aseparator(char c)
{
	if (c == ' ' || c == 39 || c == 34)
		return (1);
	else
		return (0);
}

static char		*make_token(char *line, int *i)
{
	char	c;
	int		index;

	c = line[*i];
	index = ++(*i);
	while (line[*i] && line[*i] != c)
		(*i)++;
	return (ft_strsub(line, index, (*i - index)));
}

static t_list	*create_first_token(char *line, int *i)
{
	char	*content;
	char	c;
	int		index;
	t_list	*begin;
	
	if (!is_aseparator(line[0]))
		c = ' ';
	else
	{
		c = line[0];
		(*i)++;
	}
	index = (*i)++;
	while (line[*i] && line[*i] != c)
		(*i)++;
	if (!(content = ft_strsub(line, index, (*i - index))))
		return (NULL);
	begin = ft_lstnew(content, ft_strlen(content));
	ft_strdel(&content);
	return (begin);
}

t_list			*lex_line(char *line)
{
	t_list	*begin;
	t_list	*elem;
	char	*content;
	int		i;

	i = 0;
	begin = create_first_token(line, &i);
	while (line[i] && line[i + 1])
	{
		if (is_aseparator(line[i]) && !is_aseparator(line[i + 1]))
		{
			content = make_token(line, &i);
			elem = ft_lstnew(content, ft_strlen(content));
			if (!begin)
				begin = elem;
			else if (elem)
				ft_lstend(&begin, elem);
			ft_strdel(&content);
		}
		else
			i++;
	}
	return (begin);
}
