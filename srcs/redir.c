/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:36:10 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/25 23:16:07 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "exec.h"

t_redir_router	g_tab[] =\
{
	{less, ft_less},
	//{dless, ft_dless},
	//{lessand, ft_lessand},
	{great, ft_great},
	{dgreat, ft_dgreat}
	//{greatand, ft_greatand}
};

void	ft_redir_router(t_redir *redir_list)
{
	t_redir	*tmp;
	int		i;

	tmp = redir_list;
	while (tmp)
	{
		i = -1;
		while (++i < 3)
			if (g_tab[i].redir == tmp->type)
				g_tab[i].f(tmp);
		tmp = tmp->next;
	}
}
