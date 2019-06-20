/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:17:29 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/20 18:36:23 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	k_ctrlx(t_line *line)
{
	int		len;
	int		right;

	fill_visu(line);
	right = line->visu.bigger - line->index;
	len = line->visu.bigger - line->visu.smaller;
	ft_strdel(&line->visu.clipboard);
	line->visu.clipboard = ft_strsub(line->line, line->visu.smaller, len);
	reset_visu(line, line->visu.smaller, line->visu.bigger);
	while (right--)
		k_right(line);
	while (len--)
		k_backspace(line);
	line->visu.begin = 0;
	line->visu.current = 0;
}

void	k_altc(t_line *line)
{
	ft_strdel(&line->visu.clipboard);
	fill_visu(line);
	line->visu.clipboard = ft_strsub(line->line, line->visu.smaller,
			line->visu.bigger - line->visu.smaller);
	reset_visu(line, line->visu.smaller, line->visu.bigger);
	line->visu.begin = 0;
	line->visu.current = 0;
}

void	k_ctrlv(t_line *line)
{
	char	*sub;
	int		i;

	i = -1;
	while (line->visu.clipboard[++i])
	{
		sub = ft_strsub(line->visu.clipboard, i, 1);
		write_char(line, sub);
		free(sub);
	}
}
