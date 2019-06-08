/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:17:03 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/08 15:55:44 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	init_caps(t_line *line)
{
	if (!(line->caps.cm = tgetstr("cm", NULL)))
		line->caps.cm = NULL;
	if (!(line->caps.ch = tgetstr("ch", NULL)))
		line->caps.ch = NULL;
	if (!(line->caps.im = tgetstr("im", NULL)))
		line->caps.im = NULL;
	if (!(line->caps.le = tgetstr("le", NULL)))
		line->caps.le = NULL;
	if (!(line->caps.nd = tgetstr("nd", NULL)))
		line->caps.nd = NULL;
	if (!(line->caps.dc = tgetstr("dc", NULL)))
		line->caps.dc = NULL;
	if (!(line->caps.cr = tgetstr("cr", NULL)))
		line->caps.cr = NULL;
	if (!(line->caps.cd = tgetstr("cd", NULL)))
		line->caps.cd = NULL;
	if (!(line->caps.dow = tgetstr("do", NULL)))
		line->caps.dow = NULL;
}

int		init_line(t_line *line)
{
	char	*name_term;
	t_ws	ws;

	if (!(name_term = getenv("TERM")))
		return (-1);
	if (tgetent(NULL, name_term) != 1)
		return (-1);
	tcgetattr(0, &(line->term));
	line->term.c_lflag &= ~(ICANON);
	line->term.c_lflag &= ~(ECHO);
	line->term.c_cc[VMIN] = 1;
	line->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &line->term) == -1)
		return (-1);
	ioctl(0, TIOCGWINSZ, &ws);
	line->nb_col = ws.ws_col;
	line->nb_line = ws.ws_row;
	line->history = NULL;
	init_caps(line);
	return (0);
}
