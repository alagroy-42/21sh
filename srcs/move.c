/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:12:35 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/20 18:17:47 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	k_left(t_line *line)
{
	get_cursor_position(&line->pos.col, &line->pos.row);
	if (line->pos.col == 0)
	{
		tgetputstr("up");
		tputs(tgoto(line->caps.ch, 0, line->nb_col - 2), 0, ft_putc);
		line->index--;
	}
	else if (line->index > 0)
	{
		tputs(line->caps.le, 0, ft_putc);
		line->index--;
	}
	else
		tgetputstr("bl");
}

void	k_right(t_line *line)
{
	get_cursor_position(&line->pos.col, &line->pos.row);
	if (line->index < (int)ft_strlen(line->line))
	{
		if (line->pos.col == line->nb_col - 2)
		{
			tputs(line->caps.dow, 0, ft_putc);
			tputs(line->caps.cr, 0, ft_putc);
		}
		else
			tputs(line->caps.nd, 0, ft_putc);
		line->index++;
	}
}

void	k_home(t_line *line)
{
	if (line->index == 0)
		return (tgetputstr("bl"));
	left(line, line->index);
	line->index = 0;
}

void	k_end(t_line *line)
{
	if (line->index == (int)ft_strlen(line->line))
		return (tgetputstr("bl"));
	right(line, ft_strlen(line->line) - line->index);
	line->index = ft_strlen(line->line);
}

void	k_backspace(t_line *line)
{
	if (line->index <= 0)
		return (tgetputstr("bl"));
	k_left(line);
	line->line = ft_delete_flags(line->line, line->index, 1);
	get_cursor_position(&line->pos.col, &line->pos.row);
	tputs(line->caps.cr, 0, ft_putc);
	tputs(line->caps.cd, 0, ft_putc);
	if (line->index + 3 < line->nb_col - 1)
	{
		ft_putstr_fd("$> ", 0);
		write_str(line, line->line);
	}
	else
		write_str(line, line->line + line->index - line->pos.col);
		left(line, (int)ft_strlen(line->line) - line->index);
}
