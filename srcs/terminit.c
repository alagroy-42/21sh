/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:17:03 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/28 15:09:53 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "env.h"

extern t_env	*g_env;
extern t_line	*g_line;

void		term_setup(void)
{
	tcsetattr(0, TCSANOW, &g_line->term);
}

void		term_unsetup(void)
{
	tputs(tgetstr("ei", NULL), 0, ft_putc);
	tcsetattr(0, 0, &g_line->old_term);
}

static void	make_history(t_line *line)
{
	t_list	*new;
	char	*content;
	int		fd;
	t_env	*home;

	fd = -1;
	home = env_get(g_env, "HOME");
	if (home && isatty(STDIN_FILENO))
		line->history_file = ft_strjoin(home->value, "/.21sh_history");
	else
		line->history = NULL;
	if (!home || !line->history_file)
		return ;
	if (((fd = open(line->history_file, O_RDONLY | O_CREAT | O_NOFOLLOW,
						0644)) == -1 || !isatty(STDIN_FILENO)))
		return ;
	while (get_next_line(fd, &content) == 1)
	{
		new = ft_lstnew(content, ft_strlen(content) + 1);
		if (new)
			ft_lstend(&line->history, new);
		ft_strdel(&content);
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
	t_env	*name_term;

	if (!(name_term = env_get(g_env, "TERM")) || !ft_strlen(name_term->value))
		tgetent(NULL, "xterm-256color");
	else
		tgetent(NULL, name_term->value);
	tcgetattr(0, &(line->old_term));
	tcgetattr(0, &(line->term));
	line->term.c_lflag &= ~(ICANON);
	line->term.c_lflag &= ~(ECHO);
	line->term.c_cc[VMIN] = 1;
	line->term.c_cc[VTIME] = 0;
	if (isatty(STDIN_FILENO) && tcsetattr(0, TCSANOW, &line->term) == -1)
		return (-1);
	ft_resize(0);
	line->history = NULL;
	line->prompt = NULL;
	line->line = NULL;
	line->visu.clipboard = NULL;
	make_history(line);
	init_caps(line);
	load_21shrc(line);
	return (0);
}
