/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_21sh.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:53:44 by alagroy-          #+#    #+#             */
/*   Updated: 2019/08/16 16:04:35 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_21SH_H
# define SIGNAL_21SH_H

void	ft_quit(int code);
void	ft_ctrlc(int sig);
void	ft_resize(int sig);
void	signal_ctrlr(void);

#endif
