/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 10:18:24 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/25 16:33:23 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "signal_21sh.h"
#include "readline.h"
#include "ast.h"

extern int	g_lastpid;
extern int	g_status;

char		*g_sig_tab[] =\
{
	NULL,
	"hangup",
	NULL,
	"quit",
	"illegal hardware instruction",
	"trace trap",
	"abort",
	"EMT instruction",
	"floating point exception",
	"killed",
	"bus error",
	"segmentation fault",
	"invalid system call",
	NULL,
	"alarm",
	"terminated",
};

int		child_crash(int status, t_ast *ast)
{
	status = WTERMSIG(status);
	if (g_sig_tab[status])
		ft_printf("%-7s%d %s  %s\n", "[1]", g_lastpid, g_sig_tab[status],
				ast->cmd);
	return (status + 128);
}

void	signal_init(void)
{
	signal(SIGWINCH, ft_resize);
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, ft_ctrlc);
}
