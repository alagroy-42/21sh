/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:53:48 by alagroy-          #+#    #+#             */
/*   Updated: 2019/05/28 03:59:22 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key	g_tbl[] =\
{
	{K_LEFT, &k_left},
	{K_RGHT, &k_right},
	{K_HOME, &k_home},
	{K_END, &k_end},
	{K_BSPC, &k_backspace},
	{NULL, &k_left}
};

int		ft_putc(int c)
{
	write(0, &c, 1);
	return (0);
}

void	ft_termcap(char *buf, t_line *line)
{
	int		i;

	i = -1;
	while (g_tbl[++i].key)
	{
		if (!ft_strcmp(buf, g_tbl[i].key))
			return (g_tbl[i].f(line));
	}
}

int		readline(t_line *line)
{
	char	buf[10];
	int		ret;

	line->index = 0;
	line->line = ft_strnew(1);
	ft_putstr("$> ");
	tputs(line->caps.im, 0, ft_putc);
	while ((ret = read(0, buf, 9)))
	{
		buf[ret] = '\0';
		if (buf[0] == '\n' && !buf[1])
			return (ft_printf("\n"));
		else if (!ft_isprint(buf[0]) || ret > 1)
			ft_termcap(buf, line);
		else
		{
			ft_putchar_fd(buf[0], 0);
			line->line = ft_insert_str(line->line, ft_strdup(buf), line->index);
			line->index++;
		}
	}
	return (0);
}
