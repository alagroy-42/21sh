/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:48:33 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/26 16:39:21 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H
# include "libft.h"
# include "ft_printf.h"
# include <termios.h>
# include <term.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# define UP 0
# define DOWN 1
# define LINE 0
# define INCOMPLETE 1
# define K_LEFT	"\33[D"
# define K_RGHT "\33[C"
# define K_HOME "\33[H"
# define K_END "\33[F"
# define K_BSPC "\177"
# define K_UP "\33[A"
# define K_DOWN "\33[B"
# define K_CTRLD "\4"
# define K_CTRLC "\3"
# define K_CTRLL "\f"
# define K_ALFT "\33\33[D"
# define K_ARGT "\33\33[C"
# define K_AUP "\33\33[A"
# define K_ADOWN "\33\33[B"
# define K_CTRLV "\026"
# define K_ALTV "√"
# define K_ALTX "≈"
# define K_ALTC "ç"
# define K_ALTB "∫"
# define K_TAB "\t"
# define K_CTRLR "\022"

typedef struct termios	t_termios;
typedef struct winsize	t_ws;

typedef struct			s_autocmplt
{
	int		max_len;
	int		nb_row;
	int		first_row;
}						t_autocmplt;

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

typedef struct			s_visu
{
	int		begin;
	int		offset;
	char	*clipboard;
}						t_visu;

typedef struct			s_line
{
	int			index;
	int			history_index;
	char		*line;
	char		*prompt;
	t_termios	term;
	t_termios	old_term;
	t_cap		caps;
	t_pos		pos;
	t_list		*history;
	int			nb_col;
	int			nb_line;
	int			last_arrow;
	char		*history_file;
	t_visu		visu;
	t_autocmplt	cmplt;
}						t_line;

typedef struct			s_key
{
	char	*key;
	void	(*f)(t_line *line);
}						t_key;

extern t_key			*g_tbl;
extern t_key			g_normal_tbl[];
extern t_key			g_visutab[];

int						readline(t_line *line, int status);
int						ft_putc(int c);
int						init_line(t_line *line);
void					k_left(t_line *line);
void					k_right(t_line *line);
void					k_home(t_line *line);
void					k_end(t_line *line);
void					k_backspace(t_line *line);
void					k_up(t_line *line);
void					k_down(t_line *line);
void					k_ctrld(t_line *line);
void					k_ctrll(t_line *line);
void					k_altleft(t_line *line);
void					k_altright(t_line *line);
void					k_altup(t_line *line);
void					k_altdown(t_line *line);
void					k_visuinit(t_line *line);
void					k_visuend(t_line *line);
void					k_vleft(t_line *line);
void					k_vright(t_line *line);
void					k_altx(t_line *line);
void					k_altv(t_line *line);
void					k_ctrlr(t_line *line);
void					k_altc(t_line *line);
void					k_tab(t_line *line);
void					get_back_to_index(t_line *line);
void					get_cursor_position(int *col, int *row);
void					history_push(t_line *line, char *s);
void					tgetputstr(char *s);
void					write_char(t_line *line, char *buf);
void					ft_termcap(char *buf, t_line *line);
void					print_visu(t_line *line);
void					reset_visu(t_line *line);
void					left(t_line *line, int len);
void					right(t_line *line, int len);
void					write_str(t_line *line, char *str);
void					signal_init(void);
void					ft_resize(int sig);
void					ft_quit(int sig);
void					term_unsetup(void);
void					find_path(char *str, char **path, char **cmplt);
void					disp_cmplt_tab(t_line *line, char **cmplt_tab);
char					**find_in_path(char *path, char *cmplt);
char					**find_env_var_cmplt(char *cmplt);
void					disp_cmplt(t_line *line, char **cmplt_tab, char *cmplt,
						char *path);
int						cmplt_beginning(t_line *line, char **cmplt_tab,
						char *cmplt);
int						ft_eoi(t_line *line);
void					readline_init(t_line *line, int status);
void					exec_file(int ac, char **av, t_line *line);
void					core(t_line *line);
void					load_21shrc(t_line *line);
void					cmplt_end(t_line *line, char *cmlplt_word, char *path);

#endif
