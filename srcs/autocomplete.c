/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr:alag      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 19:39:57 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/05 15:44:34 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer_parser.h"
#include <dirent.h>

char	**find_in_path(char *path, char *cmplt)
{
	char			**cmplt_tab;
	DIR				*dir;
	struct dirent	*content;

	cmplt_tab = NULL;
	if (!(dir = opendir(path)))
		return (NULL);
	while ((content = readdir(dir)))
	{
		if (ft_strstr(content->d_name, cmplt))
			ft_expend_2dstr(cmplt_tab, content->d_name);
	}
	return (cmplt_tab);
}

char	*find_cmplt_word(char *str, int index)
{
	t_list	*lex;
	char	*sub;
	char	**split;
	int		i;

	sub = ft_strsub(str, 0, index + 1);
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

void	disp_cmplt(t_line *line, char **cmplt_tab)
{
	int		len;
	int		i;

	len = 0;
	while (cmplt_tab[len])
		len++;

}

void	ft_cmpltfile(t_line *line)
{
	char	*word;
	char	*path;
	char	*cmplt;
	char	**cmplt_tab;

	word = find_cmplt_word(line->line, line->index);
	if (!word)
		return ;
	find_path(word, &path, &cmplt);
	cmplt_tab = find_in_path(path, cmplt);
	ft_strdel(&path);
	ft_strdel(&word);
	ft_strdel(&cmplt);
}

void	k_tab(t_line *line)
{
	int		status;

	status = lite_parser(line->line, line->index);
	if (status)
		ft_cmpltfile(line);
//	else
//		ft_cmpltcmd(line);
}
