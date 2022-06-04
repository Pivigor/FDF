/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:54:20 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:54:21 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

t_mesh	mesh_init(void)
{
	t_mesh	mesh;

	mesh.vert = 0;
	mesh.mlx = 0;
	mesh.mlx_win = 0;
	mesh.render_type = Default;
	mesh.trans.location.x = 100;
	mesh.trans.location.y = 50;
	mesh.trans.location.z = 0;
	mesh.trans.scale.x = 1;
	mesh.trans.scale.y = 1;
	mesh.trans.scale.z = 1;
	return (mesh);
}
