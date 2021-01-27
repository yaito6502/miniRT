/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 04:05:52 by yaito             #+#    #+#             */
/*   Updated: 2021/01/27 06:30:06 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/debug.h"

int		error(char *message)
{
	ft_putendl_fd("ERROR", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	init_environment(t_env *env)
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
}

void	set_mlx(t_env *env, void **mlx, void **mlx_win)
{
	int		x;
	int		y;
	size_t	cam_index;
	t_img	*img;

	*mlx = mlx_init();
	mlx_get_screen_size(*mlx, &x, &y);
	env->resolution.width = MIN(x, env->resolution.width);
	env->resolution.height = MIN(y, env->resolution.height);
	*mlx_win = mlx_new_window(*mlx, env->resolution.width, env->resolution.height, "miniRT");
	cam_index = 0;
	while (cam_index < env->count.c)
	{
		img = &env->img[cam_index++];
		img->img = mlx_new_image(*mlx, env->resolution.width, env->resolution.height);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
		//printf("img[%p] addr[%p]\n", img->img, img->addr);
		if (!img->img || !img->addr)
			error("failed img setting");
	}
	if (!*mlx || !*mlx_win)
		error("failed mlx setting");
}

void	set_screen_base(t_cam *cam, t_reso *reso)
{
	double aspect;
	double half_h;
	double half_w;
	t_vec3 basis[3];

	aspect = (double)reso->width / reso->height;
	half_w = tan(RADIANS(cam->fov) / 2.0);
	half_h = half_w / aspect;
	basis[2] = cam->unit_vec;
	basis[0] = vec3_cross(VUP, basis[2]);
	if (vec3_length(basis[0]) == 0)
		basis[0] = vec3_cross(vec3_new(0, 0, 1), basis[2]);
	basis[1] = vec3_tonum_fourope(vec3_cross(basis[2], basis[0]), '*', -1);
	cam->u = vec3_tonum_fourope(basis[0], '*', 2.0 * half_w);
	cam->v = vec3_tonum_fourope(basis[1], '*', 2.0 * half_h);
	cam->w = vec3_tovec3_fourope(cam->view, '-', vec3_tonum_fourope(cam->u, '/', 2.0));
	cam->w = vec3_tovec3_fourope(cam->w, '-', vec3_tonum_fourope(cam->v, '/', 2.0));
	cam->w = vec3_tovec3_fourope(cam->w, '+', basis[2]);
}

int		main(int argc, char **argv)
{
	void			*mlx;
	void			*mlx_win;
	static t_env	env = {0};

	if (argc <= 1 || argc >= 4 || !ENDSWITH(argv[1], ".rt"))
		error("Does not follow the input format [./miniRT *.rt]");
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
		error("Does not follow the input format [./miniRT *.rt --save]");
	mlx = NULL;
	mlx_win = NULL;
	readrtfile(argv[1], &env, &environment_check);
	init_environment(&env);
	readrtfile(argv[1], &env, &set_environment);
	set_mlx(&env, &mlx, &mlx_win);
	print_environment(&env); //
	raytrace_iterate(&env);
	if (argc == 3)
		write_bmpfile_iterate(&env, argv[1]);
	else
	{
		mlx_put_image_to_window(mlx, mlx_win, env.img[0].img, 0, 0);
		mlx_loop(mlx);
	}
	exit(EXIT_SUCCESS);
}
