/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 04:02:37 by yaito             #+#    #+#             */
/*   Updated: 2021/02/05 00:00:48 by yaito            ###   ########.fr       */
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

void	readrtfile(char *filename, t_env *env, void (*set)(t_env *, char **))
{
	int		fd;
	int		result;
	char	*line;
	char	**params;

	if ((fd = open(filename, O_RDONLY)) == ERROR)
		error(strerror(errno));
	result = READ;
	while (result && ((result = get_next_line(fd, &line)) || 1))
	{
		if (result == ERROR || ((params = ft_split(line, ' '))) == NULL)
			error(strerror(errno));
		(*set)(env, params);
		printf("line[%s]\n", line);
		free_params(params);
		if (result != END)
			SAFE_FREE(line);
	}
	close(fd);
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
