/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:15:20 by pcharrie          #+#    #+#             */
/*   Updated: 2019/06/26 00:15:20 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ast.h"
# include "env.h"

void	builtin_echo(t_ast *ast);
void	builtin_exit(t_ast *ast);
void	builtin_setenv(t_ast *ast, t_env *env);
void	builtin_unsetenv(t_ast *ast, t_env **env);
void	builtin_env(t_ast *ast, t_env *env);
void	builtin_cd(t_ast *ast, t_env *env);

int		exec(t_ast *ast);
void	ft_quit(int sig);
void	ft_redir_router(t_redir *redir_list);
void	ft_less(t_redir *redir);
void	ft_dless(t_redir *redir);
void	ft_great(t_redir *redir);
void	ft_dgreat(t_redir *redir);

#endif
