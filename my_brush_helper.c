/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_brush_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:21:37 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:21:38 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

int	my_abs(int x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

double	my_abs_d(double x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

void	my_swap(int *a, int *b)
{
	int	t;

	t = *a;
	*a = *b;
	*b = t;
}

double	my_get_progress(double min, double now, double max)
{
	return ((double)(now - min) / (double)(max - min));
}

double	my_depth(t_vector2d_double height, double progress)
{
	return ((height.y - height.x) * progress + height.x);
}
