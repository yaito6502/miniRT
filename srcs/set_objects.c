/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 12:06:49 by yaito             #+#    #+#             */
/*   Updated: 2021/01/23 23:21:06 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_sphere(t_sp *sphere, char **params)
{
	set_vector3(&sphere->center, params[1]);
	sphere->diameter = ft_atof(params[2]);
	set_color(&sphere->color, params[3]);
}

void	set_plane(t_pl *plane, char **params)
{
	set_vector3(&plane->pos, params[1]);
	set_vector3(&plane->unit_vec, params[2]);
	set_color(&plane->color, params[3]);
}

void	set_square(t_sq *square, char **params)
{
	set_vector3(&square->center, params[1]);
	set_vector3(&square->unit_vec, params[2]);
	square->size = ft_atof(params[3]);
	set_color(&square->color, params[4]);
}

void	set_cylinder(t_cy *cylinder, char **params)
{
	set_vector3(&cylinder->pos, params[1]);
	set_vector3(&cylinder->unit_vec, params[2]);
	cylinder->diameter = ft_atof(params[3]);
	cylinder->height = ft_atof(params[4]);
	set_color(&cylinder->color, params[5]);
}

void	set_triangle(t_tr *triangle, char **params)
{
	set_vector3(&triangle->first, params[1]);
	set_vector3(&triangle->second, params[2]);
	set_vector3(&triangle->third, params[3]);
	set_color(&triangle->color, params[4]);
}
