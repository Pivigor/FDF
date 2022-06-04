/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_brush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:36:18 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:36:20 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

int	my_optimizer(t_mesh *mesh, t_line line)
{
	double	segment;

	segment = my_abs_d(10 * mesh->trans.scale.x) + 1;
	if (line.coorda.x > MY_RES_X + segment || line.coorda.x < -segment)
		return (1);
	if (line.coorda.y > MY_RES_Y + segment || line.coorda.y < -segment)
		return (1);
	if (line.coordb.x > MY_RES_X + segment || line.coordb.x < -segment)
		return (1);
	if (line.coordb.y > MY_RES_Y + segment || line.coordb.y < -segment)
		return (1);
	return (0);
}

void	my_draw_line4(t_mesh *mesh, t_line l)
{
	if (my_optimizer(mesh, l))
		return ;
	if (my_abs(l.coordb.y - l.coorda.y) < my_abs(l.coordb.x - l.coorda.x))
	{
		if (l.coorda.x > l.coordb.x)
			my_draw_line_low(mesh, my_line_reverse(l));
		else
			my_draw_line_low(mesh, l);
	}
	else
	{
		if (l.coorda.y > l.coordb.y)
			my_draw_line_high(mesh, my_line_reverse(l));
		else
			my_draw_line_high(mesh, l);
	}
}

t_line	my_generate_line(t_vertex *a, t_vertex *b)
{
	t_line	line;

	line.coorda.x = (int)round(a->g_loc.x);
	line.coorda.y = (int)round(a->g_loc.y);
	line.coordb.x = (int)round(b->g_loc.x);
	line.coordb.y = (int)round(b->g_loc.y);
	line.height.x = a->g_loc.z;
	line.height.y = b->g_loc.z;
	line.g.x = a->color;
	line.g.y = b->color;
	return (line);
}

void	my_draw_mesh_debug(t_vertex *vertexes, t_mesh *mesh)
{
	if (vertexes->stage == Draw)
		return ;
	vertexes->stage = Draw;
	if (vertexes->nexth != NULL)
	{
		my_draw_line4(mesh, my_generate_line(vertexes, vertexes->nexth));
		my_draw_mesh_debug(vertexes->nexth, mesh);
	}
	if (vertexes->nextv != NULL)
	{
		my_draw_line4(mesh, my_generate_line(vertexes, vertexes->nextv));
		my_draw_mesh_debug(vertexes->nextv, mesh);
	}
}

void	my_init_hooks(t_mesh *mesh)
{
	mlx_key_hook(mesh->mlx_win, &my_key_hook, mesh);
}
