#include "cub3d.h"

static void	free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	destroy_config(t_config *cf)
{
	free(cf->no_tex_path);
	free(cf->so_tex_path);
	free(cf->we_tex_path);
	free(cf->ea_tex_path);
	free_strs(cf->map);
}
