/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:50:31 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:50:33 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"
#include "get_next_line.h"

t_vector2d	my_mfmm2(t_vector2d temp_min_max, t_vector2d min_max)
{
	if (!(temp_min_max.x == 1 && temp_min_max.y == -1))
	{
		if (temp_min_max.x < min_max.x)
			min_max.x = temp_min_max.x;
		if (temp_min_max.y > min_max.y)
			min_max.y = temp_min_max.y;
	}
	return (min_max);
}

t_vector2d	my_mesh_find_min_max(t_vertex *vertexes)
{
	t_vector2d	min_max;

	min_max.x = 1;
	min_max.y = -1;
	if (vertexes->stage == MinMax)
		return (min_max);
	vertexes->stage = MinMax;
	min_max.x = vertexes->l_loc.z;
	min_max.y = vertexes->l_loc.z;
	if (vertexes->nexth != NULL)
		min_max = my_mfmm2(my_mesh_find_min_max(vertexes->nexth), min_max);
	if (vertexes->nextv != NULL)
		min_max = my_mfmm2(my_mesh_find_min_max(vertexes->nextv), min_max);
	return (min_max);
}

void	my_abort_fdf(t_mesh *mesh)
{
	t_vertex	*vertex;
	t_vertex	*temp;
	t_vertex	*nextv;

	vertex = mesh->vert;
	while (vertex != NULL)
	{
		temp = vertex->nextv;
		while (temp != NULL)
		{
			nextv = temp->nextv;
			free(temp);
			temp = nextv;
		}
		temp = vertex->nexth;
		free(vertex);
		vertex = temp;
	}
	if (mesh->mlx_win != 0)
		mlx_destroy_window(mesh->mlx, mesh->mlx_win);
	write(STDOUT_FILENO, "Closing...\n", 11);
	exit(0);
}

void	my_filereader(t_mesh *mesh, int fd)
{
	char	*str;
	int		x;

	str = 0;
	x = get_next_line(fd, &str);
	while (x == 1)
	{
		my_generate_vertexes(mesh, str);
		free(str);
		str = 0;
		x = get_next_line(fd, &str);
	}
	if (x == -1)
		my_abort_fdf(mesh);
	my_generate_vertexes(mesh, str);
	free(str);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_mesh	mesh;

	mesh = mesh_init();
	if (argc != 2)
		my_abort_fdf(&mesh);
	fd = open(argv[1], O_RDONLY);
	my_filereader(&mesh, fd);
	my_mesh_colorizer(mesh.vert, my_mesh_find_min_max(mesh.vert));
	my_render(&mesh);
	mlx_loop(mesh.mlx);
}
