/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mesh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 15:38:50 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 15:38:51 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	my_add_vertex_h(t_vertex *start, t_vertex *vertex)
{
	t_vertex	*begin;

	begin = start;
	while (begin->nexth != 0)
		begin = begin->nexth;
	begin->nexth = vertex;
	vertex->l_loc.x = begin->l_loc.x + 10;
	vertex->l_loc.y = begin->l_loc.y;
}

void	my_add_vertex_v(t_vertex *start, t_vertex *vertex, int pos)
{
	t_vertex	*begin;
	int			i;

	begin = start;
	i = 0;
	if (start == 0)
		return ;
	while (i++ < pos)
		begin = begin->nexth;
	begin->nextv = vertex;
	vertex->l_loc.x = begin->l_loc.x;
	vertex->l_loc.y = begin->l_loc.y + 10;
}

void	my_add_vertex(t_mesh *mesh, t_vertex *vertex, int pos)
{
	t_vertex	*begin;
	t_vertex	*prev;

	begin = mesh->vert;
	prev = 0;
	if (begin == NULL)
	{
		mesh->vert = vertex;
		return ;
	}
	while (begin->nextv != 0)
	{
		prev = begin;
		begin = begin->nextv;
	}
	if (pos == 0)
		my_add_vertex_v(begin, vertex, pos);
	else
	{
		my_add_vertex_h(begin, vertex);
		my_add_vertex_v(prev, vertex, pos);
	}
}

t_vertex	*my_init_vertex(int z)
{
	t_vertex	*vertex;

	vertex = malloc(sizeof(t_vertex));
	if (vertex == NULL)
		return (0);
	vertex->l_loc.x = 0;
	vertex->l_loc.y = 0;
	vertex->l_loc.z = z;
	vertex->nexth = 0;
	vertex->nextv = 0;
	vertex->stage = Init;
	return (vertex);
}

void	my_generate_vertexes(t_mesh *mesh, char *str)
{
	t_vertex	*vertex;
	char		**test;
	int			i;

	if (str == NULL)
		my_abort_fdf(mesh);
	test = ft_split(str, ' ');
	if (my_check_split_size(test) == 0)
		my_abort_fdf(mesh);
	i = 0;
	while (test[i] != NULL)
	{
		vertex = my_init_vertex(ft_atoi(test[i]));
		if (vertex == NULL)
			my_abort_fdf(mesh);
		my_add_vertex(mesh, vertex, i);
		free(test[i]);
		i++;
	}
	if (mesh->vert == NULL)
		my_abort_fdf(mesh);
	free(test);
}
