/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 18:42:55 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/08 19:20:28 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	k_ctrll(t_line *line)
{
	tgetputstr("cl");
	tputs("$> ", 0, ft_putc);
	tputs(line->line, 0, ft_putc);
	get_back_to_index(line);
}
