/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   altkey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:21:16 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/15 16:41:09 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	k_altleft(t_line *line)
{
	if (line->index > 0 && line->line[line->index - 1] == ' ')
		k_left(line);
	while (line->index > 0 && line->line[line->index - 1] != ' ')
		k_left(line);
}

void	k_altright(t_line *line)
{
	if (line->index < (int)ft_strlen(line->line)
			&& line->line[line->index + 1] == ' ')
		k_right(line);
	while (line->index < (int)ft_strlen(line->line)
			&& line->line[line->index + 1] && line->line[line->index + 1] != 32)
		k_right(line);
}

void	k_altup(t_line *line)
{
	if (line->index == 0)
		return (tgetputstr("bl"));
	if (line->index < line->nb_col)
	{
		while (line->index)
			k_left(line);
		return ;
	}
	tgetputstr("up");
	line->index -= (line->nb_col - 1);
}

void	k_altdown(t_line *line)
{
	if (line->index == (int)ft_strlen(line->line))
		return (tgetputstr("bl"));
	get_cursor_position(&line->pos.col, &line->pos.row);
	if (line->index + line->nb_col < (int)ft_strlen(line->line))
	{
		tputs(tgoto(line->caps.cm, line->pos.col,
					line->pos.row + 1), 0, ft_putc);
		line->index += (line->nb_col - 1);
		return ;
	}
	tputs(tgoto(line->caps.cm, (ft_strlen(line->line) + 3) % (line->nb_col - 1),
				line->pos.row + 1), 0, ft_putc);
	line->index = ft_strlen(line->line);
}
