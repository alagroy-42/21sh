/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_cmplt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:53:46 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/26 17:37:53 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "env.h"

extern t_env	*g_env;

static void	ft_putline(t_line *line)
{
	int		up;

	up = (line->index + 3) / line->nb_col ? line->nb_col : 1;
	while (up--)
		tgetputstr("up");
	tputs(line->caps.cr, 2, ft_putc);
	tputs(line->caps.cd, 2, ft_putc);
	ft_printf("%s%s", line->prompt, line->line);
	left(line, ft_strlen(line->line) - line->index);
}

void		cmplt_end(t_line *line, char *cmplt_word, char *path)
{
	struct stat	infos;
	char		*full_path;

	if (path && path[ft_strlen(path) - 1] == '/')
		full_path = ft_strjoin(path, cmplt_word);
	else
		full_path = ft_strstrjoin(path, "/", cmplt_word);
	if (stat(full_path ? full_path : cmplt_word, &infos))
	{
		line->line = ft_insert_str(line->line, ft_strdup(" "), line->index++);
		ft_strdel(&full_path);
		ft_putline(line);
		return ;
	}
	if (S_ISDIR(infos.st_mode))
		line->line = ft_insert_str(line->line, ft_strdup("/"), line->index++);
	else
		line->line = ft_insert_str(line->line, ft_strdup(" "), line->index++);
	ft_strdel(&full_path);
	ft_putline(line);
}

char		**find_env_var_cmplt(char *cmplt)
{
	t_env	*tmp;
	char	**cmplt_tab;

	cmplt_tab = NULL;
	tmp = g_env;
	while (tmp)
	{
		if (!ft_strncmp(cmplt + 1, tmp->name, ft_strlen(cmplt + 1)))
			cmplt_tab = ft_expend_2dstr(cmplt_tab, tmp->name);
		tmp = tmp->next;
	}
	return (cmplt_tab);
}

static int	cmplt_ok(char **cmplt_tab, int len)
{
	int		i;

	i = -1;
	if (!cmplt_tab[0][len - 1])
		return (0);
	while (cmplt_tab[++i] && cmplt_tab[i + 1])
		if (ft_strncmp(cmplt_tab[i], cmplt_tab[i + 1], len))
			return (0);
	return (1);
}

int			cmplt_beginning(t_line *line, char **cmplt_tab, char *cmplt)
{
	int		len;
	int		len_beg;
	char	*disp;

	if (cmplt[0] == '$')
		len = ft_strlen(cmplt + 1);
	else if (ft_strirchr(cmplt, '/') == -1)
		len = ft_strlen(cmplt);
	else
		len = ft_strlen(cmplt + ft_strirchr(cmplt, '/') + 1);
	len_beg = len;
	disp = NULL;
	while (cmplt_ok(cmplt_tab, len + 1))
		len++;
	if (len == len_beg && ft_2dstrlen(cmplt_tab) > 1)
		return (0);
	else if (ft_2dstrlen(cmplt_tab) == 1)
		len = ft_strlen(cmplt_tab[0]);
	if (!(disp = ft_strsub(cmplt_tab[0], len_beg, len - len_beg)) || !disp[0])
		return (!disp ? 0 : 1);
	line->line = ft_insert_str(line->line, ft_strdup(disp), line->index);
	line->index += ft_strlen(disp);
	ft_putline(line);
	ft_strdel(&disp);
	return (ft_2dstrlen(cmplt_tab) > 1 ? 2 : 1);
}
