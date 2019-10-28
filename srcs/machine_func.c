/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 02:38:55 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/28 16:27:28 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

int		ft_is_eoi(char c)
{
	if (c == '\0')
		return (1);
	else
		return (0);
}

int		ft_is_dquote(char c)
{
	if (c == '"')
		return (1);
	else
		return (0);
}

int		ft_is_quote(char c)
{
	if (c == '\'')
		return (1);
	else
		return (0);
}

int		ft_is_alpha(char c)
{
	if (ft_isprint(c) && c != '\'' && c != '"' && c != '|' && c != '>'
			&& c != '<' && c != '&' && c != ';' && !ft_isdigit(c) && c != ' ')
		return (1);
	else
		return (0);
}
