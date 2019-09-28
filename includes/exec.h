/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:15:20 by pcharrie          #+#    #+#             */
/*   Updated: 2019/09/28 22:07:07 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "ast.h"
# include "env.h"

void	ft_putendl_child(char *s);
void	ft_putstr_fd_child(char *s, int fd);
int		is_cmd_builtin(char *cmd);

void	builtin_echo(t_ast *ast);
void	builtin_exit(t_ast *ast);
void	builtin_setenv(t_ast *ast);
void	builtin_unsetenv(t_ast *ast);
void	builtin_env(t_ast *ast);
void	builtin_cd(t_ast *ast, t_env *env);
void	builtin_cd_chdir(char *path, int follow, t_ast *ast, int cdpath);

void	exec(t_ast *ast);
void	ft_quit(int sig);
int		ft_redir_router(t_redir *redir_list);
int		ft_less(t_redir *redir);
int		ft_dless(t_redir *redir);
int		ft_great(t_redir *redir);
int		ft_dgreat(t_redir *redir);
int		ft_greatand(t_redir *redir);
int		child_crash(int status, t_ast *ast);
void	term_setup(void);
void	term_unsetup(void);

#endif
