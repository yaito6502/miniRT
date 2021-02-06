/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_fourope.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:21:07 by yaito             #+#    #+#             */
/*   Updated: 2021/02/03 22:55:40 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec3	vec3_tonum_fourope(t_vec3 vec, char ope, double num)
{
	return (vec3_tovec3_fourope(vec, ope, vec3_new(num, num, num)));
}

t_vec3	vec3_tovec3_fourope(t_vec3 a, char ope, t_vec3 b)
{
	t_vec3 vec;

	if (ope == '+')
		vec = vec3_add(a, b);
	else if (ope == '-')
		vec = vec3_sub(a, b);
	else if (ope == '*')
		vec = vec3_multi(a, b);
	else if (ope == '/')
		vec = vec3_div(a, b);
	else
		error("Does not follow the input format [ope = +,-,*,/]");
	return (vec);
}
