/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mesh_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 15:39:00 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 15:39:01 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

int	my_check_split_size(char **test)
{
	static int	g_size;
	int			size;

	if (test == NULL)
		return (0);
	size = 0;
	while (test[size] != NULL)
		size++;
	if (g_size != -1 && size == 0)
		g_size = -1;
	else if (g_size != 0 && g_size != size)
		return (0);
	else
		g_size = size;
	return (1);
}
