/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_specialchar_func.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 02:46:12 by alagroy-          #+#    #+#             */
/*   Updated: 2019/05/28 02:51:08 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_pipe(char c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

int		ft_is_amper(char c)
{
	if (c == '&')
		return (1);
	else
		return (0);
}

int		ft_is_less(char c)
{
	if (c == '<')
		return (1);
	else
		return (0);
}

int		ft_is_great(char c)
{
	if (c == '>')
		return (1);
	else
		return (0);
}

int		ft_is_semicol(char c)
{
	if (c == ';')
		return (1);
	else
		return (0);
}
