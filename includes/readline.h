/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:48:33 by alagroy-          #+#    #+#             */
/*   Updated: 2019/05/23 19:53:21 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H
# include "libft.h"
# include "ft_printf.h"
# include <termios.h>
# include <term.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# define K_LEFT	"\33[D"
# define K_RGHT "\33[C"
# define K_HOME "\33[H"
# define K_END "\33[F"
# define K_BSPC "\177"

typedef struct termios	t_termios;
typedef struct winsize	t_ws;

typedef struct			s_cap
{
	char	*cm;
	char	*ch;
	char	*im;
	char	*le;
	char	*nd;
	char	*dc;
	char	*cd;
	char	*cr;
	char	*dow;
}						t_cap;

typedef struct			s_line
{
	int			index;
	char		*line;
	t_termios	term;
	t_cap		caps;
	int			nb_col;
	int			nb_line;
}						t_line;

typedef struct			s_key
{
	char	*key;
	void	(*f)(t_line *line);
}						t_key;

int						readline(t_line *line);
int						ft_putc(int c);
int						init_line(t_line *line);
void					k_left(t_line *line);
void					k_right(t_line *line);
void					k_home(t_line *line);
void					k_end(t_line *line);
void					k_backspace(t_line *line);
void					get_back_to_index(t_line *line);

#endif
