/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:17:03 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/23 15:20:18 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "env.h"

extern t_env	*g_env;

static void	make_history(t_line *line)
{
	t_list	*new;
	char	*content;
	int		fd;
	t_env	*home;

	home = env_get(g_env, "HOME");
	if (home)
		line->history_file = ft_strjoin(home->value, "/.21sh_history");
	if ((fd = open(line->history_file, O_RDONLY | O_CREAT, 0644)) == -1)
		return ;
	while (get_next_line(fd, &content) == 1)
	{
		new = ft_lstnew(content, ft_strlen(content) + 1);
		if (new)
			ft_lstend(&line->history, new);
	}
	close(fd);
}

static void	init_caps(t_line *line)
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

int			init_line(t_line *line)
{
	char	*name_term;
	t_ws	ws;

	if (!(name_term = getenv("TERM")))
		name_term = ft_strdup("dumb");
	tgetent(NULL, name_term);
	tcgetattr(0, &(line->term));
	line->term.c_lflag &= ~(ICANON);
	line->term.c_lflag &= ~(ECHO);
	line->term.c_cc[VMIN] = 1;
	line->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &line->term) == -1 && isatty(0))
		return (-1);
	ioctl(0, TIOCGWINSZ, &ws);
	line->nb_col = ws.ws_col;
	line->nb_line = ws.ws_row;
	line->history = NULL;
	line->visu.clipboard = NULL;
	make_history(line);
	init_caps(line);
	return (0);
}
