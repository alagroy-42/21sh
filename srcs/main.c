/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:51:07 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/10 19:30:24 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer_parser.h"
#include "ast.h"

t_line	*g_line;

void	ft_quit(int sig)
{
	int		fd;
	t_list	*tmp;

	tmp = g_line->history;
	sig = 0;
	fd = open("history/history", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (fd != -1 && tmp)
	{
		ft_putendl_fd(tmp->content, fd);
		tmp = tmp->next;
	}
	g_line->term.c_lflag = (ICANON | ECHO | ISIG | ECHOE);
	tputs(tgetstr("ei", NULL), 0, ft_putc);
	tcsetattr(0, 0, &g_line->term);
	close(fd);
	exit(EXIT_SUCCESS);
}

int		main(void)
{
	t_line	*line;
	t_list	*lex;
	t_ast	*ast;

	ast = NULL;
	if (!(line = (t_line *)malloc(sizeof(t_line))))
		return (-1);
	g_line = line;
	signal(SIGINT, ft_quit);
	if (init_line(line))
		return (-1);
	while (readline(line))
	{
		ft_putendl(line->line);
		lex = lex_line(line->line);
		ft_strdel(&line->line);
		if (lex)
			if (parse_cmd(lex) == -42)
				ast = ast_init(lex);
	}
	return (0);
}
