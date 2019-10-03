/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 10:16:36 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/03 17:35:09 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer_parser.h"
#include "env.h"

extern t_env	*g_env;

char			*g_builtins[7] =\
{
	"echo",
	"cd",
	"env",
	"setenv",
	"unsetenv",
	"exit",
	NULL
};

static char	*find_cmplt_word(char *str, int index)
{
	t_list	*lex;
	char	*sub;
	char	**split;
	int		i;

	sub = ft_strsub(str, 0, index);
	split = ft_strsplit(sub, ' ');
	lex = lex_line(sub);
	ft_strdel(&sub);
	i = -1;
	while (split && split[i + 1])
		i++;
	if (split && lex && index - 1 >= 0 && str[index - 1] != ' ')
		sub = ft_strdup(split[i]);
	ft_lstdel(&lex, ft_del_token);
	ft_free_2dstr(split);
	return (sub);
}

static char	**find_in_env(char *cmplt)
{
	t_env	*path;
	char	**split;
	char	**cmplt_tab;
	char	**tmp;
	int		i;

	i = -1;
	cmplt_tab = NULL;
	path = env_get(g_env, "PATH");
	if (!path)
		return (NULL);
	split = ft_strsplit(path->value, ':');
	while (split && split[++i])
	{
		tmp = find_in_path(split[i], cmplt);
		cmplt_tab = ft_2dstrjoin(cmplt_tab, tmp);
	}
	ft_2dstrdel(split);
	i = -1;
	while (g_builtins[++i])
	{
		if (!ft_strncmp(g_builtins[i], cmplt, ft_strlen(cmplt)))
			cmplt_tab = ft_expend_2dstr(cmplt_tab, g_builtins[i]);
	}
	return (cmplt_tab);
}

static void	ft_cmpltfile(t_line *line)
{
	char	*word;
	char	*path;
	char	*cmplt;
	char	**cmplt_tab;

	path = NULL;
	cmplt = NULL;
	word = find_cmplt_word(line->line, line->index);
	if (!word)
		return ;
	if (word[0] == '$')
		cmplt_tab = find_env_var_cmplt(word);
	else
	{
		find_path(word, &path, &cmplt);
		cmplt_tab = find_in_path(path, cmplt);
	}
	disp_cmplt(line, cmplt_tab, word, path);
	ft_strdel(&path);
	ft_strdel(&word);
	ft_strdel(&cmplt);
	ft_free_2dstr(cmplt_tab);
}

static void	ft_cmpltcmd(t_line *line)
{
	char	*word;
	char	**cmplt_tab;

	cmplt_tab = NULL;
	word = find_cmplt_word(line->line, line->index);
	if (!word)
		return ;
	if (ft_strchr(word, '/'))
		ft_cmpltfile(line);
	else
	{
		cmplt_tab = find_in_env(word);
		disp_cmplt(line, cmplt_tab, word, NULL);
	}
	ft_strdel(&word);
	ft_free_2dstr(cmplt_tab);
}

void		k_tab(t_line *line)
{
	int		status;

	status = lite_parser(line->line, line->index);
	if (status)
		ft_cmpltfile(line);
	else
		ft_cmpltcmd(line);
}
