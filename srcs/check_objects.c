/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 05:04:38 by yaito             #+#    #+#             */
/*   Updated: 2021/02/03 22:50:16 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	sphere_check(char **params)
{
	if (get_memcount(params) != SP_MEMCOUNT)
		error("Does not follow the input format [sp [vec3] [>0.0] [rgb] ]");
	vector3_check(params[1], false);
	if (!ISRANGE(ft_atof(params[2]), 0.0, DBL_MAX))
		error("Does not follow the input format [sp [vec3] [>0.0] [rgb] ]");
	rgbcolor_check(params[3]);
}

void	plane_check(char **params)
{
	if (get_memcount(params) != PL_MEMCOUNT)
		error("Does not follow the input format\
		[pl] [vec3] [vec3_unit] [rgb] ]");
	vector3_check(params[1], false);
	vector3_check(params[2], true);
	rgbcolor_check(params[3]);
}

void	square_check(char **params)
{
	if (get_memcount(params) != SQ_MEMCOUNT)
		error("Does not follow the input format\
		[sq [vec3] [vec3_unit] [>0.0] [rgb] ]");
	vector3_check(params[1], false);
	vector3_check(params[2], true);
	if (!ISRANGE(ft_atof(params[3]), 0.0, DBL_MAX))
		error("Does not follow the input format\
		[sq [vec3] [vec3_unit] [>0.0] [rgb] ]");
	rgbcolor_check(params[4]);
}

void	cylinder_check(char **params)
{
	if (get_memcount(params) != CY_MEMCOUNT)
		error("Does not follow the input format\
		[cy [vec3] [vec3_unit] [>0.0] [>0.0] [rgb] ]");
	vector3_check(params[1], false);
	vector3_check(params[2], true);
	if (!(ISRANGE(ft_atof(params[3]), 0.0, DBL_MAX) &&
	ISRANGE(ft_atof(params[4]), 0.0, DBL_MAX)))
		error("Does not follow the input format\
		[cy [vec3] [vec3_unit] [>0.0] [>0.0] [rgb] ]");
	rgbcolor_check(params[5]);
}

void	triangle_check(char **params)
{
	if (get_memcount(params) != TR_MEMCOUNT)
		error("Does not follow the input format\
		[tr [vec3] [vec3] [vec3] [rgb] ]");
	vector3_check(params[1], false);
	vector3_check(params[2], false);
	vector3_check(params[3], false);
	rgbcolor_check(params[4]);
}
