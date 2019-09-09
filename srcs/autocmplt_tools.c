/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocmplt_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 10:16:46 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/09 17:43:40 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <dirent.h>

char		**find_in_path(char *path, char *cmplt)
{
	char			**cmplt_tab;
	DIR				*dir;
	struct dirent	*content;

	cmplt_tab = NULL;
	if (!(dir = opendir(path)))
		return (NULL);
	while ((content = readdir(dir)))
	{
		if (!ft_strncmp(content->d_name, cmplt, ft_strlen(cmplt))
				&& (content->d_name[0] != '.' || cmplt[0] == '.'))
			cmplt_tab = ft_expend_2dstr(cmplt_tab, content->d_name);
	}
	closedir(dir);
	return (cmplt_tab);
}

void		disp_cmplt(t_line *line, char **cmplt_tab, char *cmplt)
{
	int		len;

	len = ft_2dstrlen(cmplt_tab);
	if (!len)
		return (tgetputstr("bl"));
	if (!cmplt_beginning(line, cmplt_tab, cmplt))
		disp_cmplt_tab(line, cmplt_tab);
}

void		cmplt_init(t_line *line, char **cmplt_tab)
{
	int		i;
	int		tmp;

	i = -1;
	tmp = 0;
	while (cmplt_tab[++i])
		if ((int)ft_strlen(cmplt_tab[i]) > tmp)
			tmp = ft_strlen(cmplt_tab[i]);
	line->cmplt.max_len = tmp;
	line->cmplt.nb_row = i / (line->nb_col / (tmp + 2)) + 1;
	get_cursor_position(&line->pos.col, &line->pos.row);
	line->cmplt.first_row = line->pos.row;
}

void		disp_cmplt_tab(t_line *line, char **cmplt_tab)
{
	int		i;
	int		status;

	status = 0;
	i = -1;
	ft_putchar_fd('\n', 2);
	cmplt_init(line, cmplt_tab);
	while (cmplt_tab[++i])
	{
		tputs(tgoto(line->caps.cm, (line->cmplt.max_len + 2) * (i
						/ line->cmplt.nb_row), line->cmplt.first_row + i
					% line->cmplt.nb_row), 2, ft_putc);
		line->cmplt.nb_row == 1 ? ft_putstr_fd(cmplt_tab[i], 2)
			: ft_putendl_fd(cmplt_tab[i], 2);
		get_cursor_position(&line->pos.col, &line->pos.row);
		if (line->pos.row < line->cmplt.first_row + i % line->cmplt.nb_row)
			status = 1;
		if (line->pos.row < line->cmplt.first_row + i % line->cmplt.nb_row)
			line->cmplt.first_row--;
		if (status && i == line->cmplt.nb_row - 1)
			line->cmplt.first_row--;
	}
	tputs(tgoto(line->caps.cm, 0, line->cmplt.first_row
				+ line->cmplt.nb_row), 2, ft_putc);
	ft_dprintf(2, "\n%s%s", line->prompt, line->line);
}

void		find_path(char *str, char **path, char **cmplt)
{
	int		len;

	*path = NULL;
	*cmplt = NULL;
	len = ft_strlen(str);
	while (--len > -1)
		if (str[len] == '/')
		{
			*path = ft_strsub(str, 0, len + 1);
			break ;
		}
	if (!*path)
	{
		*path = ft_strdup(".");
		*cmplt = ft_strdup(str);
	}
	else
		*cmplt = ft_strsub(str, len + 1, ft_strlen(str) - len + 1);
}
