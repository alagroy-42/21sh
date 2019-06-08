/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:53:48 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/08 19:20:30 by alagroy-         ###   ########.fr       */
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
	{NULL, &k_left}
};

int			ft_putc(int c)
{
	write(0, &c, 1);
	return (0);
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
}

static void	write_char(t_line *line, char *buf)
{
	ft_putchar_fd(buf[0], 0);
	line->line = ft_insert_str(line->line, ft_strdup(buf), line->index);
	line->index++;
	if ((line->index + 3) / line->nb_col < ((int)ft_strlen(line->line) + 3)
			/ line->nb_col)
	{
		tputs(line->line + line->index, 0, ft_putc);
		get_back_to_index(line);
	}
}

int			readline(t_line *line)
{
	char	buf[10];
	int		ret;

	line->history_index = 0;
	line->index = 0;
	line->line = ft_strnew(0);
	ft_putstr("$> ");
	tputs(line->caps.im, 0, ft_putc);
	while ((ret = read(0, buf, 9)))
	{
		buf[ret] = '\0';
		if (buf[0] == '\n' && !buf[1])
		{
			history_push(line);
			return (ft_printf("\n"));
		}
		else if (!ft_isprint(buf[0]) || ret > 1)
			ft_termcap(buf, line);
		else
			write_char(line, buf);
	}
	return (0);
}
