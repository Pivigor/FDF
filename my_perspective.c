/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_perspective.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 15:34:24 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 15:34:25 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

t_camera	my_init_camera(void)
{
	t_camera	camera;

	camera.near = 0.1;
	camera.far = 1000;
	camera.fov = 90;
	camera.aspectratio = (double)MY_RES_Y / (double)MY_RES_X;
	camera.fovrad = 1 / tan(camera.fov * 0.5 / 180 * M_PI);
	return (camera);
}

t_mat4x4	my_null_matrix(void)
{
	int			i;
	int			j;
	t_mat4x4	mat;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat.m[i][j] = 0;
			j++;
		}
		i++;
	}
	return (mat);
}

t_mat4x4	my_init_matproj(t_camera camera)
{
	t_mat4x4	m;

	m = my_null_matrix();
	m.m[0][0] = camera.aspectratio * camera.fovrad;
	m.m[1][1] = camera.fovrad;
	m.m[2][2] = camera.far / (camera.far - camera.near);
	m.m[3][2] = (-camera.far * camera.near) / (camera.far - camera.near);
	m.m[2][3] = 1;
	return (m);
}
/*
t_mat4x4	my_init_matZ(void)
{
	t_mat4x4	mat;
	double	angle;

	angle = 0.1;
	mat = my_null_matrix();
	mat.m[0][0] = cos(angle);
	mat.m[0][1] = sin(angle);
	mat.m[1][0] = -sin(angle);
	mat.m[1][1] = cos(angle);
	mat.m[2][2] = 1;
	mat.m[3][3] = 1;
	return (mat);
}

t_mat4x4	my_init_matX(void)
{
	t_mat4x4	mat;
	double		angle;

	angle = 0.1;
	mat = my_null_matrix();
	mat.m[0][0] = 1;
	mat.m[1][1] = cos(angle);
	mat.m[1][2] = sin(angle);
	mat.m[2][1] = -sin(angle);
	mat.m[2][2] = cos(angle);
	mat.m[3][3] = 1;
	return (mat);
}
*/

void	my_multiplymatrix(t_vector3d_d i, t_vector3d_d *o, t_mat4x4 m)
{
	double	w;

	o->x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o->y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o->z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
	if (w != 0)
	{
		o->x /= w;
		o->y /= w;
		o->z /= w;
	}
}
