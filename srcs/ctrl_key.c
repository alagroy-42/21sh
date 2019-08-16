/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 18:42:55 by alagroy-          #+#    #+#             */
/*   Updated: 2019/08/16 16:12:41 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "signal_21sh.h"

void		k_ctrld(t_line *line)
{
	if (line->line[0])
		return (tgetputstr("bl"));
	ft_strdel(&line->line);
	if (!ft_strcmp(line->prompt, "$> "))
	{
		write(0, "\n", 1);
		ft_quit(0);
	}
}

void		k_ctrll(t_line *line)
{
	tgetputstr("cl");
	tputs(line->prompt, 0, ft_putc);
	tputs(line->line, 0, ft_putc);
	get_back_to_index(line);
}
