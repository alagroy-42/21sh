/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:15:20 by pcharrie          #+#    #+#             */
/*   Updated: 2019/06/25 21:25:55 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ast.h"
# include "env.h"

void	builtin_env(t_ast *ast, t_env *env);
void	builtin_cd(t_ast *ast, t_env *env);

int		exec(t_ast *ast);
void	ft_quit(int sig);

#endif