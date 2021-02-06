/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 21:47:23 by yaito             #+#    #+#             */
/*   Updated: 2021/02/06 20:01:20 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	intersect_sphere(t_sp *sphere, t_ray *ray, t_hit *hit)
{
	double abcd[4];
	double t[3];

	abcd[0] = pow(vec3_length(ray->direction), 2);
	abcd[1] = 2 * vec3_dot(vec3_tovec3_fourope(\
		ray->origin, '-', sphere->center), ray->direction);
	abcd[2] = pow(vec3_length(vec3_tovec3_fourope(\
		ray->origin, '-', sphere->center)), 2) - pow(sphere->diameter / 2, 2);
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0)
		return ;
	t[0] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);
	t[1] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
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
	hit->normal = vec3_normalize(vec3_tovec3_fourope(\
		get_ray_at(ray, hit->t), '-', sphere->center));
}

void	intersect_plane(t_pl *pl, t_ray *ray, t_hit *hit)
{
	double	t;

	t = orthogonal(&pl->unit_vec, &pl->pos, ray, hit->t);
	if (t == hit->t)
		return ;
	hit->color = pl->color;
	hit->t = t;
	hit->normal = pl->unit_vec;
}

void	intersect_square(t_sq *sq, t_ray *ray, t_hit *hit)
{
	t_vec3 m;
	t_vec3 p;
	double l1;
	double l2;
	double t;

	t = orthogonal(&sq->unit_vec, &sq->center, ray, hit->t);
	if (t == hit->t)
		return ;
	m = vec3_new(1, 0, 0);
	if (vec3_length(vec3_cross(m, sq->unit_vec)) == 0)
		m = vec3_new(0, 1, 0);
	m = vec3_normalize(vec3_cross(m, sq->unit_vec));
	p = vec3_normalize(vec3_cross(m, sq->unit_vec));
	l1 = abs(vec3_dot(\
		m, vec3_tovec3_fourope(get_ray_at(ray, t), '-', sq->center)));
	l2 = abs(vec3_dot(\
		p, vec3_tovec3_fourope(get_ray_at(ray, t), '-', sq->center)));
	if (l1 > (sq->size / 2) || l2 > (sq->size / 2))
		return ;
	hit->color = sq->color;
	hit->t = t;
	hit->normal = sq->unit_vec;
}

void	intersect_cylinder(t_cy *cy, t_ray *ray, t_hit *hit)
{
	double	abcd[4];
	double	t[3];
	t_vec3	cross[2];

	cross[0] = vec3_cross(ray->direction, cy->unit_vec);
	if (vec3_length(cross[0]) == 0)
		return ;
	cross[1] = vec3_cross(vec3_tovec3_fourope(\
		ray->origin, '-', cy->pos), cy->unit_vec);
	abcd[0] = pow(vec3_length(cross[0]), 2);
	abcd[1] = 2 * vec3_dot(cross[0], cross[1]);
	abcd[2] = pow(vec3_length(cross[1]), 2) - pow(cy->diameter / 2, 2);
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0)
		return ;
	t[0] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);
	t[1] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
	intersect_cylinder_normal(cy, ray, hit, t[0]);
	if (intersect_cylinder_normal(cy, ray, hit, t[1]))
		hit->normal = vec3_tonum_fourope(hit->normal, '/', -1);
}

void	intersect_triangle(t_tr *tr, t_ray *ray, t_hit *hit)
{
	double	t;
	t_vec3	normal;
	t_vec3	abc[3];
	t_vec3	p_abc[3];

	abc[0] = vec3_tovec3_fourope(tr->second, '-', tr->first);
	abc[1] = vec3_tovec3_fourope(tr->third, '-', tr->second);
	normal = vec3_normalize(vec3_cross(abc[1], abc[0]));
	t = orthogonal(&normal, &tr->first, ray, hit->t);
	if (t == hit->t)
		return ;
	p_abc[0] = vec3_cross(vec3_tovec3_fourope(get_ray_at(ray, t), \
	'-', tr->first), abc[0]);
	p_abc[1] = vec3_cross(vec3_tovec3_fourope(get_ray_at(ray, t), \
	'-', tr->second), abc[1]);
	p_abc[2] = vec3_cross(vec3_tovec3_fourope(get_ray_at(ray, t), \
	'-', tr->third), vec3_tovec3_fourope(tr->first, '-', tr->third));
	if ((vec3_dot(normal, p_abc[0]) > 0 && vec3_dot(normal, p_abc[1]) > 0 && \
	vec3_dot(normal, p_abc[2]) > 0) || (vec3_dot(normal, p_abc[0]) < 0 && \
	vec3_dot(normal, p_abc[1]) < 0 && vec3_dot(normal, p_abc[2]) < 0))
	{
		hit->color = tr->color;
		hit->t = t;
		hit->normal = normal;
	}
}
