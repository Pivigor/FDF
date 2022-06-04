/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:49:35 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:49:36 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#define BUFFER_SIZE 10

long long	find_line(char *str, int ignore)
{
	long long	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (ignore == 0 || str[i] == '\n')
		return (i);
	return (-1);
}

long long	read_new_line(int fd, char **saved_buffer)
{
	long long	getted_size;
	char		*temp_buffer;
	char		*new_save_buffer;
	long long	size;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (temp_buffer == 0)
		return (-1);
	getted_size = read(fd, temp_buffer, BUFFER_SIZE);
	if (getted_size <= 0)
	{
		my_free(&temp_buffer);
		return (0);
	}
	size = str_size(*saved_buffer);
	new_save_buffer = malloc(size + getted_size + 1);
	if (new_save_buffer == 0)
	{
		my_free(&temp_buffer);
		return (-1);
	}
	copy_line(new_save_buffer, *saved_buffer, size, 1);
	copy_line(new_save_buffer + size, temp_buffer, getted_size, 1);
	*saved_buffer = new_save_buffer;
	return (getted_size);
}

int	generate_output(char **line, char **saved_buffer, long long new_line_pos)
{
	char		*new_save_buffer;
	long long	size;

	*line = malloc(new_line_pos + 1);
	if (*line == 0)
		return (my_failure(saved_buffer));
	copy_line(*line, *saved_buffer, new_line_pos, 0);
	size = str_size(*saved_buffer);
	new_save_buffer = malloc(size - new_line_pos + 2);
	if (new_save_buffer == 0)
	{
		my_free(line);
		return (my_failure(saved_buffer));
	}
	copy_line(new_save_buffer, *saved_buffer + new_line_pos + 1,
		size - new_line_pos - 1, 0);
	new_save_buffer[size - new_line_pos + 1] = '\0';
	my_free(saved_buffer);
	*saved_buffer = new_save_buffer;
	return (1);
}

int	get_next_line_part2(int fd, char **line, char **saved_buffer)
{
	long long		new_line_pos;
	long long		getted_size;

	getted_size = BUFFER_SIZE;
	new_line_pos = find_line(*saved_buffer, 1);
	while (new_line_pos == -1)
	{
		getted_size = read_new_line(fd, saved_buffer);
		if (getted_size == -1)
			return (my_failure(saved_buffer));
		if (getted_size < BUFFER_SIZE)
		{
			new_line_pos = find_line(*saved_buffer, 0);
			if ((*saved_buffer)[new_line_pos] == '\0')
			{
				if (generate_output(line, saved_buffer, new_line_pos) == -1)
					return (-1);
				my_free(saved_buffer);
				return (0);
			}
			break ;
		}
		new_line_pos = find_line(*saved_buffer, 1);
	}
	return (generate_output(line, saved_buffer, new_line_pos));
}

int	get_next_line(int fd, char **line)
{
	static char		*saved_buffer;

	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (my_failure(&saved_buffer));
	if (saved_buffer == 0)
	{
		saved_buffer = malloc(1);
		if (saved_buffer == 0)
			return (my_failure(&saved_buffer));
		else
			saved_buffer[0] = '\0';
	}
	return (get_next_line_part2(fd, line, &saved_buffer));
}
