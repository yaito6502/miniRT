/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 21:47:23 by yaito             #+#    #+#             */
/*   Updated: 2021/01/25 01:56:25 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/debug.h"

void	intersect_sphere(t_sp *sphere, t_ray *ray, t_hit *hit)
{
	double abcd[4];
	double t[3];

	abcd[0] = pow(vec3_length(ray->direction), 2);
	abcd[1] = 2 * vec3_dot(vec3_tovec3_fourope\
	(ray->origin, '-', sphere->center), ray->direction);
	abcd[2] = pow(vec3_length(vec3_tovec3_fourope\
	(ray->origin, '-', sphere->center)), 2) - pow(sphere->diameter / 2, 2);
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0)
		return ;
	t[0] = (-abcd[1] - sqrt(abcd[3])) / 2 * abcd[0];
	t[1] = (-abcd[1] + sqrt(abcd[3])) / 2 * abcd[0];
	if (t[0] > 0)
		t[2] = t[0];
	else if (t[1] > 0)
		t[2] = t[1];
	else
		return ;
	if (hit->t < t[2])
		return ;
	hit->color = sphere->color;
	hit->t = t[2];
	hit->normal = vec3_normalize(vec3_tovec3_fourope\
	(get_ray_at(ray, hit->t), '-', sphere->center));
}

void	intersect_plane(t_pl *pl, t_ray *ray, t_hit *hit)
{
	double	t;
	double	in_product;
	t_vec3	normal;

	normal = pl->unit_vec;
	in_product = vec3_dot(ray->direction, normal);
	if (in_product == 0)
		return ;
	if (in_product < 0)
		normal = vec3_tonum_fourope(normal, '*', -1);
	t = vec3_dot(vec3_tovec3_fourope(pl->pos, '-', ray->origin), normal) \
	/ vec3_dot(ray->direction, normal);
	if (t < 0 || hit->t < t)
		return ;
	hit->color = pl->color;
	hit->t = t;
	hit->normal = normal;
}

/*
void	intersect_square(t_sq *sq, t_ray *ray, t_hit *hit)
{
}
*/

void	intersect_cylinder(t_cy *cy, t_ray *ray, t_hit *hit)
{
	double	abcd[4];
	double	t[3];
	t_vec3	cross[2];
	t_vec3	p_c;

	cross[0] = vec3_cross(ray->direction, cy->unit_vec);
	if (vec3_length(cross[0]) < 0)
		return ;
	cross[1] = vec3_cross(vec3_tovec3_fourope(ray->origin, '-', cy->pos), cy->unit_vec);
	abcd[0] = pow(vec3_length(cross[0]), 2);
	abcd[1] = 2 * vec3_dot(cross[0], cross[1]);
	abcd[2] = pow(vec3_length(cross[1]), 2) - pow(cy->diameter / 2, 2);
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0)
		return ;
	t[0] = (-abcd[1] - sqrt(abcd[3])) / 2 * abcd[0];
	t[1] = (-abcd[1] + sqrt(abcd[3])) / 2 * abcd[0];
	if (ISRANGE(vec3_dot(vec3_tovec3_fourope(get_ray_at(ray, t[0]), '-', cy->pos), cy->unit_vec), 0, cy->height) && t[0] > 0 && hit->t > t[0])
	{
		p_c = vec3_tovec3_fourope(get_ray_at(ray, t[0]), '-', cy->pos);
		hit->normal = vec3_tovec3_fourope(p_c, '-', vec3_tonum_fourope(cy->unit_vec, '*', vec3_dot(p_c, cy->unit_vec)));
		hit->normal = vec3_tonum_fourope(hit->normal, '/', vec3_length(hit->normal));
	}
	else if (ISRANGE(vec3_dot(vec3_tovec3_fourope(get_ray_at(ray, t[1]), '-', cy->pos), cy->unit_vec), 0, cy->height) && t[1] > 0 && hit->t > t[1])
	{
		printf("t[1]");
		p_c = vec3_tovec3_fourope(get_ray_at(ray, t[1]), '-', cy->pos);
		hit->normal = vec3_tovec3_fourope(get_ray_at(ray, t[1]), '-', vec3_tonum_fourope(cy->unit_vec, '*', vec3_dot(p_c, cy->unit_vec)));
		hit->normal = vec3_tonum_fourope(hit->normal, '/', vec3_length(hit->normal) * -1);
	}
	else
		return ;
	hit->color = cy->color;
}

void	intersect_triangle(t_tr *tr, t_ray *ray, t_hit *hit)
{
	double	t;
	double	in_product;
	t_vec3	normal;
	t_vec3	abc[3];
	t_vec3	p_abc[3];

	abc[0] = vec3_tovec3_fourope(tr->second, '-', tr->first);
	abc[1] = vec3_tovec3_fourope(tr->third, '-', tr->second);
	abc[2] = vec3_tovec3_fourope(tr->first, '-', tr->third);
	normal = vec3_cross(abc[0], vec3_tonum_fourope(abc[2], '*', -1));
	normal = vec3_normalize(normal);
	in_product = vec3_dot(ray->direction, normal);
	if (in_product == 0)
		return ;
	if (in_product < 0)
		normal = vec3_tonum_fourope(normal, '*', -1);
	t = vec3_dot(vec3_tovec3_fourope(tr->first, '-', ray->origin), normal) / vec3_dot(ray->direction, normal);
	if (t < 0 || hit->t < t)
		return ;
	p_abc[0] = vec3_cross(vec3_tovec3_fourope(get_ray_at(ray, t), '-', tr->first), abc[0]);
	p_abc[1] = vec3_cross(vec3_tovec3_fourope(get_ray_at(ray, t), '-', tr->second), abc[1]);
	p_abc[2] = vec3_cross(vec3_tovec3_fourope(get_ray_at(ray, t), '-', tr->third), abc[2]);
	if ((vec3_dot(normal, p_abc[0]) > 0 && vec3_dot(normal, p_abc[1]) > 0 && vec3_dot(normal, p_abc[2]) > 0) || (vec3_dot(normal, p_abc[0]) < 0 && vec3_dot(normal, p_abc[1]) < 0 && vec3_dot(normal, p_abc[2]) < 0))
	{
		hit->color = tr->color;
		hit->t = t;
		hit->normal = normal;
	}
}
