/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 08:23:14 by alagroy-          #+#    #+#             */
/*   Updated: 2019/07/02 21:59:06 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "libft.h"

typedef enum		e_redir_type
{
	less,
	great,
	dless,
	dgreat,
	lessand,
	greatand,
}					t_redir_type;

typedef enum		e_sep_type
{
	semicol,
	or_if,
	and_if,
}					t_sep_type;

typedef struct		s_redir
{
	t_redir_type	type;
	char			*target;
	int				fd;
	int				fd_target;
	char			**heredoc;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_sep
{
	t_sep_type		sep;
	struct s_ast	*next;
}					t_sep;

typedef struct		s_ast
{
	char			*cmd;
	char			**args;
	t_redir			*input;
	t_redir			*output;
	int				status;
	t_sep			*sep;
	struct s_ast	*pipe;
	int				piped;
}					t_ast;

typedef struct		s_redir_router
{
	t_redir_type	redir;
	void			(*f)(t_redir *redir);
}					t_redir_router;

t_ast				*create_ast_node(int piped);
t_ast				*ast_init(t_list *token_list);
t_list				*ft_add_redir(t_redir **redir, t_list *tmp);
void				make_ast(t_ast *ast, t_list *tmp);
void				display_ast(t_ast *ast);

#endif
