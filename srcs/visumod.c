/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visumod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 17:01:42 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/02 15:06:18 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key		g_visutab[] =\
{
	{K_ALTB, &k_visuend},
	{K_LEFT, &k_vleft},
	{K_RGHT, &k_vright},
	{K_ALTX, &k_altx},
	{K_ALTC, &k_altc},
	{K_ALTV, &k_altv},
};

void	reset_visu(t_line *line)
{
	int		len;
	char	*sub;

	len = line->visu.offset < 0 ? line->visu.offset * -1 : line->visu.offset;
	len++;
	if (!(sub = ft_strsub(line->line, line->visu.offset < 0 ? line->visu.begin
					+ line->visu.offset : line->visu.begin, len)))
		return ;
	if (line->visu.offset > 0)
		left(line, len - 1);
	tgetputstr("ei");
	write_str(line, sub);
	tgetputstr("im");
	get_cursor_position(&line->pos.col, &line->pos.row);
	if (line->visu.offset <= 0)
		left(line, len);
	else if (line->visu.begin + line->visu.offset != (int)ft_strlen(line->line))
		left(line, 1);
	ft_strdel(&sub);
}

void	print_visu(t_line *line)
{
	int		len;
	char	*sub;

	len = line->visu.offset < 0 ? line->visu.offset * -1 : line->visu.offset;
	len++;
	if (!(sub = ft_strsub(line->line, line->visu.offset < 0 ? line->visu.begin
					+ line->visu.offset : line->visu.begin, len)))
		return ;
	if (line->visu.offset > 0)
		left(line, len - 1);
	tgetputstr("mr");
	tgetputstr("ei");
	write_str(line, sub);
	tgetputstr("im");
	tgetputstr("me");
	get_cursor_position(&line->pos.col, &line->pos.row);
	if (line->visu.offset <= 0)
		left(line, len);
	else if (line->visu.begin + line->visu.offset != (int)ft_strlen(line->line))
		left(line, 1);
	ft_strdel(&sub);
}

void	k_visuinit(t_line *line)
{
	if (!ft_strlen(line->line))
		return (tgetputstr("bl"));
	if (line->index == (int)ft_strlen(line->line))
		k_left(line);
	line->visu.begin = line->index;
	line->visu.offset = 0;
	line->visu.clipboard = NULL;
	g_tbl = g_visutab;
}

void	k_visuend(t_line *line)
{
	g_tbl = g_normal_tbl;
	reset_visu(line);
	ft_strdel(&line->visu.clipboard);
	line->visu.offset = 0;
	line->visu.begin = 0;
}
