/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lite_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr:alag      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 19:43:11 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/03 20:11:53 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"

int		is_sep(char *str)
{
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, "||") || !ft_strcmp(str, ";")
			|| !ft_strcmp(str, "&&"))
		return (1);
	else
		return (0);
}

int		lite_parser(char *line, int index)
{
	int		i;
	int		status;
	char	*sub;
	char	**split;

	i = 0;
	if (!ft_strlen(line))
		return (0);
	sub = ft_strsub(line, 0, index + 1);
	split = ft_strsplit(sub, ' ');
	status = 0;
	while (split[0] && split[++i])
	{
		status++;
		if (is_sep(split[i]))
			status = 0;
	}
	if (!is_sep(split[i - 1]) && line[index - 1] == ' ')
		status++;
	ft_free_2dstr(split);
	free(sub);
	return (status);
}
