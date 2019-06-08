/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:12:35 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/08 17:37:43 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	k_left(t_line *line)
{
	if (line->index > 0)
	{
		tputs(line->caps.le, 0, ft_putc);
		line->index--;
	}
}

void	k_right(t_line *line)
{
	if (line->index < (int)ft_strlen(line->line))
	{
		tputs(line->caps.nd, 0, ft_putc);
		line->index++;
		if (line->index + 3 == line->nb_col)
		{
			tputs(line->caps.dow, 0, ft_putc);
			tputs(tgoto(line->caps.ch, 0, 0), 0, ft_putc);
		}
	}
}

void	k_home(t_line *line)
{
	if (line->index  + 3 < line->nb_col)
		tputs(tgoto(line->caps.ch, 0, 3), 0, ft_putc);
	else
		tputs(tgoto(line->caps.ch, 0, 0), 0, ft_putc);
	if (line->index < line->nb_col)
		line->index = 0;
	else
		line->index = line->index - line->index % line->nb_col;
}

void	k_end(t_line *line)
{
	if ((line->index + 3) / line->nb_col == ((int)ft_strlen(line->line) + 3)
			/ line->nb_col)
	{
		tputs(tgoto(line->caps.ch, 0, ft_strlen(line->line) - line->index + 1),
				0, ft_putc);
		line->index = ft_strlen(line->line);
	}
	if (line->index + 3 <= line->nb_col)
	{
		tputs(tgoto(line->caps.ch, 0, ft_strlen(line->line) + 3), 0, ft_putc);
		line->index = ft_strlen(line->line);
	}
}

void	k_backspace(t_line *line)
{
	if (line->index <= 0)
		return ;
	tputs(line->caps.le, 0, ft_putc);
	tputs(line->caps.dc, 0, ft_putc);
	line->line = ft_delete_flags(line->line, --line->index, 1);
	get_cursor_position(&line->pos.col, &line->pos.row);
	if ((line->index + 3) / line->nb_col < ((int)ft_strlen(line->line) + 3)
			/ line->nb_col)
	{
		tputs(line->caps.cr, 0, ft_putc);
		tputs(line->caps.cd, 0, ft_putc);
		if ((line->index + 3) / line->nb_col == 0)
		{
			tputs("$> ", 0, ft_putc);
			tputs((line->line), 0, ft_putc);
		}
		else
			tputs((line->line + (size_t)(line->index - line->pos.col)), 0,
					ft_putc);
		get_back_to_index(line);
	}
}
