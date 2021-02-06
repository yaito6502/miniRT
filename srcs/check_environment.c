/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 03:59:13 by yaito             #+#    #+#             */
/*   Updated: 2021/02/06 18:29:23 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	environment_check(t_env *env, char **params)
{
	if (!*params)
		return ;
	if (!ft_strncmp(*params, "R", 2) && ++env->count.r)
		resolution_check(params);
	else if (!ft_strncmp(*params, "A", 2))
		ambientlight_check(params);
	else if (!ft_strncmp(*params, "c", 2) && ++env->count.c)
		camera_check(params);
	else if (!ft_strncmp(*params, "l", 2) && ++env->count.l)
		light_check(params);
	else if (!ft_strncmp(*params, "sp", 3) && ++env->count.sp)
		sphere_check(params);
	else if (!ft_strncmp(*params, "pl", 3) && ++env->count.pl)
		plane_check(params);
	else if (!ft_strncmp(*params, "sq", 3) && ++env->count.sq)
		square_check(params);
	else if (!ft_strncmp(*params, "cy", 3) && ++env->count.cy)
		cylinder_check(params);
	else if (!ft_strncmp(*params, "tr", 3) && ++env->count.tr)
		triangle_check(params);
	else
	{
		error("Does not follow the input format\
		[identifier_list = R,A,c,l,sp,pl,sq,cy,tr]");
	}
}

void	vector3_check(char *param, bool isunit)
{
	char **vec3;

	if ((vec3 = ft_split(param, ',')) == NULL)
		error(strerror(errno));
	if (get_memcount(vec3) != VEC3_MEMCOUNT)
		error("Does not follow the input format [x, y, z]");
	if (isunit)
	{
		if (!(isrange(ft_atof(vec3[0]), -1, 1) && \
		isrange(ft_atof(vec3[1]), -1, 1) && isrange(ft_atof(vec3[2]), -1, 1)))
			error("Does not follow the input format [-1:1],[-1:1],[-1:1]");
	}
	else
	{
		if (!(isrange(ft_atof(vec3[0]), -DBL_MAX, DBL_MAX) && \
		isrange(ft_atof(vec3[1]), -DBL_MAX, DBL_MAX) && \
		isrange(ft_atof(vec3[2]), -DBL_MAX, DBL_MAX)))
			error("Does not follow the input format\
			[d_min:d_max],[d_min:d_max],[d_min:d_max]");
	}
	free_params(vec3);
}

void	rgbcolor_check(char *param)
{
	char **rgb;

	if ((rgb = ft_split(param, ',')) == NULL)
		error(strerror(errno));
	if (get_memcount(rgb) != RGB_MEMCOUNT)
		error("Does not follow the input format [0-255][0-255][0-255]");
	if (!(isrange(ft_atoi(rgb[0]), 0, 0xFF) && \
	isrange(ft_atoi(rgb[1]), 0, 0xFF) && isrange(ft_atoi(rgb[2]), 0, 0xFF)))
		error("Does not follow the input format [0-255][0-255][0-255]");
	free_params(rgb);
}

void	free_params(char **params)
{
	int i;

	i = 0;
	while (params[i] != NULL)
	{
		safe_free(params[i]);
		i++;
	}
	safe_free(params);
}

size_t	get_memcount(char **params)
{
	size_t c;

	c = 0;
	while (params[c] != NULL)
		c++;
	return (c);
}
