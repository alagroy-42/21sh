/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 10:18:24 by alagroy-          #+#    #+#             */
/*   Updated: 2019/08/12 17:49:50 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "signal_21sh.h"
#include "readline.h"

void	signal_init(void)
{
	signal(SIGWINCH, ft_resize);
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, ft_ctrlc);
}
