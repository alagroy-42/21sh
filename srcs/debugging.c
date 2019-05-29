/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 11:48:40 by alagroy-          #+#    #+#             */
/*   Updated: 2019/05/29 11:50:46 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		aff_token(t_list *token)
{
	t_list	*tmp;

	tmp = token;
	while (tmp)
	{
		ft_printf("lexem : |%s|, type : %d\n", ((t_token *)tmp->content)->lexem,
				((t_token *)tmp->content)->type);
		tmp = tmp->next;
	}
}
