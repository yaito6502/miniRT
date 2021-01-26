/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:25:39 by yaito             #+#    #+#             */
/*   Updated: 2021/01/27 00:03:46 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#define FILE_TYPE 0x4D42
#define DEFAULT_HEADER_SIZE 54
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

void	write_bmpfile_iterate(t_env *env, t_img *img, char *filename)
{
	size_t	cam_index;
	char	file_index[2];

	cam_index = 0;
	while (cam_index < env->count.c)
	{
		file_index[0] = cam_index + '0';
		file_index[1] = '\0';
		if ((filename = ft_strjoin(filename, file_index)) == NULL)
			error(strerror(errno));
		write_bmpfile(filename, &img[cam_index++], &env->resolution);
		SAFE_FREE(filename);
	}
}

void	write_bmpfile(const char *filename, t_img *img, t_reso *reso)
{
	int						fd;
	static char				*bmp_file;
	static unsigned char	header_buf[DEFAULT_HEADER_SIZE];
	static t_file			*file = (t_file*)(header_buf + 2);
	static t_info			*info = (t_info*)(header_buf + FILE_HEADER_SIZE);

	if (!filename || !img || !reso)
		error(strerror(EINVAL));
	if ((bmp_file = get_path("./bmp_files/", (char*)filename, ".bmp")) == NULL)
		error(strerror(errno));
	if ((fd = open(bmp_file, O_WRONLY | O_CREAT, S_IREAD | S_IWRITE)) == ERROR)
		error(strerror(errno));
	SAFE_FREE(bmp_file);
	header_buf[0] = 0x42;
	header_buf[1] = 0x4D;
	set_header(file, info, img, reso);
	if (write(fd, header_buf, DEFAULT_HEADER_SIZE) == ERROR)
	{
		close(fd);
		error(strerror(errno));
	}
	if (write_image_to_bmp(fd, img, reso) == ERROR)
		error(strerror(errno));
	close(fd);
}

char	*get_path(const char *new_path, char *filepath, const char *new_extension)
{
	char			*new_file;
	char			*file_name;
	char			*offset;
	size_t			len;

	file_name = ft_strrchr(filepath, '/');
	file_name = (file_name == NULL ? filepath : file_name + 1);
	offset = ft_strrchr(file_name, '.');
	offset = (offset == NULL ? NULL : offset);
	len = ft_strlen(new_path) + ft_strlen(file_name) - ft_strlen(offset) + ft_strlen(new_extension) + 1;
	if ((new_file = malloc(len)) == NULL)
		return (NULL);
	ft_strlcpy(new_file, new_path, len);
	ft_strlcat(new_file, file_name, len);
	ft_strlcpy(new_file + ft_strlen(new_file) - ft_strlen(offset), new_extension, len);
	printf("%s\n", new_file);
	return (new_file);
}

void	set_header(t_file *file, t_info *info, t_img *img, t_reso *reso)
{
	file->filesize = DEFAULT_HEADER_SIZE + img->line_length * reso->height;
	file->reserved = 0;
	file->offbits = DEFAULT_HEADER_SIZE;
	info->infosize = INFO_HEADER_SIZE;
	info->img_width = reso->width;
	info->img_height = reso->height;
	info->planes = 1;
	info->bitcount = img->bits_per_pixel;
	info->compression = 0;
	info->sizeimage = img->line_length * reso->height;
	info->pixpermeter_x = 0;
	info->pixpermeter_y = 0;
	info->colorused = 0;
	info->colorimp = 0;
}

//これを呼ぶとなぜかbmpが真っ暗(全て0)になる
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

int		write_image_to_bmp(int fd, t_img *img, t_reso *reso)
{
	unsigned char	*row;
	unsigned char	*buf;
	int				x;
	int				y;

	if ((buf = ft_calloc(img->line_length, sizeof(char))) == NULL)
		return (ERROR);
	y = reso->height;
	while (y-- > 0)
	{
		row = buf;
		x = 0;
		while (x < reso->width)
		{
			my_mlx_pixel_write(img, x, y, row + x * 4);
			x++;
		}
		if (write(fd, buf, img->line_length) == ERROR)
		{
			SAFE_FREE(buf);
			return (ERROR);
		}
	}
	SAFE_FREE(buf);
	return (END);
}
