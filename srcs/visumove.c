/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visumove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 17:45:57 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/18 19:58:20 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	k_vleft(t_line *line)
{
	if (line->visu.current == 0)
		return (tgetputstr("bl"));
	fill_visu(line);
	reset_visu(line, line->visu.smaller, line->visu.bigger);
	line->visu.current--;
	fill_visu(line);
	k_left(line);
	print_visu(line, line->visu.smaller, line->visu.bigger);
}

void	k_vright(t_line *line)
{
	if (line->visu.current == (int)ft_strlen(line->line) || (!line->visu.current
				&& !line->visu.begin && line->visu.clipboard))
		return (tgetputstr("bl"));
	fill_visu(line);
	reset_visu(line, line->visu.smaller, line->visu.bigger);
	line->visu.current++;
	k_right(line);
	fill_visu(line);
	print_visu(line, line->visu.smaller, line->visu.bigger);
}
