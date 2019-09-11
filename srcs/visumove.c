/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visumove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 17:45:57 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/11 19:26:44 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	k_vleft(t_line *line)
{
	if (line->index == 0)
		return (tgetputstr("bl"));
	if (!line->visu.clipboard)
	{
		reset_visu(line);
		line->visu.offset--;
	}
	k_left(line);
	if (!line->visu.clipboard)
		print_visu(line);
}

void	k_vright(t_line *line)
{
	if (line->index == (int)ft_strlen(line->line))
		return (tgetputstr("bl"));
	if (!line->visu.clipboard)
	{
		reset_visu(line);
		line->visu.offset++;
	}
	k_right(line);
	if (!line->visu.clipboard)
	{
		print_visu(line);
		get_cursor_position(&line->pos.col, &line->pos.row);
		if (line->pos.col == line->nb_col)
			tgetputstr("do");
	}
}
