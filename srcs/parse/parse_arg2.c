#include "cub3d.h"

bool	has_ext(const char *path, const char *ext);

int	parse_file_path(const char *path)
{
	if (!has_ext(path, "cub"))
		return (INVALID_CUB_FILE);
	return (NO_ERR);
}

int str_to_rgb(const char *s)
{
	char	*end;
	int		r;
	int		g;
	int		b;

	r = ft_strtoll(s, &end, 10);
	end++;
	g = ft_strtoll(end, &end, 10);
	end++;
	b = ft_strtoll(end, &end, 10);
	return (r << 16 | g << 8 | b);
}

char	*append(char *dst, char *src)
{
	char	*tmp_1;
	char	*tmp_2;
	char	*new;

	tmp_1 = dst;
	tmp_2 = src;
	new = ft_strjoin(dst, src);
	free(tmp_1);
	free(tmp_2);
	return (new);
}

void	set_color(t_config *this, const char *line)
{
	if (line[0] == 'F')
		this->floor_color = str_to_rgb(&line[1]);
	if (line[0] == 'C')
		this->ceilling_color = str_to_rgb(&line[1]);
}
