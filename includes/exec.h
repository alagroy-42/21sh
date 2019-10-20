/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:15:20 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/20 16:52:10 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "ast.h"
# include "env.h"

int		is_cmd_file(char *cmd);
int		is_cmd_builtin(char *cmd);

void	builtin_echo(t_ast *ast);
void	builtin_exit(t_ast *ast);
void	builtin_setenv(t_ast *ast);
void	builtin_unsetenv(t_ast *ast);
void	builtin_env(t_ast *ast);
void	builtin_cd(t_ast *ast);
void	builtin_cd_chdir(char *path, int follow, t_ast *ast, int cdpath);
void	set_pwd(char *path, int follow, t_ast *ast, int cdpath);
char	**ft_2dstrjoin_path(char **tab1, char **tab2, int *k);
char	*ft_2dstr_to_path(char **tab1);
char	**ft_2dstrclean(char **tab1, int size);
void	set_pwd_check_pwd(char **pwd);

void	exec(t_ast *ast);
int		exec_builtin(t_ast *ast);
void	exec_ast_pipes(t_ast **ast, int size, char **envp);
int		exec_error(t_ast *ast);
void	exec_gfds_free(int size);
int		exec_gfds_malloc(int size);
t_ast	*ast_get_index(t_ast *ast, int index);
void	ast_pipes_end(t_ast **ast);
void	exec_ast_child(t_ast *ast, char **envp);
void	exec_ast_single(t_ast *ast, char **envp);
void	exec_ast_fork(t_ast **ast);
void	exec_wait_set_status(t_ast *ast, int pid, int status);
int		ast_pipes_size(t_ast *ast);
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
