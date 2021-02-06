/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 19:41:22 by yaito             #+#    #+#             */
/*   Updated: 2021/02/03 23:41:42 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		escape(void)
{
	exit(EXIT_SUCCESS);
}

int		rewrite(t_mlxptr *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->window, \
	mlx->imgs[mlx->index % mlx->cam_length]->img, 0, 0);
	return (0);
}

int		recieve_entry(int keycode, t_mlxptr *mlx)
{
	if (keycode == ESC)
		escape();
	if (mlx->cam_length == 0)
		return (0);
	if (keycode == RT_ARROW || keycode == LF_ARROW)
		mlx_clear_window(mlx->mlx, mlx->window);
	if (keycode == RT_ARROW)
		mlx_put_image_to_window(mlx->mlx, mlx->window, \
		mlx->imgs[++mlx->index % mlx->cam_length]->img, 0, 0);
	if (keycode == LF_ARROW)
		mlx_put_image_to_window(mlx->mlx, mlx->window, \
		mlx->imgs[--mlx->index % mlx->cam_length]->img, 0, 0);
	return (0);
}
