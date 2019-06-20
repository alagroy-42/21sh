/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:27:56 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/20 18:14:44 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	write_str(t_line *line, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		get_cursor_position(&line->pos.col, &line->pos.row);
		if (line->pos.col == line->nb_col - 1)
			tgetputstr("do");
		ft_putchar_fd(str[i], 0);
	}
}

void	left(t_line *line, int len)
{
	int	up;
	int	le;
	int	i;

	up = len / (line->nb_col - 1);
	le = len % (line->nb_col - 1);
	i = -1;
	while (++i < up)
		tgetputstr("up");
	i = -1;
	while (++i < le)
	{
		get_cursor_position(&line->pos.col, &line->pos.row);
		if (line->pos.col == 0)
			tputs(tgoto(line->caps.cm, line->nb_col - 2, line->pos.row - 1), 0,
					ft_putc);
		else
			tgetputstr("le");
	}
}

void	right(t_line *line, int len)
{
	int	dow;
	int	nd;
	int	i;

	dow = len / (line->nb_col - 1);
	nd = len % (line->nb_col - 1);
	i = -1;
	while (++i < dow)
	{
		get_cursor_position(&line->pos.col, &line->pos.row);
		tputs(tgoto(line->caps.cm, line->pos.col, line->pos.row + 1), 0,
				ft_putc);
	}
	i = -1;
	while (++i < nd)
	{
		get_cursor_position(&line->pos.col, &line->pos.row);
		if (line->pos.col == line->nb_col - 2)
			tgetputstr("do");
		else
			tgetputstr("nd");
	}
}
