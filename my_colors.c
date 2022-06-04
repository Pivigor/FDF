/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:10:46 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:10:48 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

t_vector3d	my_to_rgb(int hex)
{
	t_vector3d	rgb;

	rgb.z = hex % 256;
	hex /= 256;
	rgb.y = hex % 256;
	hex /= 256;
	rgb.x = hex % 256;
	hex /= 256;
	return (rgb);
}

int	my_to_hex(t_vector3d rgb)
{
	int	hex;

	hex = rgb.x * 256 * 256;
	hex += rgb.y * 256;
	hex += rgb.z;
	return (hex);
}

int	my_grad(t_vector2d gradient, double progress)
{
	t_vector3d	rgb1;
	t_vector3d	rgb2;
	t_vector3d	rgb3;

	rgb1 = my_to_rgb(gradient.x);
	rgb2 = my_to_rgb(gradient.y);
	rgb3.x = (int)(rgb1.x + (rgb2.x - rgb1.x) * progress);
	rgb3.y = (int)(rgb1.y + (rgb2.y - rgb1.y) * progress);
	rgb3.z = (int)(rgb1.z + (rgb2.z - rgb1.z) * progress);
	return (my_to_hex(rgb3));
}

/*
 * m_m = min_max
 * p = progress
 */
void	my_mesh_colorizer(t_vertex *vert, t_vector2d m_m)
{
	double		p;
	t_vector3d	rgb;

	if (vert->stage == Color)
		return ;
	vert->stage = Color;
	p = (double)(vert->l_loc.z - m_m.x) / (double)(m_m.y - m_m.x) *2;
	if (p > 1)
	{
		rgb.x = 250;
		rgb.y = 250 - (int)(250 * (p - 1));
	}
	else
	{
		rgb.x = (int)(250 * p);
		rgb.y = 250;
	}
	rgb.z = 0;
	vert->color = my_to_hex(rgb);
	if (vert->nexth != NULL)
		my_mesh_colorizer(vert->nexth, m_m);
	if (vert->nextv != NULL)
		my_mesh_colorizer(vert->nextv, m_m);
}

int	my_mix_colors(int color1, int color2)
{
	t_vector3d	rgb1;
	t_vector3d	rgb2;
	t_vector3d	rgb3;

	rgb1 = my_to_rgb(color1);
	rgb2 = my_to_rgb(color2);
	rgb3.x = (rgb1.x + rgb2.x) / 2;
	rgb3.y = (rgb1.y + rgb2.y) / 2;
	rgb3.z = (rgb1.z + rgb2.z) / 2;
	return (my_to_hex(rgb3));
}
