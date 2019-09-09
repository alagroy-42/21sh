/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testpipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:26:37 by alagroy-          #+#    #+#             */
/*   Updated: 2019/09/04 16:51:08 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "includes/libft.h"
#define READ 0
#define WRITE 1
#define NBR_CMD 4
#define NBR_PIP (NBR_CMD - 1)

char	*cmd[NBR_CMD][3] =\
{
	{
		"/bin/cat",
		NULL,
		NULL,
	},
	{
		"/bin/cat",
		NULL,
		NULL,
	},
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

void	exec_pipe(int *pipefd, int *pipewait, int index)
{
	pid_t	pid;
	char	*pid_str;
	int		i;

	i = -1;
	if (index == NBR_CMD)
		return ;
	if (index < NBR_PIP)
		pid = fork();
	else
	{
		dup2(pipefd[READ + 2 * index - 2], STDIN_FILENO);
		close(pipewait[READ]);
		close(pipewait[WRITE]);
		while (++i < NBR_PIP * 2)
			close(pipefd[i]);
		execve(cmd[index][0], cmd[index], NULL);
		exit(EXIT_FAILURE);
	}
	if (!pid)
		exec_pipe(pipefd, pipewait, index + 1);
	else
	{
		if (index != 0)
			dup2(pipefd[READ + 2 * index - 2], STDIN_FILENO);
		if (index != NBR_PIP)
			dup2(pipefd[WRITE + 2 * index], STDOUT_FILENO);
		close(pipewait[READ]);
		if ((pid_str = ft_itoa(pid)))
			write(pipewait[WRITE], pid_str, ft_strlen(pid_str));
		ft_strdel(&pid_str);
		close(pipewait[WRITE]);
		while (++i < NBR_PIP * 2)
			close(pipefd[i]);
		execve(cmd[index][0], cmd[index], NULL);
		exit(EXIT_FAILURE);
	}
}

int		main()
{
	int		*pipefd;
	int		pipewait[2];
	int		*pid_tab;
	char	pid_str[6];
	int		ret;
	int		i;
	pid_t	pid;

	if (!(pipefd = (int *)malloc(NBR_PIP * 2 * sizeof(int))))
		return (2);
	if (!((pid_tab = (int *)malloc(NBR_CMD * sizeof(int)))))
		return (3);
	i = -1;
	while (++i < NBR_PIP)
		pipe(pipefd + i * 2);
	pipe(pipewait);
	pid = fork();
	if (!pid)
	{
		exec_pipe(pipefd, pipewait, 0);
		exit(EXIT_FAILURE);
	}
	else
	{
		i = -1;
		while (++i < NBR_PIP * 2)
			close(pipefd[i]);
		pid_tab[0] = pid;
		close(pipewait[WRITE]);
		i = 1;
		while ((ret = read(pipewait[READ], pid_str, 5)) && i < NBR_CMD && ret != -1)
		{
			pid_str[ret] = '\0';
			pid_tab[i] = atoi(pid_str);
			i++;
		}
		close(pipewait[READ]);
		i = -1;
		while (++i < NBR_CMD)
			waitpid(pid_tab[i], NULL /* &status */, 0);
		free(pipefd);
		free(pid_tab);
	}
}
