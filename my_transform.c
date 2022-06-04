/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 15:29:27 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 15:29:29 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	my_iso(double *x, double *y, double z)
{
	double	previous_x;
	double	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	my_mesh_iso_debug(t_vertex *vertexes)
{
	if (vertexes->stage == Iso)
		return ;
	vertexes->stage = Iso;
	my_iso(&vertexes->g_loc.x, &vertexes->g_loc.y, vertexes->g_loc.z);
	if (vertexes->nexth != NULL)
		my_mesh_iso_debug(vertexes->nexth);
	if (vertexes->nextv != NULL)
		my_mesh_iso_debug(vertexes->nextv);
}

void	my_mesh_persp(t_vertex *vertexes, t_mat4x4 matProj)
{
	if (vertexes->stage == Persp)
		return ;
	vertexes->stage = Persp;
	my_multiplymatrix(vertexes->g_loc, &vertexes->g_loc, matProj);
	if (vertexes->nexth != NULL)
		my_mesh_persp(vertexes->nexth, matProj);
	if (vertexes->nextv != NULL)
		my_mesh_persp(vertexes->nextv, matProj);
}

void	my_init_render(t_mesh *mesh)
{
	int	i;
	int	j;

	i = 0;
	while (i < MY_RES_X)
	{
		j = 0;
		while (j < MY_RES_Y)
		{
			mesh->screen[i][j] = -DBL_MAX;
			j++;
		}
		i++;
	}
	if (mesh->mlx == 0)
	{
		mesh->mlx = mlx_init();
		mesh->mlx_win = mlx_new_window(mesh->mlx, MY_RES_X, MY_RES_Y, "FDF");
	}
	else
		mlx_clear_window(mesh->mlx, mesh->mlx_win);
}

void	my_render(t_mesh *mesh)
{
	t_transform	transform;

	my_init_render(mesh);
	if (mesh->render_type == Default)
		my_apply_transform(mesh->vert, mesh->trans);
	if (mesh->render_type == Isometric)
	{
		my_apply_transform(mesh->vert, mesh->trans);
		my_mesh_iso_debug(mesh->vert);
	}
	if (mesh->render_type == Perspective)
	{
		transform = mesh->trans;
		transform.rotation.x = 0;
		transform.rotation.y = 0;
		transform.rotation.z = 0;
		my_apply_transform(mesh->vert, transform);
		my_mesh_persp(mesh->vert, my_init_matproj(my_init_camera()));
	}
	my_draw_mesh_debug(mesh->vert, mesh);
	my_init_hooks(mesh);
}
