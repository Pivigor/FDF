/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_brush_helper2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:36:31 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:36:32 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

t_line	my_line_reverse(t_line line)
{
	double	t;

	my_swap(&line.coorda.x, &line.coordb.x);
	my_swap(&line.coorda.y, &line.coordb.y);
	my_swap(&line.g.x, &line.g.y);
	t = line.height.x;
	line.height.x = line.height.y;
	line.height.y = t;
	return (line);
}

void	my_pp(t_mesh *mesh, t_line_helper h, double z, int color)
{
	if (h.x > MY_RES_X || h.x < 1 || h.y > MY_RES_Y || h.y < 1)
		return ;
	if (z > mesh->screen[h.x - 1][h.y - 1])
	{
		mlx_pixel_put(mesh->mlx, mesh->mlx_win, h.x, h.y, color);
		mesh->screen[h.x - 1][h.y - 1] = z;
	}
}

t_line_helper	my_draw_line_init(t_line line)
{
	t_line_helper	helper;

	helper.dx = line.coordb.x - line.coorda.x;
	helper.dy = line.coordb.y - line.coorda.y;
	helper.di = 1;
	return (helper);
}

void	my_draw_line_low(t_mesh *mesh, t_line line)
{
	t_line_helper	h;

	h = my_draw_line_init(line);
	if (h.dy < 0)
	{
		h.di = -1;
		h.dy = -h.dy;
	}
	h.d = (2 * h.dy) - h.dx;
	h.y = line.coorda.y;
	h.x = line.coorda.x;
	while (h.x <= line.coordb.x)
	{
		h.p = my_get_progress(line.coorda.x, h.x, line.coordb.x);
		my_pp(mesh, h, my_depth(line.height, h.p), my_grad(line.g, h.p));
		if (h.d > 0)
		{
			h.y = h.y + h.di;
			h.d = h.d + (2 * (h.dy - h.dx));
		}
		else
			h.d = h.d + 2 * h.dy;
		h.x++;
	}
}

void	my_draw_line_high(t_mesh *mesh, t_line line)
{
	t_line_helper	h;

	h = my_draw_line_init(line);
	if (h.dx < 0)
	{
		h.di = -1;
		h.dx = -h.dx;
	}
	h.d = (2 * h.dx) - h.dy;
	h.x = line.coorda.x;
	h.y = line.coorda.y;
	while (h.y <= line.coordb.y)
	{
		h.p = my_get_progress(line.coorda.y, h.y, line.coordb.y);
		my_pp(mesh, h, my_depth(line.height, h.p), my_grad(line.g, h.p));
		if (h.d > 0)
		{
			h.x = h.x + h.di;
			h.d = h.d + (2 * (h.dx - h.dy));
		}
		else
			h.d = h.d + 2 * h.dx;
		h.y++;
	}
}
