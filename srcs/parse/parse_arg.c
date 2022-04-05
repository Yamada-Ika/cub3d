
#include "cub3d.h"

bool	has_ext(const char *path, const char *ext);
int		parse_file_path(const char *path);
int 	str_to_rgb(const char *s);
char	*append(char *dst, char *src);
void	set_color(t_config *this, const char *line);
size_t	count_row(char **strs);
size_t	count_col(char **strs);

bool	validate_arg_num(int ac)
{
	return (ac != 2);
}

char	*remove_char(const char *s, const char c)
{
	char	**strs;
	char	*rs;
	size_t	i;

	strs = ft_split(s, c);
	if (strs == NULL)
		return (NULL);
	i = 0;
	rs = ft_strdup("");
	while (strs[i] != NULL)
	{
		rs = append(rs, strs[i]);
		i++;
	}
	return (rs);
}

void	set_texture_path(t_config *this, const char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		if (line[2] != '\0')
			this->no_tex_path = remove_char(&line[3], '\n');
	}
	if (line[0] == 'S' && line[1] == 'O')
	{
		if (line[2] != '\0')
			this->so_tex_path = remove_char(&line[3], '\n');
	}
	if (line[0] == 'W' && line[1] == 'E')
	{
		if (line[2] != '\0')
			this->we_tex_path = remove_char(&line[3], '\n');
	}
	if (line[0] == 'E' && line[1] == 'A')
	{
		if (line[2] != '\0')
			this->ea_tex_path = remove_char(&line[3], '\n');
	}
}

int	init_config(t_config *this, const char *file)
{
	size_t	read_cnt;
	char	*line;
	char	*one_line;
	char	**char_map;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (CUB_FILE_ERR);
	one_line = ft_strdup("");
	if (one_line == NULL)
	{
		close(fd);
		return (MEM_ERR);
	}
	read_cnt = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] != '\n')
			read_cnt++;
		if (read_cnt <= 4)
			set_texture_path(this, line);
		else if (5 <= read_cnt && read_cnt <= 6)
			set_color(this, line);
		else
		{
			one_line = append(one_line, line);
			if (one_line == NULL)
			{
				close(fd);
				return (MEM_ERR);
			}
			continue ;
		}
		free(line);
	}
	this->map = ft_split(one_line, '\n');
	if (this->map == NULL)
	{
		close(fd);
		return (MEM_ERR);
	}
	close(fd);
	return (NO_ERR);
}

int	parse_arg(t_config *this, int ac, char **av)
{
	t_error	err;

	if (validate_arg_num(ac))
		return (INVALID_ARG_NUM);
	err = parse_file_path(av[1]);
	if (err != NO_ERR)
		return (err);
	err = init_config(this, av[1]);
	if (err != NO_ERR)
		return (err);
	this->map_row_size = count_row(this->map);
	this->map_col_size = count_col(this->map);
	return (NO_ERR);
}
