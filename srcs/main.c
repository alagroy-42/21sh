/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:51:07 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/03 15:17:22 by alagroy-         ###   ########.fr       */
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
	signal_init();
	if (init_line(line))
		return (-1);
	while (readline(line, LINE))
		core(line);
	return (0);
}
