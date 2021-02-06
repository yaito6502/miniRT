/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_fourope_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:51:26 by yaito             #+#    #+#             */
/*   Updated: 2021/02/03 22:49:54 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3 vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3 vec;

	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return (vec);
}

t_vec3	vec3_multi(t_vec3 a, t_vec3 b)
{
	t_vec3 vec;

	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
	return (vec);
}

t_vec3	vec3_div(t_vec3 a, t_vec3 b)
{
	t_vec3 vec;

	vec.x = a.x / b.x;
	vec.y = a.y / b.y;
	vec.z = a.z / b.z;
	return (vec);
}
