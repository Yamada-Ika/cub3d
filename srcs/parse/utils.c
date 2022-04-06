#include "cub3d.h"

size_t	count_row(char **strs)
{
	size_t	row;

	row = 0;
	while (strs[row] != NULL)
		row++;
	return (row);
}

size_t	count_col(char **strs)
{
	return (ft_strlen(strs[0]));
}

bool	has_ext(const char *path, const char *ext)
{
	char	*dot_at;
	size_t	dot_index;

	if (ft_strlen(path) < ft_strlen(ext))
		return (false);
	dot_at = ft_strrchr(path, '.');
	if (dot_at == NULL)
		return (false);
	dot_index = ++dot_at - path;
	if (ft_strcmp(&path[dot_index], ext) != 0)
		return (false);
	return (true);
}

void	debug_config(t_config *this)
{
	fprintf(stderr, "no_tex_path    %s\n", this->no_tex_path);
	fprintf(stderr, "so_tex_path    %s\n", this->so_tex_path);
	fprintf(stderr, "we_tex_path    %s\n", this->we_tex_path);
	fprintf(stderr, "ea_tex_path    %s\n", this->ea_tex_path);
	fprintf(stderr, "floor_color    %d\n", this->floor_color);
	fprintf(stderr, "ceilling_color %d\n", this->ceilling_color);
	fprintf(stderr, "map_col_size   %zu\n", this->map_col_size);
	fprintf(stderr, "map_row_size   %zu\n", this->map_row_size);
	fprintf(stderr, "pos_x          %f\n", this->pos_x);
	fprintf(stderr, "pos_y          %f\n", this->pos_y);
	fprintf(stderr, "dir_x          %f\n", this->dir_x);
	fprintf(stderr, "dir_y          %f\n", this->dir_y);
}
