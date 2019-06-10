/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:48:33 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/10 19:16:26 by alagroy-         ###   ########.fr       */
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
# define UP 0
# define DOWN 1
# define K_LEFT	"\33[D"
# define K_RGHT "\33[C"
# define K_HOME "\33[H"
# define K_END "\33[F"
# define K_BSPC "\177"
# define K_UP "\33[A"
# define K_DOWN "\33[B"
# define K_CTRLL "\f"

typedef struct termios	t_termios;
typedef struct winsize	t_ws;

typedef struct			s_pos
{
	int		col;
	int		row;
}						t_pos;

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
	int			history_index;
	char		*line;
	t_termios	term;
	t_cap		caps;
	t_pos		pos;
	t_list		*history;
	int			nb_col;
	int			nb_line;
	int			last_arrow;
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
void					k_up(t_line *line);
void					k_down(t_line *line);
void					k_ctrll(t_line *line);
void					get_back_to_index(t_line *line);
void					get_cursor_position(int *col, int *row);
void					history_push(t_line *line);
void					tgetputstr(char *s);

#endif
