/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 12:03:55 by yaito             #+#    #+#             */
/*   Updated: 2021/01/27 02:10:21 by yaito            ###   ########.fr       */
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
		set_ambientlight(&env->ambientlight, params);
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
