/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:17:29 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/26 19:21:33 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	k_altx(t_line *line)
{
	int		len;
	int		beg;
	int		up;

	beg = line->visu.offset < 0 ? line->visu.begin + line->visu.offset
		: line->visu.begin;
	len = line->visu.offset < 0 ? line->visu.offset * -1 : line->visu.offset;
	len++;
	ft_strdel(&line->visu.clipboard);
	if (!(line->visu.clipboard = ft_strsub(line->line, beg, len)))
		return ;
	line->line = ft_delete_flags(line->line, beg, len);
	if (line->index != beg)
		left(line, len - 1);
	get_cursor_position(&line->pos.col, &line->pos.row);
	up = (beg + 3) / (line->nb_col ? line->nb_col : 1);
	tputs(line->caps.cr, 2, ft_putc);
	tputs(line->caps.cd, 2, ft_putc);
	while (up--)
		tgetputstr("up");
	ft_dprintf(2, "%s%s", line->prompt, line->line);
	tputs(tgoto(line->caps.cm, line->pos.col, line->pos.row), 2, ft_putc);
	line->visu.begin = beg;
	line->index = beg;
	line->visu.offset = 0;
}

void	k_altc(t_line *line)
{
	int		len;
	int		beg;

	beg = line->visu.offset < 0 ? line->visu.begin + line->visu.offset
		: line->visu.begin;
	len = line->visu.offset < 0 ? line->visu.offset * -1 : line->visu.offset;
	len++;
	if (!(line->visu.clipboard = ft_strsub(line->line, beg, len)))
		return ;
	reset_visu(line);
	line->visu.offset = 0;
}

void	k_altv(t_line *line)
{
	int		up;
	int		len;

	if (!line->visu.clipboard)
		return ;
	up = (line->index + 3) / (line->nb_col ? line->nb_col : 1);
	line->line = ft_insert_str(line->line, ft_strdup(line->visu.clipboard),
			line->index);
	get_cursor_position(&line->pos.col, &line->pos.row);
	while (up--)
		tgetputstr("up");
	tputs(line->caps.cr, 2, ft_putc);
	tputs(line->caps.cd, 2, ft_putc);
	ft_dprintf(2, "%s%s", line->prompt, line->line);
	tputs(tgoto(line->caps.cm, line->pos.col, line->pos.row), 2, ft_putc);
	len = ft_strlen(line->visu.clipboard);
	while (len--)
		k_right(line);
}
