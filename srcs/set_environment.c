/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 12:03:55 by yaito             #+#    #+#             */
/*   Updated: 2021/02/06 19:55:34 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_environment(t_env *env, char **params)
{
	static size_t c[7] = {0};

	if (!*params)
		return ;
	if (!ft_strncmp(*params, "R", 2))
		set_resolution(&env->resolution, params);
	else if (!ft_strncmp(*params, "A", 2))
		set_ambientlight(&env->amb, params);
	else if (!ft_strncmp(*params, "c", 2))
		set_camera(&env->camera[c[0]++], params);
	else if (!ft_strncmp(*params, "l", 2))
		set_light(&env->light[c[1]++], params);
	else if (!ft_strncmp(*params, "sp", 3))
		set_sphere(&env->sphere[c[2]++], params);
	else if (!ft_strncmp(*params, "pl", 3))
		set_plane(&env->plane[c[3]++], params);
	else if (!ft_strncmp(*params, "sq", 3))
		set_square(&env->square[c[4]++], params);
	else if (!ft_strncmp(*params, "cy", 3))
		set_cylinder(&env->cylinder[c[5]++], params);
	else if (!ft_strncmp(*params, "tr", 3))
		set_triangle(&env->triangle[c[6]++], params);
}

void	set_vector3(t_vec3 *vec3, char *params)
{
	char **vec;

	if ((vec = ft_split(params, ',')) == NULL)
		error(strerror(errno));
	vec3->x = ft_atof(vec[0]);
	vec3->y = ft_atof(vec[1]);
	vec3->z = ft_atof(vec[2]);
	free_params(vec);
}

void	set_color(t_rgb *color, char *params)
{
	char **rgb;

	if ((rgb = ft_split(params, ',')) == NULL)
		error(strerror(errno));
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free_params(rgb);
}

void	set_screen_base(t_cam *cam, t_reso *reso)
{
	double aspect;
	double half_h;
	double half_w;
	t_vec3 basis[3];

	aspect = (double)reso->width / reso->height;
	half_w = tan(cam->fov * M_PI / 180.0 / 2.0);
	half_h = half_w / aspect;
	basis[2] = cam->unit_vec;
	basis[0] = vec3_cross(vec3_new(0, 1, 0), basis[2]);
	if (vec3_length(basis[0]) == 0)
		basis[0] = vec3_cross(vec3_new(0, 0, 1), basis[2]);
	basis[1] = vec3_cross(basis[0], basis[2]);
	cam->u = vec3_tonum_fourope(basis[0], '*', 2.0 * half_w);
	cam->v = vec3_tonum_fourope(basis[1], '*', 2.0 * half_h);
	cam->w = vec3_tovec3_fourope(cam->view, '-', \
	vec3_tonum_fourope(cam->u, '/', 2.0));
	cam->w = vec3_tovec3_fourope(cam->w, '-', \
	vec3_tonum_fourope(cam->v, '/', 2.0));
	cam->w = vec3_tovec3_fourope(cam->w, '+', basis[2]);
}

void	set_mlx(t_mlxptr *mlx, t_env *env)
{
	int		x;
	int		y;
	size_t	cam_index;
	t_img	*img;

	if ((mlx->mlx = mlx_init()) == NULL)
		error("failed mlx setting");
	mlx->cam_length = env->count.c;
	mlx->index = 0;
	mlx_get_screen_size(mlx->mlx, &x, &y);
	env->resolution.width = min(x, env->resolution.width);
	env->resolution.height = min(y, env->resolution.height);
	cam_index = 0;
	while (cam_index < env->count.c)
	{
		img = &env->img[cam_index];
		img->img = mlx_new_image(\
			mlx->mlx, env->resolution.width, env->resolution.height);
		img->addr = mlx_get_data_addr(\
			img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
		if (!img->img || !img->addr)
			error("failed img setting");
		mlx->imgs[cam_index] = &env->img[cam_index];
		cam_index++;
	}
}
