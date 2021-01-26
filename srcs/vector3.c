/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 12:56:14 by yaito             #+#    #+#             */
/*   Updated: 2021/01/24 22:09:48 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	vec3_tonum_fourope(t_vec3 vec, char ope, double num)
{
	t_vec3 new_vec;

	if (ope == '+')
	{
		new_vec.x = vec.x + num;
		new_vec.y = vec.y + num;
		new_vec.z = vec.z + num;
	}
	else if (ope == '-')
	{
		new_vec.x = vec.x - num;
		new_vec.y = vec.y - num;
		new_vec.z = vec.z - num;
	}
	else if (ope == '*')
	{
		new_vec.x = vec.x * num;
		new_vec.y = vec.y * num;
		new_vec.z = vec.z * num;
	}
	else if (ope == '/')
	{
		new_vec.x = vec.x / num;
		new_vec.y = vec.y / num;
		new_vec.z = vec.z / num;
	}
	else
		error("Does not follow the input format [ope = +,-,*,/]");
	return (new_vec);
}

t_vec3	vec3_tovec3_fourope(t_vec3 a, char ope, t_vec3 b)
{
	t_vec3 vec;

	if (ope == '+')
	{
		vec.x = a.x + b.x;
		vec.y = a.y + b.y;
		vec.z = a.z + b.z;
	}
	else if (ope == '-')
	{
		vec.x = a.x - b.x;
		vec.y = a.y - b.y;
		vec.z = a.z - b.z;
	}
	else if (ope == '*')
	{
		vec.x = a.x * b.x;
		vec.y = a.x * b.y;
		vec.z = a.z * b.z;
	}
	else if (ope == '/')
	{
		vec.x = a.x / b.x;
		vec.y = a.x / b.y;
		vec.z = a.z / b.z;
	}
	else
		error("Does not follow the input format [ope = +,-,*,/]");
	return (vec);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3 vec;

	vec.x = a.y * b.z - b.y * a.z;
	vec.y = a.z * b.x - b.z * a.x;
	vec.z = a.x * b.y - b.x * a.y;
	return (vec);
}

t_vec3	vec3_normalize(t_vec3 vec)
{
	t_vec3	unit;
	double	length;

	length = vec3_length(vec);
	unit.x = vec.x / length;
	unit.y = vec.y / length;
	unit.z = vec.z / length;
	return (unit);
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	vec3_length(t_vec3 vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}
