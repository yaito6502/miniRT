/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 23:09:53 by yaito             #+#    #+#             */
/*   Updated: 2021/01/23 23:20:19 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_vector3(t_vec3 *vec3)
{
	printf("[%lf, %lf, %lf] \n", vec3->x, vec3->y, vec3->z);
}

void	print_color(t_rgb *color)
{
	printf("color[%d, %d, %d] \n", color->r, color->g, color->b);
}

void	print_environment(t_env *env)
{
	printf("resolution : ");
	printf("width[%d] ", env->resolution.width);
	printf("height[%d]\n", env->resolution.height);
	printf("ambientlight : ");
	printf("light[%lf] ", env->ambientlight.light);
	print_color(&env->ambientlight.color);
	for(size_t i = 0; i < env->count.c; i++)
	{
		printf("camera[%ld] : ", i);
		printf("view");
		print_vector3(&env->camera[i].view);
		printf("unit_vec");
		print_vector3(&env->camera[i].unit_vec);
		printf("fov[%d]\n", env->camera[i].fov);
	}
	for(size_t i = 0; i < env->count.l; i++)
	{
		printf("light[%ld] : ", i);
		printf("point");
		print_vector3(&env->light[i].point);
		printf("bright[%lf] ", env->light[i].bright);
		print_color(&env->light[i].color);
	}
	for(size_t i = 0; i < env->count.sp; i++)
	{
		printf("sphere[%ld] : ", i);
		printf("center");
		print_vector3(&env->sphere[i].center);
		printf("diameter[%lf] ", env->sphere[i].diameter);
		print_color(&env->sphere[i].color);
	}
	for(size_t i = 0; i < env->count.pl; i++)
	{
		printf("plane[%ld] : ", i);
		printf("pos");
		print_vector3(&env->plane[i].pos);
		printf("unit_vec");
		print_vector3(&env->plane[i].unit_vec);
		print_color(&env->plane[i].color);
	}
	for(size_t i = 0; i < env->count.sq; i++)
	{
		printf("square[%ld] : ", i);
		printf("center");
		print_vector3(&env->square[i].center);
		printf("unit_vec");
		print_vector3(&env->square[i].unit_vec);
		printf("size[%lf] ", env->square[i].size);
		print_color(&env->square[i].color);
	}
	for(size_t i = 0; i < env->count.cy; i++)
	{
		printf("cylinder[%ld] : ", i);
		printf("pos");
		print_vector3(&env->cylinder[i].pos);
		printf("unit_vec");
		print_vector3(&env->cylinder[i].unit_vec);
		printf("diameter[%lf] ", env->cylinder[i].diameter);
		printf("height[%lf] ", env->cylinder[i].height);
		print_color(&env->cylinder[i].color);
	}
	for(size_t i = 0; i < env->count.tr; i++)
	{
		printf("triangle[%ld] : ", i);
		printf("first");
		print_vector3(&env->triangle[i].first);
		printf("second");
		print_vector3(&env->triangle[i].second);
		printf("third");
		print_vector3(&env->triangle[i].third);
		print_color(&env->triangle[i].color);
	}
}
