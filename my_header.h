/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 15:57:24 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 15:57:26 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_HEADER_H
# define MY_HEADER_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <float.h>
# define MY_RES_X 600
# define MY_RES_Y 400

typedef enum e_stage
{
	Init,
	MinMax,
	Color,
	Transform,
	Iso,
	Persp,
	Draw,
}				t_stage;
typedef enum e_render_type
{
	Default,
	Isometric,
	Perspective,
}				t_render_type;
typedef struct s_vector2d
{
	int				x;
	int				y;
}				t_vector2d;
typedef struct s_vector2d_double
{
	double			x;
	double			y;
}				t_vector2d_double;
typedef struct s_vector3d
{
	int				x;
	int				y;
	int				z;
}				t_vector3d;
typedef struct s_vector3d_double
{
	double			x;
	double			y;
	double			z;
}				t_vector3d_d;
typedef struct s_transform
{
	t_vector3d				location;
	t_vector3d				rotation;
	t_vector3d_d			scale;
}				t_transform;
typedef struct s_line
{
	t_vector2d			coorda;
	t_vector2d			coordb;
	t_vector2d_double	height;
	t_vector2d			g;
}				t_line;
typedef struct s_vertex
{
	t_vector3d_d			l_loc;
	t_vector3d_d			g_loc;
	int						color;
	t_stage					stage;
	struct s_vertex			*nexth;
	struct s_vertex			*nextv;
}				t_vertex;
typedef struct s_mesh
{
	t_transform			trans;
	t_vertex			*vert;
	double				screen[MY_RES_X][MY_RES_Y];
	t_render_type		render_type;
	void				*mlx;
	void				*mlx_win;
}				t_mesh;
typedef struct s_line_helper
{
	int		dx;
	int		dy;
	int		di;
	int		d;
	int		x;
	int		y;
	double	p;
}				t_line_helper;
void			my_init_hooks(t_mesh *mesh);
void			my_draw_mesh_debug(t_vertex *vertexes, t_mesh *mesh);
void			my_render(t_mesh *mesh);
int				my_grad(t_vector2d gradient, double progress);
void			my_mesh_colorizer(t_vertex *vert, t_vector2d m_m);
int				my_mix_colors(int color1, int color2);
void			my_generate_vertexes(t_mesh *mesh, char *str);
int				ft_atoi(char *str);
char			*ft_itoa(int n);
char			**ft_split(char const *s, char c);
__SIZE_TYPE__	ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
void			my_abort_fdf(t_mesh *mesh);
void			my_apply_transform(t_vertex *vertexes, t_transform transform);
int				my_check_split_size(char **test);
int				my_abs(int x);
double			my_abs_d(double x);
void			my_swap(int *a, int *b);
double			my_get_progress(double min, double now, double max);
double			my_depth(t_vector2d_double height, double progress);
t_line			my_line_reverse(t_line line);
void			my_draw_line_low(t_mesh *mesh, t_line line);
void			my_draw_line_high(t_mesh *mesh, t_line line);
int				my_key_hook(int key, t_mesh *mesh);
t_mesh			mesh_init(void);

/*
 *          Persp
 */

typedef struct s_triangle
{
	t_vector3d_d			vertex[3];
}				t_triangle;
typedef struct s_mat4x4
{
	double			m[4][4];
}				t_mat4x4;
typedef struct s_camera
{
	t_vector3d_d		location;
	double				near;
	double				far;
	double				fov;
	double				aspectratio;
	double				fovrad;
}				t_camera;
t_camera		my_init_camera(void);
t_mat4x4		my_init_matproj(t_camera camera);
void			my_multiplymatrix(t_vector3d_d i, t_vector3d_d *o, t_mat4x4 m);
#endif
