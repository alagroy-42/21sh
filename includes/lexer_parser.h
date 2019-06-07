/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 09:54:01 by alagroy-          #+#    #+#             */
/*   Updated: 2019/06/07 07:42:01 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H
# include "libft.h"
# include <stdlib.h>

# define ERROR -1
# define QUOTE -2
# define DQUOTE -3
# define PIPE_ERR -4
# define WORD -5
# define WORD_WC -25
# define WORD_DC -45
# define WORD_DQ -65
# define WORD_JOIN -6
# define WORD_JOIN_WC -26
# define WORD_JOIN_DC -46
# define WORD_JOIN_DQ -66
# define PIPE -7
# define PIPE_WC -27
# define OR_IF -8
# define AND_IF -9
# define LESS -10
# define LESS_WC -30
# define GREAT -11
# define GREAT_WC -31
# define DLESS -12
# define DGREAT -13
# define LESSAND -14
# define GREATAND -15
# define SEMICOL -16
# define EOI -17

# define NBR_FUNC 10
# define NBR_SYMBOL 12

typedef struct	s_token
{
	int		type;
	char	*lexem;
}				t_token;

t_list			*lex_line(char *line);
void			ft_del_token(void *content, size_t content_size);
void			aff_token(t_list *token);
int				ft_is_whitespace(char c);
int				ft_is_eoi(char c);
int				ft_is_dquote(char c);
int				ft_is_quote(char c);
int				ft_is_bckslsh(char c);
int				ft_is_pipe(char c);
int				ft_is_amper(char c);
int				ft_is_less(char c);
int				ft_is_great(char c);
int				ft_is_semicol(char c);
int				ft_is_alnum(char c);
int				parse_cmd(t_list *token_list);

#endif
