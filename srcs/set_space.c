/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 12:09:32 by yaito             #+#    #+#             */
/*   Updated: 2021/01/27 01:15:35 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_resolution(t_reso *reso, char **params)
{
	reso->width = ft_atof(params[1]);
	reso->height = ft_atof(params[2]);
}

void	set_ambientlight(t_amb *amb, char **params)
{
	amb->light = ft_atof(params[1]);
	set_color(&amb->color, params[2]);
}

void	set_camera(t_cam *cam, char **params)
{
	set_vector3(&cam->view, params[1]);
	set_vector3(&cam->unit_vec, params[2]);
	cam->fov = ft_atof(params[3]);
}

void	set_light(t_light *light, char **params)
{
	set_vector3(&light->point, params[1]);
	light->bright = ft_atof(params[2]);
	set_color(&light->color, params[3]);
}
