/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:53:48 by alagroy-          #+#    #+#             */
/*   Updated: 2019/05/13 18:13:21 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		ft_putc(int c)
{
	write(0, &c, 1);
	return (0);
}

int		ft_termcap(char *buf, t_line *line)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2])
	{
		if (buf[2] == 'D' && line->index > 0)
		{
			tputs(line->caps.le, 0, ft_putc);
			line->index--;
		}
		else if (buf[2] == 'C' && line->index < (int)ft_strlen(line->line))
		{
			tputs(line->caps.nd, 0, ft_putc);
			line->index++;
		}
		else if (buf[2] == 'H')
		{
			line->index < line->nb_col ? tputs(tgoto(line->caps.ch, 0, 3), 0,
					ft_putc) : tputs(tgoto(line->caps.ch, 0, 0), 0, ft_putc);
			line->index = line->index < line->nb_col ? 0
				: line->index - line->index % line->nb_col;
		}
		else if (buf[2] == 'F')
		{
			line->index < line->nb_col ? tputs(tgoto(line->caps.ch, 0,
						ft_strlen(line->line) + 3), 0, ft_putc) : 0;
			line->index = ft_strlen(line->line);
		}
	}
	return (0);
}

int		readline(t_line *line)
{
	char	buf[4];
	int		ret;

	line->index = 0;
	line->line = ft_strnew(1);
	ft_putstr("$> ");
	tputs(line->caps.im, 0, ft_putc);
	while ((ret = read(0, buf, 3)))
	{
		buf[ret] = '\0';
		if (buf[0] == '\n' && !buf[1])
			return (ft_printf("\n"));
		else if (ret > 1)
			ft_termcap(buf, line);
		else if (buf[0] == 127 && ret == 1 && line->index > 0)
		{
			tputs(line->caps.le, 0, ft_putc);
			tputs(line->caps.dc, 0, ft_putc);
			line->line = ft_delete_flags(line->line, --line->index, 1);
		}
		else if (buf[0] != 127)
		{
			ft_putchar_fd(buf[0], 0);
			line->line = ft_insert_str(line->line, ft_strdup(buf), line->index);
			line->index++;
		}
	}
	return (0);
}
