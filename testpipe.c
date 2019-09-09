/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testpipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:26:37 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/04 15:12:28 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "includes/libft.h"
#define READ 0
#define WRITE 1

char	*cmd[][3] =\
{
	{
		"/bin/cat",
		NULL,
		NULL,
	},
	{
		"/bin/ls",
		"-l",
		NULL,
	},
};

void	exec_pipe(int *pipefd, int *pipewait)
{
	pid_t	pid;
	char	*pid_str;

	pid = fork();
	if (!pid)
	{
		dup2(pipefd[READ], 0);
		close(pipefd[WRITE]);
		close(pipefd[READ]);
		close(pipewait[READ]);
		close(pipewait[WRITE]);
		execve(cmd[1][0], cmd[1], NULL);
		exit(EXIT_FAILURE);
	}
	else 
	{
		dup2(pipefd[WRITE], 1);
		close(pipefd[READ]);
		close(pipefd[WRITE]);
		close(pipewait[READ]);
		pid_str = ft_itoa(pid);
		write(pipewait[WRITE], pid_str, ft_strlen(pid_str));
		free(pid_str);
		close(pipewait[WRITE]);
		execve(cmd[0][0], cmd[0], NULL);
		exit(EXIT_FAILURE);
	}
}

int		main()
{
	int		pipefd[2];
	int		pipewait[2];
	int		pid_tab[2];
	char	pid_str[6];
	int		ret;
	pid_t	pid;

	pipe(pipefd);
	pipe(pipewait);
	pid = fork();
	if (!pid)
	{
		exec_pipe(pipefd, pipewait);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		pid_tab[0] = pid;
		close(pipewait[WRITE]);
		ret = read(pipewait[READ], pid_str, 5);
		pid_str[ret] = '\0';
		pid_tab[1] = atoi(pid_str);
		close(pipewait[READ]);
		waitpid(pid_tab[0], NULL, 0);
		waitpid(pid_tab[1], NULL, 0);
	}
}
