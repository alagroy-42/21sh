/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:39:13 by alagroy-          #+#    #+#             */
/*   Updated: 2019/05/24 11:29:59 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	get_back_to_index(t_line *line)
{
	int		cursor;

	cursor = ft_strlen(line->line);
	while (--cursor >= line->index + 1)
		tputs(line->caps.le, 0, ft_putc);
}
