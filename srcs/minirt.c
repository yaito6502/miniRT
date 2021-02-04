/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 04:05:52 by yaito             #+#    #+#             */
/*   Updated: 2021/02/03 23:35:54 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		error(char *message)
{
	ft_putendl_fd("ERROR", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	init_environment(t_env *env, t_mlxptr *mlx)
{
	if ((env->camera = malloc(sizeof(t_cam) * env->count.c)) == NULL)
		error(strerror(errno));
	if ((env->light = malloc(sizeof(t_light) * env->count.l)) == NULL)
		error(strerror(errno));
	if ((env->sphere = malloc(sizeof(t_sp) * env->count.sp)) == NULL)
		error(strerror(errno));
	if ((env->plane = malloc(sizeof(t_pl) * env->count.pl)) == NULL)
		error(strerror(errno));
	if ((env->square = malloc(sizeof(t_sq) * env->count.sq)) == NULL)
		error(strerror(errno));
	if ((env->cylinder = malloc(sizeof(t_cy) * env->count.cy)) == NULL)
		error(strerror(errno));
	if ((env->triangle = malloc(sizeof(t_tr) * env->count.tr)) == NULL)
		error(strerror(errno));
	if ((env->img = malloc(sizeof(t_img) * env->count.c)) == NULL)
		error(strerror(errno));
	if ((mlx->imgs = (t_img**)malloc(sizeof(t_img*) * env->count.c)) == NULL)
		error(strerror(errno));
}

void	set_mlx(t_mlxptr *mlx, t_env *env)
{
	int		x;
	int		y;
	size_t	cam_index;
	t_img	*img;

	if ((mlx->mlx = mlx_init()) == NULL)
		error("failed mlx setting");
	mlx->cam_length = env->count.c;
	mlx->index = 0;
	mlx_get_screen_size(mlx->mlx, &x, &y);
	env->resolution.width = MIN(x, env->resolution.width);
	env->resolution.height = MIN(y, env->resolution.height);
	cam_index = 0;
	while (cam_index < env->count.c)
	{
		img = &env->img[cam_index];
		img->img = mlx_new_image(\
			mlx->mlx, env->resolution.width, env->resolution.height);
		img->addr = mlx_get_data_addr(\
			img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
		if (!img->img || !img->addr)
			error("failed img setting");
		mlx->imgs[cam_index] = &env->img[cam_index];
		cam_index++;
	}
}

int		main(int argc, char **argv)
{
	static t_mlxptr	mlx;
	static t_env	env = {0};

	if (argc <= 1 || argc >= 4 || !ENDSWITH(argv[1], ".rt"))
		error("Does not follow the input format [./miniRT *.rt]");
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
		error("Does not follow the input format [./miniRT *.rt --save]");
	readrtfile(argv[1], &env, &environment_check);
	if (env.count.r == 0)
		error("R option is nessary");
	init_environment(&env, &mlx);
	readrtfile(argv[1], &env, &set_environment);
	set_mlx(&mlx, &env);
	raytrace(&env);
	if (argc == 3)
		write_bmpfile_iterate(&env, argv[1]);
	else
	{
		mlx.window = mlx_new_window(\
			mlx.mlx, env.resolution.width, env.resolution.height, "miniRT");
		if (env.count.c != 0)
		{
			mlx_put_image_to_window(mlx.mlx, mlx.window, env.img[0].img, 0, 0);
			mlx_hook(mlx.window, FOCUSIN, FOCUSCHANGEMASK, rewrite, &mlx);
		}
		mlx_hook(mlx.window, KEYPRESS, KEYPRESSMASK, recieve_entry, &mlx);
		mlx_hook(mlx.window, CLIENTMESSAGE, STRUCTURENOTIFYMASK, escape, &mlx);
		mlx_loop(mlx.mlx);
	}
	return (0);
}
