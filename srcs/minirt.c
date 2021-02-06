/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 04:05:52 by yaito             #+#    #+#             */
/*   Updated: 2021/02/06 20:01:33 by yaito            ###   ########.fr       */
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

void	display(t_env *env, t_mlxptr *mlx)
{
	mlx->window = mlx_new_window(\
		mlx->mlx, env->resolution.width, env->resolution.height, "miniRT");
	if (mlx->cam_length != 0)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->window, env->img[0].img, 0, 0);
		mlx_hook(mlx->window, FOCUSIN, FOCUSCHANGEMASK, rewrite, mlx);
	}
	mlx_hook(mlx->window, KEYPRESS, KEYPRESSMASK, recieve_entry, mlx);
	mlx_hook(mlx->window, CLIENTMESSAGE, STRUCTURENOTIFYMASK, escape, mlx);
	mlx_loop(mlx->mlx);
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
	line = NULL;
	while (result && ((result = get_next_line(fd, &line)) || 1))
	{
		if (result == ERROR || \
		((params = ft_split_multi(line, " \t\v\f\r"))) == NULL)
			error(strerror(errno));
		(*set)(env, params);
		free_params(params);
		safe_free(line);
	}
	close(fd);
}

int		main(int argc, char **argv)
{
	static t_mlxptr	mlx;
	static t_env	env = {0};

	if (argc <= 1 || argc >= 4 || !endswith(argv[1], ".rt"))
		error("Does not follow the input format [./miniRT *.rt]");
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
		error("Does not follow the input format [./miniRT *.rt --save]");
	readrtfile(argv[1], &env, &environment_check);
	if (env.count.r == 0)
		error("R option is required");
	init_environment(&env, &mlx);
	readrtfile(argv[1], &env, &set_environment);
	set_mlx(&mlx, &env);
	raytrace(&env);
	if (argc == 3)
		write_bmpfile_iterate(&env, argv[1]);
	else
		display(&env, &mlx);
	return (0);
}
