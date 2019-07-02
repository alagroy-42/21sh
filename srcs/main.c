/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:51:07 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/02 21:50:51 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer_parser.h"
#include "ast.h"
#include "env.h"
#include "exec.h"

t_line	*g_line;
t_env *g_env = NULL;

void	term_setup(void)
{
	g_line->term.c_lflag &= ~(ICANON);
	g_line->term.c_lflag &= ~(ECHO);
	g_line->term.c_cc[VMIN] = 1;
	g_line->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_line->term);
}

void	term_unsetup(void)
{
	g_line->term.c_lflag = (ICANON | ECHO | ISIG | ECHOE);
	tputs(tgetstr("ei", NULL), 0, ft_putc);
	tcsetattr(0, 0, &g_line->term);
}

void		ft_quit(int code)
{
	int		fd;
	t_list	*tmp;

	tmp = g_line->history;
	fd = open("history/history", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (fd != -1 && tmp)
	{
		ft_putendl_fd(tmp->content, fd);
		tmp = tmp->next;
	}
	term_unsetup();
	close(fd);
	exit(code);
}

static void	core(t_line *line)
{
	t_list	*lex;
	t_ast	*ast;
	int		parse_return;

	ast = NULL;
	lex = NULL;
	parse_return = 0;
	parse_return = analize_line(line, &lex);
	if (parse_return == -42)
		ast = ast_init(lex);
	if (ast && ast->cmd)
		exec(ast);
	//free *
}

int		main(int argc, char **argv, char **env)
{
	t_line	*line;

	(void)argc;
	(void)argv;
	if (!(env_setup(env)))
	{
		ft_putendl("env_setup error");
		return (-1);
	}
	if (!(line = (t_line *)malloc(sizeof(t_line))))
		return (-1);
	g_line = line;
	//signal(SIGINT, ft_quit);
	if (init_line(line))
		return (-1);
	while (readline(line, LINE))
		core(line);
	return (0);
}
