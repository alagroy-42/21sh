/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:51:07 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/18 12:52:38 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer_parser.h"
#include "ast.h"
#include "env.h"
#include "exec.h"

t_line		*g_line;
t_env		*g_env = NULL;
char		*g_pwd;
char		*g_oldpwd;
extern int	g_ctrlr;
int			**g_fds;

void	core(t_line *line)
{
	t_list	*lex;
	t_ast	*ast;
	int		parse_return;

	ast = NULL;
	lex = NULL;
	parse_return = 0;
	g_ctrlr = 1;
	parse_return = analize_line(line, &lex);
	g_ctrlr = 0;
	if (parse_return == -42)
		ast = ast_init(lex);
	if (ast && ast->cmd && ft_check_ast(ast))
		exec(ast);
	ft_lstdel(&lex, ft_del_token);
	ft_ast_del(&ast);
}

int		env_init(char **envp)
{
	char	pwd[8192];
	char	*str;

	env_import_envp(&g_env, envp);
	getcwd(pwd, 8192);
	if (!(g_pwd = ft_strdup(pwd))
		|| !(g_oldpwd = ft_strdup(pwd)))
	{
		ft_strdel(&g_pwd);
		return (0);
	}
	env_set(&g_env, "PWD", pwd);
	if (env_get(g_env, "SHLVL")
		&& (str = ft_itoa(ft_atoi(env_get(g_env, "SHLVL")->value) + 1)))
	{
		env_set(&g_env, "SHLVL", str);
		ft_strdel(&str);
	}
	else
		env_set(&g_env, "SHLVL", "1");
	return (1);
}

int		main(int ac, char **av, char **envp)
{
	t_line	*line;

	if (!(env_init(envp)) || !(line = (t_line *)malloc(sizeof(t_line))))
		return (-1);
	g_line = line;
	if (init_line(line))
		return (-1);
	signal_init();
	if (ac > 1)
		exec_file(ac, av, line);
	while (readline(line, LINE) == 1)
		core(line);
	ft_quit(1);
	return (0);
}
