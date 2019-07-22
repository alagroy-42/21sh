/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 10:18:24 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/22 20:16:17 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "readline.h"

extern t_line	*g_line;

void	term_unsetup(void)
{
	g_line->term.c_lflag = (ICANON | ECHO | ISIG | ECHOE);
	tputs(tgetstr("ei", NULL), 0, ft_putc);
	tcsetattr(0, 0, &g_line->term);
}

void	ft_quit(int code)
{
	int		fd;
	t_list	*tmp;

	tmp = g_line->history;
	fd = open(g_line->history_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (fd != -1 && tmp)
	{
		ft_putendl_fd(tmp->content, fd);
		tmp = tmp->next;
	}
	term_unsetup();
	close(fd);
	exit(code);
}

void	ft_resize(int sig)
{
	t_ws	ws;

	if (sig != SIGWINCH)
		return ;
	ioctl(0, TIOCGWINSZ, &ws);
	g_line->nb_col = ws.ws_col;
	g_line->nb_line = ws.ws_row;
}

void	signal_init(void)
{
	signal(SIGWINCH, ft_resize);
	signal(SIGINT, ft_quit);
}
