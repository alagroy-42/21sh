/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:53:48 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/15 16:18:27 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key		g_tbl[] =\
{
	{K_LEFT, &k_left},
	{K_RGHT, &k_right},
	{K_HOME, &k_home},
	{K_END, &k_end},
	{K_BSPC, &k_backspace},
	{K_UP, &k_up},
	{K_DOWN, &k_down},
	{K_CTRLL, &k_ctrll},
	{K_ALFT, &k_altleft},
	{K_ARGT, &k_altright},
	{K_AUP, &k_altup},
	{K_ADOWN, &k_altdown},
	{NULL, &k_left}
};

int			ft_putc(int c)
{
	return (write(0, &c, 1));
}

static void	ft_termcap(char *buf, t_line *line)
{
	int		i;

	i = -1;
	while (g_tbl[++i].key)
	{
		if (!ft_strcmp(buf, g_tbl[i].key))
			return (g_tbl[i].f(line));
	}
	tgetputstr("bl");
}

void		write_char(t_line *line, char *buf)
{
	ft_putchar_fd(buf[0], 0);
	line->line = ft_insert_str(line->line, ft_strdup(buf), line->index);
	line->index++;
	if ((line->index + 3) / line->nb_col < ((int)ft_strlen(line->line) + 4)
			/ line->nb_col)
	{
		tgetputstr("ei");
		tputs(line->line + line->index, 0, ft_putc);
		get_back_to_index(line);
		tgetputstr("im");
	}
	get_cursor_position(&line->pos.col, &line->pos.row);
	if (line->pos.col == line->nb_col - 1)
		tgetputstr("do");
}

static int	ft_eoi(t_line *line)
{
	int		len;

	len = ft_strlen(line->line);
	while (line->index < len)
		k_right(line);
	write_char(line, "\n");
	return (1);
}

int			readline(t_line *line, int status)
{
	char	buf[10];
	int		ret;

	line->history_index = 0;
	line->last_arrow = UP;
	line->index = 0;
	line->line = ft_strnew(0);
	ft_putstr_fd(status == LINE ? "$> " : ">  ", 0);
	tputs(line->caps.im, 0, ft_putc);
	while ((ret = read(0, buf, 9)))
	{
		buf[ret] = '\0';
		if ((!ft_isprint(buf[0]) && buf[0] != '\n') || ret > 1)
			ft_termcap(buf, line);
		else if (buf[0] != '\n')
			write_char(line, buf);
		if (buf[0] == '\n' && ret == 1)
			return (ft_eoi(line));
	}
	return (0);
}
