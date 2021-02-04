/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:25:39 by yaito             #+#    #+#             */
/*   Updated: 2021/02/03 23:44:51 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	write_bmpfile_iterate(t_env *env, char *filename)
{
	size_t	cam_index;

	cam_index = 0;
	while (cam_index < env->count.c)
	{
		write_bmpfile(\
			filename, &env->img[cam_index], &env->resolution, cam_index);
		cam_index++;
	}
}

void	write_bmpfile(\
	const char *filename, t_img *img, t_reso *reso, size_t index)
{
	int						fd;
	static char				*bmp_file;
	static unsigned char	header_buf[DEFAULT_HEADER_SIZE];
	static t_file			*file = (t_file*)(header_buf + 2);
	static t_info			*info = (t_info*)(header_buf + FILE_HEADER_SIZE);

	if (!filename || !img || !reso)
		error(strerror(EINVAL));
	if ((bmp_file = get_path(\
		"./bmp_files/", (char*)filename, index, ".bmp")) == NULL)
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

char	*get_path(\
	char *new_path, char *filepath, size_t index, const char *new_extension)
{
	char			*new_file;
	char			*file_name;
	char			*offset;
	char			*index_name;
	size_t			len;

	if ((index_name = ft_itoa(index)) == NULL)
		return (NULL);
	if ((new_path = ft_strjoin(new_path, index_name)) == NULL)
	{
		SAFE_FREE(index_name);
		return (NULL);
	}
	file_name = ft_strrchr(filepath, '/');
	file_name = (file_name == NULL ? filepath : file_name + 1);
	offset = ft_strrchr(file_name, '.');
	offset = (offset == NULL ? NULL : offset);
	len = ft_strlen(new_path) + ft_strlen(file_name) \
	- ft_strlen(offset) + ft_strlen(new_extension) + 1;
	if ((new_file = malloc(len)) == NULL)
		return (NULL);
	ft_strlcpy(new_file, new_path, len);
	ft_strlcat(new_file, file_name, len);
	ft_strlcpy(new_file + ft_strlen(new_file) \
	- ft_strlen(offset), new_extension, len);
	SAFE_FREE(new_path);
	SAFE_FREE(index_name);
	return (new_file);
}
