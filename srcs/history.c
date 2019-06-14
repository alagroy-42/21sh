/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:10:02 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/14 15:51:08 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		history_push(t_line *line, char *line_str)
{
	t_list	*new_cmd;
	int		i;

	if (!line_str || line_str[0] == '\n')
		return ;
	if (line->history && !ft_strcmp(line->history->content, line_str))
		return ;
	i = ft_strlen(line_str);
	while (--i)
		if (line_str[i] == '\n')
		{
			line_str[i] = '\0';
			break ;
		}
	new_cmd = ft_lstnew(line_str, ft_strlen(line_str) + 1);
	ft_lstadd(&line->history, new_cmd);
}

static void	write_history(t_line *line, char *str)
{
	char	*sub;
	int		i;

	i = -1;
	sub = NULL;
	while (str[++i])
	{
		sub = ft_strsub(str, i, 1);
		write_char(line, sub);
		free(sub);
	}
}

void		k_up(t_line *line)
{
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = line->history;
	line->history_index += line->last_arrow == DOWN && line->history_index
		? 1 : 0;
	if (!line->history || line->history_index >= (int)ft_lstsize(line->history))
		return (tgetputstr("bl"));
	while (++i < line->history_index)
		tmp = tmp->next;
	while (line->index)
		k_left(line);
	tputs(line->caps.cr, 0, ft_putc);
	tputs(line->caps.cd, 0, ft_putc);
	tputs("$> ", 0, ft_putc);
	write_history(line, tmp->content);
	free(line->line);
	line->line = ft_strdup(tmp->content);
	line->history_index++;
	line->last_arrow = UP;
	if ((line->index + 3) % line->nb_col == 0)
		tgetputstr("do");
}

void		k_down(t_line *line)
{
	int		i;
	t_list	*tmp;

	i = -1;
	line->history_index -= line->last_arrow == UP ? 1 : 0;
	tmp = line->history;
	if (!line->history || (line->history_index == 0 && ft_strcmp(line->line,
					line->history->content)))
		return (tgetputstr("bl"));
	while (++i < line->history_index - 1)
		tmp = tmp->next;
	while (line->index)
		k_left(line);
	tputs(line->caps.cr, 0, ft_putc);
	tputs(line->caps.cd, 0, ft_putc);
	tputs("$> ", 0, ft_putc);
	write_history(line, line->history_index ? tmp->content : "");
	free(line->line);
	line->line = ft_strdup(line->history_index ? tmp->content : "");
	line->history_index -= line->history_index ? 1 : 0;
	line->last_arrow = DOWN;
	if ((line->index + 3) % line->nb_col == 0)
		tgetputstr("do");
}
