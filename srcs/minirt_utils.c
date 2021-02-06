/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 04:02:37 by yaito             #+#    #+#             */
/*   Updated: 2021/02/06 19:55:21 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	ft_atof(const char *str)
{
	double		integer;
	double		decimal;
	int			sign;

	integer = 0;
	decimal = 1;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (ft_isdigit(*str))
		integer = integer * 10 + (*str++ - '0');
	if (*str == '.')
		while (ft_isdigit(*++str))
			integer += (*str - '0') * (decimal *= 0.1);
	return (integer * sign);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_write(t_img *img, int x, int y, unsigned char *row)
{
	unsigned int color;

	color = *(unsigned int*)(img->addr + (y * img->line_length + x * \
	(img->bits_per_pixel / 8)));
	*row++ = (color & (0xFF));
	*row++ = (color & (0xFF << 8)) >> 8;
	*row++ = (color & (0xFF << 16)) >> 16;
	*row++ = 0x00;
}

double	orthogonal(t_vec3 *base, t_vec3 *pos, t_ray *ray, double hit_t)
{
	double	t;
	double	in_product;

	in_product = vec3_dot(ray->direction, *base);
	if (in_product == 0)
		return (hit_t);
	t = vec3_dot(vec3_tovec3_fourope(*pos, '-', ray->origin), *base) \
	/ vec3_dot(ray->direction, *base);
	if (t < 0 || hit_t < t)
		return (hit_t);
	return (t);
}

bool	intersect_cylinder_normal(t_cy *cy, t_ray *ray, t_hit *hit, double t)
{
	t_vec3 p_c;

	if (t < 0 || hit->t < t)
		return (false);
	if (!isrange(vec3_dot(vec3_tovec3_fourope(
		get_ray_at(ray, t), '-', cy->pos), cy->unit_vec), 0, cy->height))
		return (false);
	p_c = vec3_tovec3_fourope(get_ray_at(ray, t), '-', cy->pos);
	hit->normal = vec3_normalize(vec3_tovec3_fourope(p_c, '-', \
	vec3_tonum_fourope(cy->unit_vec, '*', vec3_dot(p_c, cy->unit_vec))));
	hit->t = t;
	hit->color = cy->color;
	return (true);
}
