/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:09:34 by skorbai           #+#    #+#             */
/*   Updated: 2023/12/15 12:24:48 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clean_up_leftover(char *leftover)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (leftover == NULL)
		return ;
	while (leftover[i] != '\n')
		i++;
	i++;
	while (leftover[i] != '\0')
		leftover[j++] = leftover[i++];
	leftover[j] = '\0';
	return ;
}

static char	*append_leftover(char *leftover, char *buffer, ssize_t bytes)
{
	char	*temp;

	temp = gnl_strdup(leftover, 0, 1);
	if (leftover != NULL)
	{
		free (leftover);
		leftover = NULL;
	}
	if (temp == NULL)
		return (NULL);
	leftover = gnl_strjoin(temp, buffer, bytes);
	free (temp);
	return (leftover);
}

static char	*last_line(char **leftover, char *buffer, ssize_t bytes)
{
	char	*result;

	if (bytes < 0)
		return (malloc_fail_cleanup(leftover));
	if (*leftover == NULL)
		*leftover = gnl_strdup(buffer, bytes, 0);
	else
		*leftover = append_leftover(*leftover, buffer, bytes);
	if (*leftover == NULL || *leftover[0] == '\0')
		return (malloc_fail_cleanup(leftover));
	if (ft_strchr(*leftover, '\n') != NULL)
	{
		result = newline_strdup(*leftover);
		if (result == NULL)
			return (malloc_fail_cleanup(leftover));
		clean_up_leftover(*leftover);
		return (result);
	}
	result = gnl_strdup(*leftover, 0, 1);
	free (*leftover);
	*leftover = NULL;
	return (result);
}

static char	*basic_gnl(int fd, char **leftover, char *buffer, ssize_t bytes)
{
	char	*result;

	if (*leftover == NULL)
		*leftover = gnl_strdup(buffer, BUFFER_SIZE, 0);
	else
		*leftover = append_leftover(*leftover, buffer, bytes);
	if (*leftover == NULL)
		return (NULL);
	while (ft_strchr(*leftover, '\n') == NULL)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < BUFFER_SIZE)
			return (last_line(leftover, buffer, bytes));
		else
		{
			*leftover = append_leftover(*leftover, buffer, bytes);
			if (*leftover == NULL)
				return (NULL);
		}
	}
	result = newline_strdup(*leftover);
	if (result == NULL)
		return (malloc_fail_cleanup(leftover));
	clean_up_leftover(*leftover);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*leftover[MAX_FD];
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE < 1)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
	{
		if (leftover[fd] != NULL)
		{
			free (leftover[fd]);
			leftover[fd] = NULL;
		}
		return (NULL);
	}
	else if (bytes < BUFFER_SIZE)
		return (last_line(&leftover[fd], buffer, bytes));
	else
		return (basic_gnl(fd, &leftover[fd], buffer, bytes));
}
