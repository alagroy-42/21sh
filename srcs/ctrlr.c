/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrlr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:11:46 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/14 11:06:16 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "signal_21sh.h"

int			g_ctrlr = 0;

static int	ft_risearch(t_line *line, int index, char **str)
{
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = line->history;
	while (tmp && ++i < index)
		tmp = tmp->next;
	while (tmp)
	{
		index++;
		if (ft_strstr(tmp->content, line->line))
		{
			free(*str);
			*str = ft_strdup(tmp->content);
			return (index);
		}
		tmp = tmp->next;
	}
	tgetputstr("bl");
	return (0);
}

static void	disp_result(t_line *line, char *tmp, int status, t_pos posr)
{
	if (!g_ctrlr)
	{
		ft_strdel(&tmp);
		tmp = ft_strnew(0);
	}
	tputs(tgoto(line->caps.cm, posr.col, posr.row), 2, ft_putc);
	tputs(line->caps.cr, 2, ft_putc);
	tputs(line->caps.cd, 2, ft_putc);
	if (status == 0)
		ft_dprintf(2, "(reverse-i-search)'%s': %s", line->line, tmp);
	else
	{
		ft_strdel(&line->line);
		line->line = ft_strdup(tmp);
		line->index = ft_strlen(line->line);
		ft_strdel(&tmp);
		ft_dprintf(2, "%s%s", line->prompt, line->line);
		signal(SIGINT, ft_ctrlc);
		g_ctrlr = 0;
	}
}

void		ctrlr_loop(char *buf, char *tmp, t_line *line, t_pos posr)
{
	int	index;
	int	ret;

	index = -1;
	ret = 1;
	while ((((ft_isprint(buf[0]) || buf[0] == '\0') && ret == 1)
			|| !ft_strcmp(buf, K_BSPC) || !ft_strcmp(buf, K_CTRLR)) && g_ctrlr)
	{
		if (!ft_strcmp(buf, K_CTRLR))
			index = ft_risearch(line, index, &tmp);
		else if (!ft_strcmp(buf, K_BSPC) && line->index)
			line->line = ft_delete_flags(line->line, --line->index, 1);
		else if (buf[0] && ft_strcmp(buf, K_BSPC))
			line->line = ft_insert_str(line->line, ft_strdup(buf),
					line->index++);
		if (ft_strcmp(buf, K_CTRLR) && buf[0])
			index = ft_risearch(line, 0, &tmp);
		disp_result(line, tmp, 0, posr);
		if ((ret = read(0, buf, 9)) == -1)
			ret = 0;
		buf[ret] = '\0';
	}
	disp_result(line, tmp, 1, posr);
}

void		k_ctrlr(t_line *line)
{
	char	buf[10];
	char	*tmp;
	t_pos	posr;

	buf[0] = '\0';
	tmp = ft_strdup("");
	g_ctrlr = 1;
	signal_ctrlr();
	get_cursor_position(&posr.col, &posr.row);
	ctrlr_loop(buf, tmp, line, posr);
}
