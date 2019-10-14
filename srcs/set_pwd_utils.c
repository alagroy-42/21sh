/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 06:19:15 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/09 18:27:18 by pcharrie         ###   ########.fr       */
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
	while (tab1 && tab1[i])
		total_len += ft_strlen(tab1[i++]);
	if (!(str = ft_strnew(total_len + ft_2dstrlen(tab1))))
		return (NULL);
	i = 0;
	j = 0;
	while (tab1 && tab1[i])
	{
		k = 0;
		str[j++] = '/';
		while (tab1[i][k])
			str[j++] = tab1[i][k++];
		i++;
	}
	str[j] = '\0';
	ft_2dstrdel(tab1);
	return (str);
}

int		ft_2dstrjoin_path_tablen(char **tab1, int k)
{
	int j;

	j = 0;
	while (tab1 && k < ft_2dstrlen(tab1) && tab1[k])
	{
		if (ft_strcmp(tab1[k], "..") && ft_strcmp(tab1[k], "."))
			j++;
		k++;
	}
	return (j);
}

char	**ft_2dstrjoin_path(char **tab1, char **tab2, int *k)
{
	char	**new_tab;
	int		i;
	int		j;
	int		len;

	len = ft_2dstrlen(tab1) + ft_2dstrjoin_path_tablen(tab2, *k);
	if (!(new_tab = (char **)malloc((len + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (tab1 && tab1[i])
		if (!(new_tab[j++] = ft_strdup(tab1[i++])))
			return (ft_2dstrdel(new_tab));
	while (tab2 && *k < ft_2dstrlen(tab2) && tab2[*k])
	{
		if ((ft_strcmp(tab2[*k], "..") && ft_strcmp(tab2[*k], "."))
			&& !(new_tab[j++] = ft_strdup(tab2[(*k)++])))
			return (ft_2dstrdel(new_tab));
		else
			break ;
	}
	new_tab[len] = NULL;
	return (new_tab);
}

char	**ft_2dstrclean(char **tab1, int size)
{
	int		i;
	int		j;
	char	**new_tab;

	i = 0;
	j = 0;
	while (i < size)
		if (tab1[i++])
			j++;
	if (!(new_tab = ft_2dstrnew(j)))
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (tab1[i])
			if (!(new_tab[j++] = ft_strdup(tab1[i])))
				return (ft_2dstrdel(new_tab));
		i++;
	}
	i = 0;
	while (i < size)
		ft_strdel(&tab1[i++]);
	free(tab1);
	return (new_tab);
}

void	set_pwd_check_pwd(char **pwd)
{
	if (!ft_strlen(*pwd))
	{
		ft_strdel(pwd);
		*pwd = ft_strdup("/");
	}
}
