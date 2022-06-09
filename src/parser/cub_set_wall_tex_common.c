/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_set_wall_tex_common.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:11:43 by iyamada           #+#    #+#             */
/*   Updated: 2022/06/09 22:33:20 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	read_xpm_image(t_texture *tex, t_cub *cub, char *path)
{
	void	*mlx;

	mlx = cub->window->mlx;
	tex->img->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
}

static void	set_xpm_image_address(t_texture *tex)
{
	t_img	*img;

	img = tex->img;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

t_texture	*new_texture(t_cub *cub, char *file)
{
	t_texture	*tex;

	tex = ft_calloc(1, sizeof(t_texture));
	tex->img = ft_calloc(1, sizeof(t_img));
	read_xpm_image(tex, cub, file);
	if (tex->img->img == NULL)
		return (tex);
	set_xpm_image_address(tex);
	return (tex);
}

t_error	init_texture(t_texture *tex, t_cub *cub, char *file)
{
	tex->img = ft_calloc(1, sizeof(t_img));
	read_xpm_image(tex, cub, file);
	if (tex->img->img == NULL)
		return (XPM_FILE_FORMAT_ERR);
	set_xpm_image_address(tex);
	return (NO_ERR);
}

t_error	set_texture_var(t_cub *cub, t_config *config)
{
	cub->map->north = new_texture(cub, config->no_tex_path);
	if (cub->map->north->img->img == NULL)
		return (XPM_FILE_FORMAT_ERR);
	cub->map->south = new_texture(cub, config->so_tex_path);
	if (cub->map->south->img->img == NULL)
		return (XPM_FILE_FORMAT_ERR);
	cub->map->east = new_texture(cub, config->ea_tex_path);
	if (cub->map->east->img->img == NULL)
		return (XPM_FILE_FORMAT_ERR);
	cub->map->west = new_texture(cub, config->we_tex_path);
	if (cub->map->west->img->img == NULL)
		return (XPM_FILE_FORMAT_ERR);
	return (NO_ERR);
}
