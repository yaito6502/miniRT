/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 23:30:16 by yaito             #+#    #+#             */
/*   Updated: 2021/01/28 03:03:20 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/debug.h"

int		convert_rgb_to_color(int r, int g, int b)
{
	r = MIN(r, 0xFF);
	g = MIN(g, 0xFF);
	b = MIN(b, 0xFF);
	return (r << 16 | g << 8 | b);
}

t_rgb	culc_rd(t_light *light, t_hit *hit, t_vec3 *l)
{
	t_rgb	color;
	double	intensity;

	*l = vec3_normalize(*l);
	intensity = MAX(vec3_dot(hit->normal, *l), 0);
	color.r = light->color.r * light->bright * intensity * hit->color.r / 0xFF;
	color.g = light->color.g * light->bright * intensity * hit->color.g / 0xFF;
	color.b = light->color.b * light->bright * intensity * hit->color.b / 0xFF;
	return (color);
}

t_rgb	culc_rs(t_light *light, t_ray *ray, t_hit *hit, t_vec3 *l)
{
	t_rgb	color;
	t_vec3	v;
	t_vec3	r;
	double	intensity;

	*l = vec3_normalize(*l);
	v = vec3_tonum_fourope(ray->direction, '*', -1);
	v = vec3_normalize(v);
	r = vec3_tovec3_fourope(vec3_tonum_fourope(hit->normal, '*', 2 * vec3_dot(hit->normal, *l)), '-', *l);
	r = vec3_normalize(r);
	intensity = pow(vec3_dot(v, r), SHININESS);
	if ((vec3_dot(hit->normal, *l) < 0) || (vec3_dot(v, r) < 0))
		intensity = 0;
	color.r = SPEC * light->color.r * light->bright * intensity;
	color.g = SPEC * light->color.g * light->bright * intensity;
	color.b = SPEC * light->color.b * light->bright * intensity;
	return (color);
}

bool	shadowing(t_env *env, t_ray *ray, t_hit *hit, t_vec3 *l)
{
	t_ray	ray_shadow;
	t_hit	hit_shadow;
	double	diff;

	ray_shadow.origin = vec3_tovec3_fourope(get_ray_at(ray, hit->t), '+', vec3_tonum_fourope(*l, '*', EPSILON));
	ray_shadow.direction = *l;
	diff = vec3_length(*l) - EPSILON;
	hit_shadow = intersect(env, &ray_shadow, diff);
	if (hit_shadow.t == diff)
		return (false);
	return (true);
}

int		reflection(t_env *env, t_ray *ray, t_hit *hit)
{
	size_t	i;
	t_vec3	l;
	t_rgb	r_d;
	t_rgb	r_s;
	t_rgb	color;

	color.r = env->ambientlight.color.r * env->ambientlight.light * hit->color.r / 0xFF;
	color.g = env->ambientlight.color.g * env->ambientlight.light * hit->color.g / 0xFF;
	color.b = env->ambientlight.color.b * env->ambientlight.light * hit->color.b / 0xFF;
	i = 0;
	while (env->count.l > i)
	{
		l = vec3_normalize(vec3_tovec3_fourope(env->light[i].point, '-', get_ray_at(ray, hit->t)));
		if (shadowing(env, ray, hit, &l) && ++i)
			continue ;
		r_d = culc_rd(&env->light[i], hit, &l);
		r_s = culc_rs(&env->light[i++], ray, hit, &l);
		color.r += r_d.r + r_s.r;
		color.g += r_d.g + r_s.g;
		color.b += r_d.b + r_s.b;
	}
	return (convert_rgb_to_color(color.r, color.g, color.b));
}
