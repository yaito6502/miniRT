/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 05:05:14 by yaito             #+#    #+#             */
/*   Updated: 2021/02/06 04:29:30 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	resolution_check(char **params)
{
	if (get_memcount(params) != RESO_MEMCOUNT)
		error("Does not follow the input format [R [>0] [>0] ]");
	if (!(isrange(ft_atoi(params[1]), 1, INT_MAX) &&
	isrange(ft_atoi(params[2]), 1, INT_MAX)))
		error("Does not follow the input format [R [>0] [>0] ]");
}

void	ambientlight_check(char **params)
{
	if (get_memcount(params) != AMB_MEMCOUNT)
		error("Does not follow the input format [A [0.0:1.0] [rgb] ]");
	if (!isrange(ft_atof(params[1]), 0.0, 1.0))
		error("Does not follow the input format [A [0.0:1.0] [rgb] ]");
	rgbcolor_check(params[2]);
}

void	camera_check(char **params)
{
	if (get_memcount(params) != CAM_MEMCOUNT)
		error("Does not follow the input format\
		[c [vec3] [vec3_unit] [0:180] ]");
	vector3_check(params[1], false);
	vector3_check(params[2], true);
	if (!isrange(ft_atoi(params[3]), 0, 180))
		error("Does not follow the input format\
		[c [vec3] [vec3_unit] [0:180] ]");
}

void	light_check(char **params)
{
	if (get_memcount(params) != LIGHT_MEMCOUNT)
		error("Does not follow the input format [l [vec3] [0.0:1.0] [rgb] ]");
	vector3_check(params[1], false);
	if (!isrange(ft_atoi(params[2]), 0, 1))
		error("Does not follow the input format [l [vec3] [0.0:1.0] [rgb] ]");
	rgbcolor_check(params[3]);
}
