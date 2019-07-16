/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocmplt_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr:alag      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:33:32 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/05 15:08:13 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		find_path(char *str, char **path, char **cmplt)
{
	int		len;

	*path = NULL;
	*cmplt = NULL;
	len = ft_strlen(str);
	if (str[len - 1] == '/')
		return ;
	while (--len > -1)
		if (str[len] == '/')
		{
			*path = ft_strsub(str, 0, len + 1);
			break ;
		}
	if (!*path)
	{
		*path = getcwd(NULL, 0);
		*cmplt = ft_strdup(str);
	}
	else
		*cmplt = ft_strsub(str, len + 1, ft_strlen(str) - len + 1);
}
