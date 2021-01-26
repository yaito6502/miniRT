/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_raytrace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 23:26:17 by yaito             #+#    #+#             */
/*   Updated: 2021/01/26 23:57:21 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	raytrace_iterate(t_env *env, t_img *imgs)
{
	size_t	cam_index;

	cam_index = 0;
	while (cam_index < env->count.c)
	{
		set_screen_base(&env->camera[cam_index], &env->resolution);
		pixel_put(env, &imgs[cam_index], cam_index);
		cam_index++;
	}
}

void	pixel_put(t_env *env, t_img *img, size_t cam_index)
{
	int		x;
	int		y;
	double	uv[2];
	t_ray	ray;
	t_hit	hit;

	y = 0;
	while (y < env->resolution.height)
	{
		x = 0;
		while (x < env->resolution.width)
		{
			uv[0] = (double)x / env->resolution.width;
			uv[1] = (double)y / env->resolution.height;
			ray = get_ray(&env->camera[cam_index], &uv[0], &uv[1]);
			hit = intersect(env, &ray, DBL_MAX);
			if (hit.t == DBL_MAX)
				my_mlx_pixel_put(img, x++, y, convert_rgb_to_color(hit.color.r, hit.color.g, hit.color.b));
			else
				my_mlx_pixel_put(img, x++, y, reflection(env, &ray, &hit));
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_hit	intersect(t_env *env, t_ray *ray, double max_dist)
{
	t_hit	hit;
	size_t	i;

	hit.color.r = 100;
	hit.color.g = 200;
	hit.color.b = 234;
	hit.t = max_dist;
	i = 0;
	while (env->count.sp > i)
		intersect_sphere(&env->sphere[i++], ray, &hit);
	i = 0;
	while (env->count.pl > i)
		intersect_plane(&env->plane[i++], ray, &hit);
	/*i = 0;
	while (env->count.sq > i)
		intersect_square(&env->square[i++], ray, &hit);*/
	i = 0;
	while (env->count.cy > i)
		intersect_cylinder(&env->cylinder[i++], ray, &hit);
	i = 0;
	while (env->count.tr > i)
		intersect_triangle(&env->triangle[i++], ray, &hit);
	return (hit);
}

t_ray	get_ray(t_cam *cam, double *x, double *y)
{
	t_vec3	dir_u;
	t_vec3	dir_v;
	t_vec3	dir_w;
	t_ray	ray;

	dir_u = vec3_tonum_fourope(cam->u, '*', *x);
	dir_v = vec3_tonum_fourope(cam->v, '*', *y);
	dir_w = cam->w;
	ray.origin = cam->view;
	ray.direction = vec3_tovec3_fourope(vec3_tovec3_fourope\
	(vec3_tovec3_fourope(dir_w, '+', dir_u), '+', dir_v), '-', ray.origin);
	ray.direction = vec3_normalize(ray.direction);
	return (ray);
}

t_vec3	get_ray_at(t_ray *ray, double t)
{
	return (vec3_tovec3_fourope(ray->origin, '+', \
	vec3_tonum_fourope(ray->direction, '*', t)));
}
