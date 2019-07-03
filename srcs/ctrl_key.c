/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 18:42:55 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/03 15:20:21 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	k_ctrld(t_line *line)
{
	ft_strdel(&line->line);
	ft_quit(0);
}

void	k_ctrll(t_line *line)
{
	tgetputstr("cl");
	tputs(line->prompt, 0, ft_putc);
	tputs(line->line, 0, ft_putc);
	get_back_to_index(line);
}
