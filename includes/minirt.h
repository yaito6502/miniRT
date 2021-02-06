/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:23:46 by yaito             #+#    #+#             */
/*   Updated: 2021/02/06 19:58:40 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <X11/Xlib.h>
# include <X11/extensions/XShm.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "get_next_line_bonus.h"
# define RESO_MEMCOUNT			3
# define AMB_MEMCOUNT			3
# define CAM_MEMCOUNT			4
# define LIGHT_MEMCOUNT			4
# define SP_MEMCOUNT			4
# define PL_MEMCOUNT			4
# define SQ_MEMCOUNT			5
# define CY_MEMCOUNT			6
# define TR_MEMCOUNT			5
# define VEC3_MEMCOUNT			3
# define RGB_MEMCOUNT			3
# define BG_R					0
# define BG_G					0
# define BG_B					0
# define SPEC					0.3
# define SHININESS				20
# define EPSILON				0.001953125
# define KEYPRESS				2
# define FOCUSIN				9
# define CLIENTMESSAGE			33
# define KEYPRESSMASK			1L
# define STRUCTURENOTIFYMASK	131072L
# define FOCUSCHANGEMASK		2097152L
# define ESC					65307
# define RT_ARROW				65363
# define LF_ARROW				65361
# define FILE_TYPE				0x4D42
# define DEFAULT_HEADER_SIZE	54
# define FILE_HEADER_SIZE		14
# define INFO_HEADER_SIZE		40

typedef struct		s_vector3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_rgbcolor
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_resolution
{
	int				width;
	int				height;
}					t_reso;

typedef struct		s_ambientlight
{
	double			light;
	t_rgb			color;
}					t_amb;

typedef struct		s_camera
{
	t_vec3			view;
	t_vec3			unit_vec;
	unsigned int	fov;
	t_vec3			u;
	t_vec3			v;
	t_vec3			w;
}					t_cam;

typedef struct		s_light
{
	t_vec3			point;
	double			bright;
	t_rgb			color;
}					t_light;

typedef struct		s_sphere
{
	t_vec3			center;
	double			diameter;
	t_rgb			color;
}					t_sp;

typedef struct		s_plane
{
	t_vec3			pos;
	t_vec3			unit_vec;
	t_rgb			color;
}					t_pl;

typedef struct		s_square
{
	t_vec3			center;
	t_vec3			unit_vec;
	double			size;
	t_rgb			color;
}					t_sq;

typedef struct		s_cylinder
{
	t_vec3			pos;
	t_vec3			unit_vec;
	double			diameter;
	double			height;
	t_rgb			color;
}					t_cy;

typedef struct		s_triangle
{
	t_vec3			first;
	t_vec3			second;
	t_vec3			third;
	t_rgb			color;
}					t_tr;

typedef struct		s_image {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct		s_objectcount
{
	size_t			r;
	size_t			c;
	size_t			l;
	size_t			sp;
	size_t			pl;
	size_t			sq;
	size_t			cy;
	size_t			tr;
}					t_count;

typedef	struct		s_environment
{
	t_reso			resolution;
	t_amb			amb;
	t_cam			*camera;
	t_light			*light;
	t_sp			*sphere;
	t_pl			*plane;
	t_sq			*square;
	t_cy			*cylinder;
	t_tr			*triangle;
	t_img			*img;
	t_count			count;
}					t_env;

typedef struct		s_ray
{
	t_vec3			origin;
	t_vec3			direction;
}					t_ray;

typedef struct		s_hit_info
{
	t_vec3			normal;
	t_rgb			color;
	double			t;
}					t_hit;

typedef struct		s_mlx_pointers
{
	void			*mlx;
	void			*window;
	size_t			cam_length;
	size_t			index;
	t_img			**imgs;
}					t_mlxptr;

typedef struct		s_bitmap_fileheader
{
	unsigned int	filesize;
	unsigned int	reserved;
	unsigned int	offbits;
}					t_file;

typedef struct		s_bitmap_infoheader
{
	unsigned int	infosize;
	int				img_width;
	int				img_height;
	unsigned short	planes;
	unsigned short	bitcount;
	unsigned int	compression;
	unsigned int	sizeimage;
	int				pixpermeter_x;
	int				pixpermeter_y;
	unsigned int	colorused;
	unsigned int	colorimp;
}					t_info;

int					error(char *message);
void				init_environment(t_env *env, t_mlxptr *mlx);
void				display(t_env *env, t_mlxptr *mlx);
void				readrtfile\
(char *filename, t_env *env, void (*set)(t_env *, char **));

void				environment_check(t_env *env, char **params);
void				resolution_check(char **params);
void				ambientlight_check(char **params);
void				camera_check(char **params);
void				light_check(char **params);
void				sphere_check(char **params);
void				plane_check(char **params);
void				square_check(char **params);
void				cylinder_check(char **params);
void				triangle_check(char **params);
void				vector3_check(char *param, bool isunit);
void				rgbcolor_check(char *param);
void				free_params(char **params);
size_t				get_memcount(char **params);
void				set_environment(t_env *env, char **params);
void				set_color(t_rgb *color, char *params);
void				set_vector3(t_vec3 *vec3, char *params);
void				set_resolution(t_reso *reso, char **params);
void				set_ambientlight(t_amb *amb, char **params);
void				set_camera(t_cam *cam, char **params);
void				set_light(t_light *light, char **params);
void				set_sphere(t_sp *sphere, char **params);
void				set_plane(t_pl *plane, char **params);
void				set_square(t_sq *square, char **params);
void				set_cylinder(t_cy *cylinder, char **params);
void				set_triangle(t_tr *triangle, char **params);
void				set_screen_base(t_cam *cam, t_reso *reso);
void				set_mlx(t_mlxptr *mlx, t_env *env);

void				raytrace(t_env *env);
void				pixel_put(t_env *env, size_t cam_index);
t_hit				intersect(t_env *env, t_ray *ray, double max_dist);
t_ray				get_ray(t_cam *cam, double *x, double *y);
t_vec3				get_ray_at(t_ray *ray, double t);
void				intersect_sphere(t_sp *sphere, t_ray *ray, t_hit *hit);
void				intersect_plane(t_pl *pl, t_ray *ray, t_hit *hit);
void				intersect_square(t_sq *sq, t_ray *ray, t_hit *hit);
void				intersect_cylinder(t_cy *cy, t_ray *ray, t_hit *hit);
void				intersect_triangle(t_tr *tr, t_ray *ray, t_hit *hit);

int					reflection(t_env *env, t_ray *ray, t_hit *hit);
t_rgb				culc_sd(t_light *light, t_ray *ray, t_hit *hit, t_vec3 *l);
t_rgb				culc_ss(t_light *light, t_ray *ray, t_hit *hit, t_vec3 *l);
bool				shadowing(t_env *env, t_ray *ray, t_hit *hit, t_vec3 *l);
int					convert_rgb_to_color(int r, int g, int b);

int					escape();
int					rewrite(t_mlxptr *mlx);
int					recieve_entry(int keycode, t_mlxptr *mlx);

void				write_bmpfile_iterate(t_env *env, char *filename);
void				write_bmpfile\
(const char *filename, t_img *img, t_reso *reso, size_t index);
void				set_header\
(t_file *file, t_info *info, t_img *img, t_reso *reso);
int					write_image_to_bmp(int fd, t_img *img, t_reso *reso);
char				*get_path\
(char *new_path, char *filename, size_t index, const char *new_extension);

t_vec3				vec3_new(double x, double y, double z);
t_vec3				vec3_tonum_fourope(t_vec3 vec, char ope, double num);
t_vec3				vec3_tovec3_fourope(t_vec3 a, char ope, t_vec3 b);
t_vec3				vec3_add(t_vec3 a, t_vec3 b);
t_vec3				vec3_sub(t_vec3 a, t_vec3 b);
t_vec3				vec3_multi(t_vec3 a, t_vec3 b);
t_vec3				vec3_div(t_vec3 a, t_vec3 b);
t_vec3				vec3_cross(t_vec3 a, t_vec3 b);
t_vec3				vec3_normalize(t_vec3 vec);
double				vec3_dot(t_vec3 a, t_vec3 b);
double				vec3_length(t_vec3 vec);

double				ft_atof(const char *str);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
void				my_mlx_pixel_write\
(t_img *img, int x, int y, unsigned char *row);
double				orthogonal\
(t_vec3 *base, t_vec3 *pos, t_ray *ray, double hit_t);
bool				intersect_cylinder_normal\
(t_cy *cy, t_ray *ray, t_hit *hit, double t);

bool				isrange(double value, double min, double max);
double				min(double a, double b);
double				max(double a, double b);
bool				endswith(char *str, char *end);
void				safe_free(void *ptr);

char				**ft_split_multi(char const *s, char *div);

#endif
