/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:49:50 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/28 22:21:25 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_21sh.h"
#include "readline.h"
#include "env.h"

extern t_line	*g_line;
extern int		g_lastpid;
extern int		g_status;
extern int		g_ctrlr;
extern char		*g_pwd;
extern char		*g_oldpwd;
extern t_env	*g_env;

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
	ft_strdel(&g_pwd);
	ft_strdel(&g_oldpwd);
	env_destroy(&g_env);
	exit(code);
}

void	signal_ctrlr(void)
{
	struct sigaction	act;

	act.sa_handler = ft_ctrlc;
	act.sa_mask = 0;
	act.sa_flags &= SA_SIGINFO;
	act.sa_flags &= SA_RESTART;
	sigaction(SIGINT, &act, NULL);
}

void	ft_ctrlc(int sig)
{
	if (g_ctrlr)
	{
		g_ctrlr = 0;
		return ;
	}
	if (g_lastpid > 0)
	{
		kill(g_lastpid, sig);
		ft_putchar('\n');
		if (!ft_strcmp(g_line->prompt, ">  "))
			return (ft_strdel(&g_line->line));
		if (g_line->line && sig == SIGINT)
		{
			free(g_line->line);
			g_line->line = ft_strnew(0);
			g_line->index = 0;
			g_tbl = g_normal_tbl;
			tgetputstr("cr");
			tgetputstr("cd");
			g_line->history_index = 0;
			ft_putstr_fd(g_line->prompt, 2);
		}
	}
}

void	ft_resize(int sig)
{
	t_ws	ws;

	if (sig != SIGWINCH)
		return ;
	ioctl(0, TIOCGWINSZ, &ws);
	g_line->nb_col = ws.ws_col;
	g_line->nb_line = ws.ws_row;
	get_cursor_position(&g_line->pos.col, &g_line->pos.row);
}
