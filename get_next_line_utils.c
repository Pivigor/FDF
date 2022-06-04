/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:49:50 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:49:52 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

long long	str_size(char *str)
{
	long long	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

void	my_free(char **pointer)
{
	free(*pointer);
	*pointer = 0;
}

int	my_failure(char **saved_buffer)
{
	my_free(saved_buffer);
	return (-1);
}

int	copy_line(char *strto, char *strfrom, long long size, int need_to_malloc)
{
	long long	i;

	i = 0;
	while (i < size)
	{
		strto[i] = strfrom[i];
		i++;
	}
	strto[i] = '\0';
	if (need_to_malloc == 1)
		my_free(&strfrom);
	return (1);
}
