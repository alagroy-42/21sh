/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 06:19:15 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/04 09:33:34 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_2dstr_to_path(char **tab1)
{
	int		total_len;
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	total_len = 0;
	while (tab1[i])
		total_len += ft_strlen(tab1[i++]);
	if (!(str = ft_strnew(total_len + ft_2dstrlen(tab1))))
		return (NULL);
	i = 0;
	j = 0;
	while (tab1[i])
	{
		k = 0;
		str[j++] = '/';
		while (tab1[i][k])
			str[j++] = tab1[i][k++];
		i++;
	}
	str[j] = '\0';
	return (str);
}

int		ft_2dstrjoin_path_tablen(char **tab1)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tab1 && tab1[i])
	{
		if (ft_strcmp(tab1[i], "..") && ft_strcmp(tab1[i], "."))
			j++;
		i++;
	}
	return (j);
}

char	**ft_2dstrjoin_path(char **tab1, char **tab2, int k)
{
	char	**new_tab;
	int		i;
	int		j;
	int		len;

	len = ft_2dstrlen(tab1) + ft_2dstrjoin_path_tablen(tab2);
	if (!(new_tab = (char **)malloc((len + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (tab1 && tab1[i])
		new_tab[j++] = ft_strdup(tab1[i++]);
	while (tab2 && k < ft_2dstrlen(tab2) && tab2[k])
	{
		if (ft_strcmp(tab2[k], "..") && ft_strcmp(tab2[k], "."))
			new_tab[j++] = ft_strdup(tab2[k]);
		k++;
	}
	new_tab[len] = NULL;
	return (new_tab);
}
