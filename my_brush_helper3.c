/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_brush_helper3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:43:57 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:43:59 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

int	my_key_hook2(int key, t_mesh *mesh)
{
	if (key == 14)
		mesh->trans.rotation.z += 10;
	else if (key == 7)
	{
		mesh->trans.scale.x += my_abs_d(mesh->trans.scale.x * 0.1) + 0.01;
		mesh->trans.scale.y += my_abs_d(mesh->trans.scale.y * 0.1) + 0.01;
		mesh->trans.scale.z += my_abs_d(mesh->trans.scale.z * 0.1) + 0.01;
	}
	else if (key == 53)
		my_abort_fdf(mesh);
	else if (key == 15)
		mesh->trans.scale.z += my_abs_d(mesh->trans.scale.z * 0.1) + 0.01;
	else if (key == 3)
		mesh->trans.scale.z -= my_abs_d(mesh->trans.scale.z * 0.1) + 0.01;
	else
		return (0);
	return (1);
}

int	my_key_hook1(int key, t_mesh *mesh)
{
	if (key == 125)
		mesh->trans.rotation.x += 10;
	else if (key == 34)
	{
		if (mesh->render_type != Isometric)
			mesh->render_type = Isometric;
		else
			mesh->render_type = Default;
	}
	else if (key == 35)
	{
		if (mesh->render_type != Perspective)
			mesh->render_type = Perspective;
		else
			mesh->render_type = Default;
	}
	else if (key == 6)
	{
		mesh->trans.scale.x -= my_abs_d(mesh->trans.scale.x * 0.1) + 0.01;
		mesh->trans.scale.y -= my_abs_d(mesh->trans.scale.y * 0.1) + 0.01;
		mesh->trans.scale.z -= my_abs_d(mesh->trans.scale.z * 0.1) + 0.01;
	}
	else
		return (my_key_hook2(key, mesh));
	return (1);
}

int	my_key_hook(int key, t_mesh *mesh)
{
	if (key == 0)
		mesh->trans.location.x -= 10;
	else if (key == 1)
		mesh->trans.location.y += 10;
	else if (key == 2)
		mesh->trans.location.x += 10;
	else if (key == 13)
		mesh->trans.location.y -= 10;
	else if (key == 123)
		mesh->trans.rotation.y -= 10;
	else if (key == 124)
		mesh->trans.rotation.y += 10;
	else if (key == 126)
		mesh->trans.rotation.x -= 10;
	else if (key == 12)
		mesh->trans.rotation.z -= 10;
	else
	{
		if (my_key_hook1(key, mesh))
			my_render(mesh);
		return (0);
	}
	my_render(mesh);
	return (0);
}
