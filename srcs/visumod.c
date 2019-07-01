/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visumod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 17:01:42 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/18 20:04:15 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key		g_visutab[] =\
{
	{K_ALTV, &k_visuend},
	{K_LEFT, &k_vleft},
	{K_RGHT, &k_vright},
	{K_CTRLX, &k_ctrlx},
	{K_ALTC, &k_altc},
	{K_CTRLV, &k_ctrlv},
};

void	reset_visu(t_line *line, int begin, int end)
{
//	int		i;
	char	*sub;

	sub = ft_strsub(line->line, begin, end - begin);
//	i = begin - 1;
	left(line, line->index - begin);
	tgetputstr("me");
	tgetputstr("ei");
	write_str(line, sub);
	tgetputstr("im");
	free(sub);
	if (line->index == begin)
		left(line, end - begin);
	get_cursor_position(&line->pos.col, &line->pos.row);
	if (line->pos.col == line->nb_col - 1)
		tgetputstr("do");
}

void	print_visu(t_line *line, int begin, int end)
{
//	int		i;
	char	*sub;

	sub = ft_strsub(line->line, begin, end - begin);
//	i = begin - 1;
	left(line, line->index - begin);
	tgetputstr("mr");
	tgetputstr("ei");
	write_str(line, sub);
	tgetputstr("im");
	tgetputstr("me");
	free(sub);
	if (line->index == begin)
		left(line, end - begin);
	get_cursor_position(&line->pos.col, &line->pos.row);
	if (line->pos.col == line->nb_col - 1)
		tgetputstr("do");
}

void	fill_visu(t_line *line)
{
	if (line->visu.begin > line->visu.current)
	{
		line->visu.smaller = line->visu.current;
		line->visu.bigger = line->visu.begin;
	}
	else
	{
		line->visu.smaller = line->visu.begin;
		line->visu.bigger = line->visu.current;
	}
}

void	k_visuinit(t_line *line)
{
	if (line->index != (int)ft_strlen(line->line))
		line->visu.begin = line->index + 1;
	else
		line->visu.begin = line->index;
	line->visu.current = line->index;
	g_tbl = g_visutab;
}

void	k_visuend(t_line *line)
{
	g_tbl = g_normal_tbl;
	fill_visu(line);
	if (line->visu.bigger - line->visu.smaller)
		reset_visu(line, line->visu.smaller, line->visu.bigger);
	line->visu.current = 0;
	line->visu.begin = 0;
}
