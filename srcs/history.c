/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:10:02 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/08 17:29:58 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	history_push(t_line *line)
{
	t_list	*new_cmd;
	
	if (!line->line || !line->line[0])
		return ;
	new_cmd = ft_lstnew(line->line, ft_strlen(line->line) + 1);
	ft_lstadd(&line->history, new_cmd);
}

void	k_up(t_line *line)
{
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = line->history;
	if (!line->history || line->history_index >= (int)ft_lstsize(line->history))
		return (tgetputstr("bl"));
	while (++i < line->history_index)
		tmp = tmp->next;
	while (line->index > line->nb_col - 2)
		k_left(line);
	tputs(line->caps.cr, 0, ft_putc);
	tputs(line->caps.cd, 0, ft_putc);
	tputs("$> ", 0, ft_putc);
	tputs(tmp->content, 0, ft_putc);
	line->index = ft_strlen(tmp->content);
	free(line->line);
	line->line = ft_strdup(tmp->content);
	line->history_index++;
}

void	k_down(t_line *line)
{
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = line->history;
	if (!line->history || (line->history_index == 0 && ft_strcmp(line->line,
					line->history->content)))
		return (tgetputstr("bl"));
	while (++i < line->history_index - 1)
		tmp = tmp->next;
	while (line->index > line->nb_col - 2)
		k_left(line);
	tputs(line->caps.cr, 0, ft_putc);
	tputs(line->caps.cd, 0, ft_putc);
	tputs("$> ", 0, ft_putc);
	tputs(line->history_index ? tmp->content : "", 0, ft_putc);
	line->index = ft_strlen(line->history_index ? tmp->content : "");
	free(line->line);
	line->line = ft_strdup(line->history_index ? tmp->content : "");
	line->history_index -= line->history_index ? 1 : 0;
}
