/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 18:42:55 by alagroy-          #+#    #+#             */
/*   Updated: 2019/08/15 19:30:32 by alagroy-         ###   ########.fr       */
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
			ft_printf("str: %s", *str);
			return (index);
		}
		tmp = tmp->next;
	}
	tgetputstr("bl");
	return (0);
}

static void	disp_result(t_line *line, char *tmp, int status)
{
	if (status == 0)
	{
		tputs(line->caps.cr, 0, ft_putc);
		tputs(line->caps.cd, 0, ft_putc);
		ft_dprintf(0, "(reverse-i-search)'%s': %s", line->line, tmp);
	}
	else
	{
		tputs(line->caps.cr, 0, ft_putc);
		tputs(line->caps.cd, 0, ft_putc);
		ft_strdel(&line->line);
		line->line = ft_strdup(tmp);
		line->index = ft_strlen(line->line);
		ft_dprintf(0, "%s%s", line->prompt, line->line);
		g_ctrlr = 0;
	}
}

void		k_ctrlr(t_line *line)
{
	char	buf[10];
	char	*tmp;
	int		ret;
	int		index;

	index = -1;
	buf[0] = '\0';
	ret = 1;
	tmp = ft_strdup("");
	g_ctrlr = 1;
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
		disp_result(line, tmp, 0);
		ret = read(0, buf, 9);
		buf[ret] = '\0';
	}
	disp_result(line, tmp, 1);
}

void		k_ctrld(t_line *line)
{
	if (line->line[0])
		return (tgetputstr("bl"));
	ft_strdel(&line->line);
	if (!ft_strcmp(line->prompt, "$> "))
	{
		write(0, "\n", 1);
		ft_quit(0);
	}
}

void		k_ctrll(t_line *line)
{
	tgetputstr("cl");
	tputs(line->prompt, 0, ft_putc);
	tputs(line->line, 0, ft_putc);
	get_back_to_index(line);
}
