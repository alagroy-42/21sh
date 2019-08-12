/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr:alag      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 18:51:26 by alagroy-          #+#    #+#             */
/*   Updated: 2019/08/12 18:29:30 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

extern int	g_status;
extern int	g_lastpid;

int		is_special_param(char c)
{
	if (c == '?' || c == '!' || c == '$' || c == '#')
		return (1);
	else
		return (0);
}

char	*special_param_replace(char *str, int *i)
{
	char	*value;
	int		len;

	value = NULL;
	if (str[*i + 1] == '?')
		value = ft_itoa(g_status);
	else if (str[*i + 1] == '!')
		value = ft_itoa(g_lastpid);
	else if (str[*i + 1] == '#')
		value = ft_itoa(0);
	else if (str[*i + 1] == '$')
		value = ft_itoa(getpid());
	if (!value)
		return (str);
	len = *i + ft_strlen(value) - 1;
	str = ft_delete_flags(str, *i, 2);
	str = ft_insert_str(str, value, *i);
	*i += len;
	return (str);
}
