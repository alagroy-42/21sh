/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:51:07 by alagroy-          #+#    #+#             */
/*   Updated: 2019/05/28 16:27:04 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer.h"

t_line	*g_line;

void	ft_restore(int sig)
{
	sig = 0;
	g_line->term.c_lflag = (ICANON | ECHO | ISIG);
	tputs(tgetstr("ei", NULL), 0, ft_putc);
	tcsetattr(0, 0, &g_line->term);
	exit(EXIT_SUCCESS);
}

int		main(void)
{
	t_line	*line;
	t_list	*lex;

	if (!(line = (t_line *)malloc(sizeof(t_line))))
		return (-1);
	g_line = line;
	signal(SIGINT, ft_restore);
	if (init_line(line))
		return (-1);
	while (readline(line))
	{
		ft_printf("line = %s\n", line->line);
		lex = lex_line(line->line);
		ft_strdel(&line->line);
	}
	return (0);
}
