/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 22:02:03 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/09 17:45:45 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_itolen(int n)
{
	int			i;
	long int	nb;

	nb = n;
	i = 0;
	if (nb < 0)
	{
		i++;
		nb = nb * -1;
	}
	if (nb == 0)
		i++;
	while (nb > 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		signe;

	i = ft_itolen(n);
	if (!(str = (char *)malloc(sizeof(*str) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	i--;
	signe = 1;
	if (n < 0)
	{
		str[0] = '-';
		signe = -1;
	}
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[i] = (n % 10) * signe + 48;
		n = n / 10;
		i--;
	}
	return (str);
}
