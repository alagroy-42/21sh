/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 18:42:55 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/17 17:35:04 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "signal_21sh.h"

void		k_ctrld(t_line *line)
{
	if (line->line[0] && line->index != (int)ft_strlen(line->line))
	{
		k_right(line);
		k_backspace(line);
		return ;
	}
	if (line->line[0])
		return (tgetputstr("bl"));
	ft_strdel(&line->line);
	if (!ft_strcmp(line->prompt, "$> "))
	{
		write(2, "\n", 1);
		ft_quit(0);
	}
}

void		k_ctrll(t_line *line)
{
	tgetputstr("cl");
	tputs(line->prompt, 2, ft_putc);
	tputs(line->line, 2, ft_putc);
	get_back_to_index(line);
}
