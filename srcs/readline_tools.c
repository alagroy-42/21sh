/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:39:13 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/09 17:41:09 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	get_cursor_position(int *col, int *rows)
{
	int		i;
	char	buf[17];

	write(1, "\033[6n", 4);
	if ((i = read(0, buf, 16)) <= 0)
		return ;
	buf[i] = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '[')
			*rows = ft_atoi(&buf[i + 1]) - 1;
		if (buf[i] == ';')
			*col = ft_atoi(&buf[i + 1]) - 1;
		i++;
	}
}

void	get_back_to_index(t_line *line)
{
	int		cursor;

	cursor = ft_strlen(line->line);
	while (--cursor >= line->index)
		tputs(line->caps.le, 2, ft_putc);
}

void	tgetputstr(char *s)
{
	char	*cap;

	if (!(cap = tgetstr(s, NULL)))
		return ;
	tputs(cap, 2, ft_putc);
}
