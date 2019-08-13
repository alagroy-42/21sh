/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:51:07 by alagroy-          #+#    #+#             */
/*   Updated: 2019/08/13 18:56:05 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer_parser.h"
#include "ast.h"
#include "env.h"
#include "exec.h"

t_line	*g_line;
t_env	*g_env = NULL;

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
	ft_lstdel(&lex, ft_del_token);
	ft_ast_del(&ast);
}

void	set_default_env(char *exe_name)
{
	t_env	*shlvl;
	char	*str;
	char**	atab;
	char	pwd[8192];

	getcwd(pwd, 8192);
	env_set(&g_env, "PWD", pwd);
	str = NULL;
	if (!(shlvl = env_get(g_env, "SHLVL")))
	{
		if ((str = ft_strdup("1")))
			env_set(&g_env, "SHLVL", str);
	}
	else
	{
		if ((str = ft_strdup(ft_itoa(ft_atoi(shlvl->value) + 1))))
			env_set(&g_env, "SHLVL", str);
	}
	ft_strdel(&str);
	if ((atab = ft_strsplit(exe_name, '/')))
		if ((str = ft_strstrjoin(pwd, "/", atab[ft_2dstrlen(atab) - 1])))
			env_set(&g_env, "SHELL", str);
	env_set(&g_env, "SHELL", str);
	ft_strdel(&str);
}

int		main(int argc, char **argv, char **env)
{
	t_line	*line;

	(void)argc;
	(void)argv;
//	if (ac > 1)
//		return (exec_file(ac, av));
	if (!(env_setup(env)))
	{
		ft_putendl("env_setup error");
		return (-1);
	}
	set_default_env(argv[0]);
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
