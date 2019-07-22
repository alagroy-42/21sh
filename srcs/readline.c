/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:53:48 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/22 14:53:52 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key		g_normal_tbl[] =\
{
	{K_LEFT, &k_left},
	{K_RGHT, &k_right},
	{K_HOME, &k_home},
	{K_END, &k_end},
	{K_BSPC, &k_backspace},
	{K_UP, &k_up},
	{K_DOWN, &k_down},
	{K_CTRLD, &k_ctrld},
	{K_CTRLL, &k_ctrll},
	{K_ALFT, &k_altleft},
	{K_ARGT, &k_altright},
	{K_AUP, &k_altup},
	{K_ADOWN, &k_altdown},
	{K_ALTV, &k_visuinit},
	{K_TAB, &k_tab},
	{K_CTRLR, &k_ctrlr},
	{NULL, &k_left}
};

t_key		*g_tbl;

int			ft_putc(int c)
{
	return (write(0, &c, 1));
}

void		ft_termcap(char *buf, t_line *line)
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
		left(line, ft_strlen(line->line) - line->index - 1);
		tgetputstr("im");
	}
	get_cursor_position(&line->pos.col, &line->pos.row);
	if (line->pos.col == line->nb_col - 1)
		tgetputstr("do");
}

int			ft_eoi(t_line *line)
{
	int		len;

	len = ft_strlen(line->line);
	while (line->index < len)
		k_right(line);
	write_char(line, "\n");
	history_push(line, line->line);
	return (1);
}

int			readline(t_line *line, int status)
{
	char	buf[10];
	int		ret;

	if (!isatty(STDIN_FILENO))
		return (get_next_line(0, &line->line));
	g_tbl = g_normal_tbl;
	line->history_index = 0;
	line->last_arrow = UP;
	line->index = 0;
	line->line = ft_strnew(0);
	line->prompt = ft_strdup(status == LINE ? "$> " : ">  ");
	ft_putstr_fd(line->prompt, 0);
	tputs(line->caps.im, 0, ft_putc);
	while ((ret = read(0, buf, 9)))
	{
		buf[ret] = '\0';
		if ((!ft_isprint(buf[0]) && buf[0] != '\n') || ret > 1)
			ft_termcap(buf, line);
		else if (buf[0] != '\n' && g_tbl != g_visutab)
			write_char(line, buf);
		if (ret == 1 && buf[0] == '\n')
			return (ft_eoi(line));
		if (buf[0] == 4 && ret == 1 && !line->line)
			return (1);
	}
	return (0);
}
