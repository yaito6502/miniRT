/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 04:02:37 by yaito             #+#    #+#             */
/*   Updated: 2021/01/27 01:52:08 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft/libft.h"
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
	while (result && ((result = get_next_line(fd, &line)) || 1))
	{
		if (result == ERROR || ((params = ft_split(line, ' '))) == NULL)
			error(strerror(errno));
		(*set)(env, params);
		free_params(params);
		if (result == END)
			break ;
		else
			SAFE_FREE(line);
	}
	close(fd);
}
