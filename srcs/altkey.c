/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   altkey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:21:16 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/10 22:42:11 by alagroy-         ###   ########.fr       */
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
	if (line->index + 3 < line->nb_col)
		return (tgetputstr("bl"));
	tgetputstr("up");
	line->index -= line->nb_col;
}

void	k_altdown(t_line *line)
{
	if (line->index  == (int)ft_strlen(line->line))
		return (tgetputstr("bl"));
	if (line->index + line->nb_col < (int)ft_strlen(line->line))
	{
		get_cursor_position(&line->pos.col, &line->pos.row);
		tputs(tgoto(line->caps.cm, (line->index + 3) % line->nb_col,
					line->pos.row + 1), 0, ft_putc);
		line->index += line->nb_col;
		return ;
	}
	get_cursor_position(&line->pos.col, &line->pos.row);
	tputs(tgoto(line->caps.cm, (ft_strlen(line->line) + 3) % line->nb_col,
				line->pos.row + 1), 0, ft_putc);
	line->index = ft_strlen(line->line);
}
