/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:36:10 by alagroy-          #+#    #+#             */
/*   Updated: 2019/10/03 14:31:31 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"

t_redir_router	g_tab[] =\
{
	{less, ft_less},
	{dless, ft_dless},
	{lessand, ft_greatand},
	{great, ft_great},
	{dgreat, ft_dgreat},
	{greatand, ft_greatand}
};

int		ft_redir_router(t_redir *redir_list)
{
	t_redir	*tmp;
	int		i;

	tmp = redir_list;
	while (tmp)
	{
		i = -1;
		while (++i < 6)
			if (g_tab[i].redir == tmp->type)
				if (!g_tab[i].f(tmp))
					return (0);
		tmp = tmp->next;
	}
	return (1);
}
