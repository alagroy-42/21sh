/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:01:23 by pcharrie          #+#    #+#             */
/*   Updated: 2019/10/20 20:44:03 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static void			reset_fd_lst_buff(t_gnllist *fd_lst)
{
	long long i;

	i = 0;
	while (i < BUFF_SIZE)
		fd_lst->buff[i++] = '\0';
	fd_lst->i = 0;
}

static t_gnllist	*get_fd_lst(int fd)
{
	static t_gnllist	*lst = NULL;
	t_gnllist			*fd_lst;

	fd_lst = lst;
	while (fd_lst != NULL)
	{
		if (fd_lst->fd == fd)
			return (fd_lst);
		fd_lst = fd_lst->next;
	}
	if (fd_lst != NULL)
		return (fd_lst);
	if (!(fd_lst = (t_gnllist *)malloc(sizeof(*fd_lst))))
		return (NULL);
	fd_lst->next = NULL;
	fd_lst->fd = fd;
	reset_fd_lst_buff(fd_lst);
	if (lst == NULL)
		lst = fd_lst;
	else
	{
		fd_lst->next = lst;
		lst = fd_lst;
	}
	return (fd_lst);
}

static int			write_char_to_line(char **line, char c)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while ((*line)[i])
		i++;
	if (!(tmp = (char *)malloc(sizeof(*tmp) * (i + 1))))
		return (0);
	j = -1;
	while (++j < i)
		tmp[j] = (*line)[j];
	free(*line);
	if (!(*line = (char *)malloc(sizeof(**line) * (i + 2))))
	{
		free(tmp);
		return (0);
	}
	j = -1;
	while (++j < i)
		(*line)[j] = tmp[j];
	free(tmp);
	(*line)[j++] = c;
	(*line)[j] = '\0';
	return (1);
}

static int			end_of_file(char **line, int error)
{
	if (error)
	{
		free(*line);
		*line = NULL;
		line = NULL;
		return (-1);
	}
	if ((*line)[0] != '\0')
		return (1);
	free(*line);
	*line = NULL;
	line = NULL;
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	t_gnllist	*fd_lst;
	int			bytes_read;

	if (fd < 0 || line == NULL || !(fd_lst = get_fd_lst(fd))
		|| !(*line = (char *)malloc(sizeof(**line) * 1)))
		return (-1);
	(*line)[0] = '\0';
	while (fd_lst->buff[fd_lst->i] != '\n')
	{
		if (fd_lst->buff[fd_lst->i] == '\0' || fd_lst->i == BUFF_SIZE)
		{
			reset_fd_lst_buff(fd_lst);
			if (!(bytes_read = read(fd, fd_lst->buff, BUFF_SIZE)))
				return (end_of_file(line, 0));
			if (bytes_read == -1)
				return (end_of_file(line, 1));
		}
		if (fd_lst->buff[fd_lst->i] && fd_lst->buff[fd_lst->i] != '\n')
			if (!write_char_to_line(line, fd_lst->buff[fd_lst->i++]))
				return (-1);
	}
	if (fd_lst->buff[fd_lst->i] == '\n')
		fd_lst->i++;
	return (1);
}
