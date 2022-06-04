/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_transform_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 15:29:36 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 15:29:37 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	my_rotate(double *x, double *y, int angle)
{
	double	tx;
	double	ty;
	double	r;

	tx = *x;
	ty = *y;
	r = 0.017453292519943 * angle;
	*x = tx * cos(r) + ty * sin(r);
	*y = ty * cos(r) - tx * sin(r);
}

void	my_apply_transform(t_vertex *vertexes, t_transform transform)
{
	if (vertexes->stage == Transform)
		return ;
	vertexes->stage = Transform;
	vertexes->g_loc = vertexes->l_loc;
	vertexes->g_loc.x *= transform.scale.x;
	vertexes->g_loc.y *= transform.scale.y;
	vertexes->g_loc.z *= transform.scale.z;
	my_rotate(&vertexes->g_loc.y, &vertexes->g_loc.z, transform.rotation.x);
	my_rotate(&vertexes->g_loc.x, &vertexes->g_loc.z, transform.rotation.y);
	my_rotate(&vertexes->g_loc.x, &vertexes->g_loc.y, transform.rotation.z);
	vertexes->g_loc.x += transform.location.x;
	vertexes->g_loc.y += transform.location.y;
	vertexes->g_loc.z += transform.location.z;
	if (vertexes->nexth != NULL)
		my_apply_transform(vertexes->nexth, transform);
	if (vertexes->nextv != NULL)
		my_apply_transform(vertexes->nextv, transform);
}
