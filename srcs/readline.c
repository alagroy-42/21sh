/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:53:48 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/09 16:59:51 by alagroy-         ###   ########.fr       */
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
	{K_ALTB, &k_visuinit},
	{K_TAB, &k_tab},
	{K_CTRLR, &k_ctrlr},
	{NULL, &k_left}
};

t_key		*g_tbl;
extern int	g_ctrlr;
int			g_filemode = 0;

int			ft_putc(int c)
{
	return (write(2, &c, 1));
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
	line->line = ft_insert_str(line->line, ft_strdup(buf), line->index);
	line->index++;
	get_cursor_position(&line->pos.col, &line->pos.row);
	ft_putchar_fd(buf[0], 2);
	if (line->pos.col == line->nb_col - 1)
		tgetputstr("do");
	if (line->line && line->index != (int)ft_strlen(line->line))
	{
		tgetputstr("ei");
		get_cursor_position(&line->pos.col, &line->pos.row);
		ft_putstr_fd(line->line + line->index, 0);
		tputs(tgoto(line->caps.cm, line->pos.col, line->pos.row), 2, ft_putc);
		tgetputstr("im");
	}
}

int			ft_eoi(t_line *line)
{
	int		len;

	len = ft_strlen(line->line);
	right(line, len - line->index);
	line->index = ft_strlen(line->line);
	write_char(line, "\n");
	history_push(line, line->line);
	return (1);
}

int			readline(t_line *line, int status)
{
	char	buf[10];
	int		ret;

	if (!isatty(STDIN_FILENO) || g_filemode)
		return (gnl_nl(g_filemode ? line->curr_fd : 0, &line->line));
	g_tbl = g_normal_tbl;
	readline_init(line, status);
	tputs(line->caps.im, 2, ft_putc);
	while ((ret = read(0, buf, 9)) && line->line)
	{
		if (ret == -1)
			return (0);
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
	if (!line->line && g_ctrlr)
		ft_putstr_fd("21sh: Allocation error, processus can't continue.\n", 2);
	return (0);
}
