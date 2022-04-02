/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:29 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/02 18:37:42 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_matrix	*gen_world_map(void);
static t_matrix	*strs_to_map(char **map);

static bool	has_ext(const char *path, const char *ext)
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

static int	parse_path(const char *path)
{
	if (!has_ext(path, "cub"))
		return (FAIL);
	return (SUCCESS);
}

static int str_to_rgb(const char *s)
{
	char	*end;
	int		r;
	int		g;
	int		b;

	r = ft_strtoll(s, &end, 10);
	end++; // ,があるはず
	g = ft_strtoll(end, &end, 10);
	end++; // ,があるはず
	b = ft_strtoll(end, &end, 10);
	return (r << 16 | g << 8 | b); // convert to rgb
}

static char	*append(char *dst, char *src)
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

static size_t	count_row(char **strs)
{
	size_t	row;

	row = 0;
	while (strs[row] != NULL)
		row++;
	return (row);
}

static size_t	count_col(char **strs)
{
	return (ft_strlen(strs[0]));
}

static t_matrix	*strs_to_map(char **map)
{
	size_t		usr_map_row;
	size_t		usr_map_col;
	t_matrix	*world_map;
	size_t		i;
	size_t		j;

	usr_map_row = count_row(map);
	usr_map_col = count_col(map);
	world_map = mat_new(usr_map_row, usr_map_col);
	i = 0;
	while (i < usr_map_row)
	{
		j = 0;
		while (j < usr_map_col)
		{
			world_map->values[i][j] = map[i][j] - '0';
			++j;
		}
		++i;
	}
	return (world_map);
}

static t_map	*read_map(const char *file)
{
	size_t	read_cnt;
	t_map	*map;
	char	*line;
	char	*one_line;
	char	**char_map;
	int	fd;

	one_line = ft_strdup("");
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	read_cnt = 0;
	fd = open(file, O_RDONLY);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// TODO: とりあえずテクスチャのファイル名を突っ込んでいる
		if (read_cnt == 0)
		{
			if (line[0] == 'N' && line[1] == 'O')
			{
				if (line[2] != '\0')
					map->no_texture = ft_strdup(&line[3]);
			}
		}
		if (read_cnt == 1)
		{
			if (line[0] == 'S' && line[1] == 'O')
			{
				if (line[2] != '\0')
					map->so_texture = ft_strdup(&line[3]);
			}
		}
		if (read_cnt == 2)
		{
			if (line[0] == 'W' && line[1] == 'E')
			{
				if (line[2] != '\0')
					map->we_texture = ft_strdup(&line[3]);
			}
		}
		if (read_cnt == 3)
		{
			if (line[0] == 'E' && line[1] == 'A')
			{
				if (line[2] != '\0')
					map->ea_texture = ft_strdup(&line[3]);
			}
		}
		if (read_cnt == 5)
		{
			if (line[0] == 'F')
				map->floor_color = str_to_rgb(&line[1]);
		}
		if (read_cnt == 6)
		{
			if (line[0] == 'C')
				map->ceilling_color = str_to_rgb(&line[1]);
		}
		if (read_cnt >= 8)
		{
			one_line = append(one_line, line);
			continue;
		}
		free(line);
		read_cnt++;
	}
	char_map = ft_split(one_line, '\n');
	map->map = strs_to_map(char_map);
	close(fd);
	return (map);
}

static bool	validate_arg_num(int ac)
{
	return (ac != 2);
}

t_map	*parse(int ac, char **av)
{
	if (validate_arg_num(ac))
		return (NULL);
	if (parse_path(av[1]) == FAIL)
		return (NULL);
	return (read_map(av[1]));
}

int	validate_map(t_map *map)
{
	return (SUCCESS);
}

// #include <assert.h>
// #include <string.h>
// // gcc parse_map.c -I ../../includes  -I ../../libmat -I ../../minilibx-linux -L ../../libmat -l mat && ./a.out
// int	main(void)
// {
// 	printf("has_ext test start!\n");
// 	assert(has_ext("hoge.cub", "cub") == true);
// 	assert(has_ext("hoge.c", "cub") == false);
// 	assert(has_ext("hoge.cu", "cub") == false);
// 	assert(has_ext("cub.cub", "cub") == true);
// 	assert(has_ext("cub.cubcub", "cub") == false);
// 	assert(has_ext(".cub", "cub") == true);
// 	printf("has_ext test ok!\n");

// 	printf("append test start!\n");
// 	char	*tmp1;
// 	char	*tmp2;
// 	char	*tmp3;
// 	tmp1 = ft_strdup("hoge");
// 	tmp2 = ft_strdup("fuga");
// 	tmp3 = append(tmp1, tmp2);
// 	assert(strcmp(tmp3, "hogefuga") == 0);
// 	printf("append test ok!\n");

// 	printf("str_to_rgb test start!\n");
// 	assert(str_to_rgb("0,0,0") == 0);
// 	assert(str_to_rgb("255,255,255") == 0xffffff);
// 	assert(str_to_rgb("255,215,0") == 0xffd700);
// 	assert(str_to_rgb("0,128,0") == 0x008000);
// 	printf("str_to_rgb test ok!\n");

// 	printf("parse_path test start!\n");
// 	assert(parse_path("hoge") == FAIL);
// 	assert(parse_path("hoge.cub") == SUCCESS);
// 	printf("parse_path test ok!\n");

// 	printf("read_map test start!\n");
// 	t_map	*map = read_map("../../map/sample.cub");
// 	assert(strcmp(map->no_texture, "./path_to_the_north_texture"));
// 	assert(strcmp(map->so_texture, "./path_to_the_south_texture"));
// 	assert(strcmp(map->we_texture, "./path_to_the_west_texture"));
// 	assert(strcmp(map->ea_texture, "./path_to_the_east_texture"));
// 	assert(map->floor_color == 0xdc6400);
// 	assert(map->ceilling_color == 0xe11e00);
// 	assert((int)(map->map->values[0][0]) == 1);
// 	assert((int)(map->map->values[0][1]) == 1);
// 	assert((int)(map->map->values[0][2]) == 1);
// 	assert((int)(map->map->values[0][3]) == 1);
// 	assert((int)(map->map->values[0][4]) == 1);
// 	assert((int)(map->map->values[1][0]) == 1);
// 	assert((int)(map->map->values[1][1]) == 0);
// 	assert((int)(map->map->values[1][2]) == 0);
// 	assert((int)(map->map->values[1][3]) == 0);
// 	assert((int)(map->map->values[1][4]) == 1);
// 	assert((int)(map->map->values[2][0]) == 1);
// 	assert((int)(map->map->values[2][1]) == 0);
// 	assert((int)(map->map->values[2][2]) == 0);
// 	assert((int)(map->map->values[2][3]) == 0);
// 	assert((int)(map->map->values[2][4]) == 1);
// 	assert((int)(map->map->values[3][0]) == 2);
// 	assert((int)(map->map->values[3][1]) == 0);
// 	assert((int)(map->map->values[3][2]) == 0);
// 	assert((int)(map->map->values[3][3]) == 0);
// 	assert((int)(map->map->values[3][4]) == 2);
// 	assert((int)(map->map->values[4][0]) == 1);
// 	assert((int)(map->map->values[4][1]) == 0);
// 	assert((int)(map->map->values[4][2]) == 0);
// 	assert((int)(map->map->values[4][3]) == 0);
// 	assert((int)(map->map->values[4][4]) == 1);
// 	assert((int)(map->map->values[5][0]) == 1);
// 	assert((int)(map->map->values[5][1]) == 1);
// 	assert((int)(map->map->values[5][2]) == 1);
// 	assert((int)(map->map->values[5][3]) == 1);
// 	assert((int)(map->map->values[5][4]) == 1);
// 	printf("read_map test end!\n");
// }

// t_map	*parse_map(const char *map_file)
// {
// 	t_map	*map_info;

// 	map_info = ft_calloc(sizeof(t_map));
// 	map_info->map = gen_world_map();
// 	return (map_info);
// }

// //debug
// static t_matrix	*gen_world_map(void)
// {
// 	const size_t usr_map_row = 6;
// 	const size_t usr_map_col = 5;
// 	char	usr_map[6][5] = {{1, 1, 1, 1, 1},
// 							{1, 0, 0, 0, 1},
// 							{1, 0, 0, 0, 1},
// 							{2, 0, 0, 0, 2},
// 							{1, 0, 0, 0, 1},
// 							{1, 1, 1, 1, 1}};
// 	t_matrix	*world_map;
// 	size_t	i;
// 	size_t	j;

// 	world_map = mat_new(usr_map_row, usr_map_col);
// 	i = 0;
// 	while (i < usr_map_row)
// 	{
// 		j = 0;
// 		while (j < usr_map_col)
// 		{
// 			world_map->values[i][j] = usr_map[i][j];
// 			++j;
// 		}
// 		++i;
// 	}
// 	return (world_map);
// }

// //libft
// static void	*ft_calloc(size_t size)
// {
// 	void	*res;

// 	res = malloc(size);
// 	// if (res == NULL)
// 	// 	exit_with_error(MALLOC_ERR, 1);
// 	ft_bzero(res, size);
// 	return (res);
// }

// static void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*uc_s;
// 	size_t			i;

// 	uc_s = (unsigned char *)s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		uc_s[i] = 0;
// 		++i;
// 	}
// }

// static size_t	ft_max(size_t num1, size_t num2)
// {
// 	if (num1 > num2)
// 		return (num1);
// 	return (num2);
// }

// static int	ft_strcmp(const char*s1, const char *s2)
// {
// 	size_t	longer_len;

// 	longer_len = ft_max(ft_strlen(s1), ft_strlen(s2));
// 	return (ft_strncmp(s1, s2, longer_len));
// }

// static int	ft_strncmp(const char*s1, const char *s2, size_t n)
// {
// 	size_t				i;
// 	const unsigned char	*cu_s1;
// 	const unsigned char	*cu_s2;

// 	cu_s1 = (const unsigned char *)s1;
// 	cu_s2 = (const unsigned char *)s2;
// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	i = 0;
// 	while (cu_s1[i] == cu_s2[i] && i < n - 1
// 		&& !(cu_s1[i] == '\0' && cu_s2[i] == '\0'))
// 		i++;
// 	return (cu_s1[i] - cu_s2[i]);
// }

// static size_t	ft_strlen(const char *s)
// {
// 	size_t	count;

// 	count = 0;
// 	while (s[count] != '\0')
// 		count++;
// 	return (count);
// }

// static char	*ft_strrchr(const char *s, int c)
// {
// 	size_t	s_len;
// 	size_t	i;

// 	s_len = ft_strlen(s);
// 	i = 0;
// 	while (1)
// 	{
// 		if (s[s_len - i] == (const char)c)
// 			return ((char *)s + s_len - i);
// 		if (s_len - i == 0)
// 			return (NULL);
// 		i++;
// 	}
// }

// // for get next line
// static void	ft_free_s(void **ptr)
// {
// 	free(*ptr);
// 	*ptr = NULL;
// }

// static size_t	ft_strclen(const char *s, int c)
// {
// 	size_t	count;
// 	size_t	i;

// 	count = 0;
// 	i = 0;
// 	while (s[i] != '\0' && s[i] != c)
// 	{
// 		count++;
// 		i++;
// 	}
// 	return (count);
// }

// static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	i;
// 	size_t	src_len;

// 	src_len = ft_strclen(src, '\0');
// 	if (dstsize == 0)
// 		return (src_len);
// 	i = 0;
// 	while (i + 1 < dstsize && i < src_len)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (src_len);
// }

// static char	*ft_strchr(const char *s, int c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (1)
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)s + i);
// 		if (s[i] == '\0')
// 			return (NULL);
// 		i++;
// 	}
// }

// static char	*ft_strcdup(const char *s1, int c)
// {
// 	char	*s2;
// 	size_t	s1_len;

// 	if (c == '\0')
// 		s1_len = ft_strclen(s1, '\0');
// 	else
// 		s1_len = ft_strclen(s1, c) + 1;
// 	s2 = (char *)malloc(sizeof(char) * (s1_len + 1));
// 	if (s2 == NULL)
// 		return (NULL);
// 	ft_strlcpy(s2, s1, s1_len + 1);
// 	return (s2);
// }

// static char	*ft_nlseparate(char *str, char **after_newline)
// {
// 	size_t	len_before_nl;
// 	char	*before_newline;

// 	len_before_nl = ft_strclen(str, '\n') + 1;
// 	before_newline = ft_strcdup(str, '\n');
// 	*after_newline = ft_strcdup(str + len_before_nl, '\0');
// 	ft_free_s((void **)&str);
// 	if (before_newline == NULL || *after_newline == NULL)
// 	{
// 		ft_free_s((void **)&before_newline);
// 		ft_free_s((void **)after_newline);
// 		return (NULL);
// 	}
// 	return (before_newline);
// }

// static char	*ft_hstrjoin_s(char **s1, char **s2)
// {
// 	char	*joined_str;
// 	size_t	s1_len;
// 	size_t	s2_len;

// 	if (s1 == NULL || s2 == NULL || *s1 == NULL || *s2 == NULL)
// 		return (NULL);
// 	s1_len = ft_strclen(*s1, '\0');
// 	s2_len = ft_strclen(*s2, '\0');
// 	joined_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
// 	if (joined_str == NULL)
// 	{
// 		ft_free_s((void **)s1);
// 		ft_free_s((void **)s2);
// 		return (NULL);
// 	}
// 	ft_strlcpy(joined_str, *s1, s1_len + 1);
// 	ft_strlcpy(joined_str + s1_len, *s2, s2_len + 1);
// 	ft_free_s((void **)s1);
// 	ft_free_s((void **)s2);
// 	return (joined_str);
// }

// # define FD_MAX 256
// # define BUFFER_SIZE 256
// static ssize_t	ft_read(int fd, char **buf)
// {
// 	ssize_t	read_bytes;

// 	*buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
// 	if (*buf == NULL)
// 		return (-1);
// 	read_bytes = read(fd, *buf, BUFFER_SIZE);
// 	if (read_bytes < 0)
// 		return (-1);
// 	(*buf)[read_bytes] = '\0';
// 	return (read_bytes);
// }

// static char	*get_next_line(int fd)
// {
// 	char		*buf;
// 	static char	*save = NULL;
// 	ssize_t		read_bytes;

// 	if (fd < 0 || fd == STDOUT_FILENO || fd == STDERR_FILENO
// 		|| FD_MAX < fd || BUFFER_SIZE < 0)
// 		return (NULL);
// 	if (save == NULL)
// 		save = ft_strcdup("", '\0');
// 	while (save != NULL)
// 	{
// 		if (ft_strchr(save, '\n'))
// 			return (ft_nlseparate(save, &save));
// 		read_bytes = ft_read(fd, &buf);
// 		if (read_bytes < 0 || (read_bytes == 0 && ft_strclen(save, '\0') == 0))
// 		{
// 			ft_free_s((void **)&buf);
// 			ft_free_s((void **)&save);
// 			break ;
// 		}
// 		if (read_bytes < BUFFER_SIZE && !(ft_strchr(buf, '\n')))
// 			return (ft_hstrjoin_s(&save, &buf));
// 		save = ft_hstrjoin_s(&save, &buf);
// 	}
// 	return (NULL);
// }

// static	void	ft_skip_prefix(const char **str, int *base)
// {
// 	if (*base == 0 || *base == 16)
// 	{
// 		if (ft_strlen(*str) > 2)
// 		{
// 			if ((*str)[0] == '0' && ((*str)[1] == 'x' || (*str)[1] == 'X'))
// 			{
// 				*base = 16;
// 				*str += 2;
// 				return ;
// 			}
// 		}
// 		if (ft_strlen(*str) > 1)
// 		{
// 			if ((*str)[0] == '0')
// 			{
// 				*base = 8;
// 				*str += 1;
// 				return ;
// 			}
// 		}
// 		if (*base == 0)
// 			*base = 10;
// 	}
// }

// static long long	ft_convert_num(char c)
// {
// 	long long	num;

// 	num = 0;
// 	if (ft_isalpha(c))
// 	{
// 		if ('A' <= c && c <= 'Z')
// 			c += 32;
// 		num = c - 'a' + 10;
// 	}
// 	else
// 		num = c - '0';
// 	return (num);
// }

// static void	ft_set_sign(const char **str, int *sign)
// {
// 	*sign = 1;
// 	if (**str == '-' || **str == '+')
// 	{
// 		*sign = 44 - **str;
// 		(*str)++;
// 	}
// }

// static bool	ft_is_flow(long long num, long long digit)
// {
// 	return ((LLONG_MIN + digit) / 10 <= num \
// 		&& num <= (LLONG_MAX - digit) / 10);
// }

// static long long	ft_strtoll(const char *str, char **endptr, int base)
// {
// 	long long	num;
// 	long long	digit;
// 	int			sign;

// 	num = 0;
// 	while (('\t' <= *str && *str <= '\r') || *str == ' ')
// 		str++;
// 	ft_set_sign(&str, &sign);
// 	ft_skip_prefix(&str, &base);
// 	while (ft_isalnum(*str))
// 	{
// 		digit = ft_convert_num(*str);
// 		if (digit >= base)
// 			break ;
// 		if (ft_is_flow(num, digit))
// 			num = num * base + digit * sign;
// 		else if (sign == 1)
// 			return (LLONG_MAX);
// 		else
// 			return (LLONG_MIN);
// 		str++;
// 	}
// 	if (endptr != NULL)
// 		*endptr = (char *)str;
// 	return (num);
// }

// static char	*ft_shift_splitted_word(char const *s, char c)
// {
// 	while (*s != c && *s != '\0')
// 		s++;
// 	return ((char *)s);
// }

// static char	*ft_skip_split_char(char const *s, char c)
// {
// 	while (*s == c && *s != '\0')
// 		s++;
// 	return ((char *)s);
// }

// static char	**ft_split_helper(char const *s, char c, size_t split_num)
// {
// 	const char	*s_ptr;
// 	char		*split_str;
// 	char		**split_strs;

// 	s = ft_skip_split_char(s, c);
// 	if (*s == '\0')
// 	{
// 		split_strs = (char **)malloc(sizeof(char *) * (split_num + 1));
// 		if (split_strs == NULL)
// 			return (NULL);
// 		split_strs[split_num] = NULL;
// 		return (split_strs);
// 	}
// 	s_ptr = s;
// 	s = ft_shift_splitted_word(s, c);
// 	split_str = ft_substr(s_ptr, 0, s - s_ptr);
// 	if (split_str == NULL)
// 		return (NULL);
// 	split_strs = ft_split_helper(s, c, ++split_num);
// 	if (split_strs == NULL)
// 		free(split_str);
// 	else
// 		split_strs[split_num - 1] = split_str;
// 	return (split_strs);
// }

// static char	**ft_split(char const *s, char c)
// {
// 	char	**split_strs;

// 	if (s == NULL || (*s == '\0' && c == '\0'))
// 	{
// 		split_strs = (char **)malloc(sizeof(char));
// 		split_strs[0] = NULL;
// 		return (split_strs);
// 	}
// 	return (ft_split_helper(s, c, 0));
// }

// static char	*ft_strdup(const char *s1)
// {
// 	char	*s2;
// 	size_t	s1_len;

// 	s1_len = ft_strlen(s1);
// 	s2 = (char *)malloc(sizeof(char) * (s1_len + 1));
// 	if (s2 == NULL)
// 		return (NULL);
// 	ft_strlcpy(s2, s1, s1_len + 1);
// 	return (s2);
// }

// static char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*joined_str;
// 	size_t	s1_len;
// 	size_t	s2_len;

// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	joined_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
// 	if (joined_str == NULL)
// 		return (NULL);
// 	ft_strlcpy(joined_str, s1, s1_len + 1);
// 	ft_strlcpy(joined_str + s1_len, s2, s2_len + 1);
// 	return (joined_str);
// }

// static size_t	ft_min(size_t num1, size_t num2)
// {
// 	if (num1 < num2)
// 		return (num1);
// 	return (num2);
// }

// static char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*substr;
// 	size_t	s_len;
// 	size_t	substr_len;

// 	if (s == NULL)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (s_len <= start)
// 		return (ft_strdup(""));
// 	substr_len = ft_min(len, s_len - (size_t)start);
// 	substr = (char *)malloc(sizeof(char) * (substr_len + 1));
// 	if (substr == NULL)
// 		return (NULL);
// 	ft_strlcpy(substr, s + start, substr_len + 1);
// 	return (substr);
// }

// static int	ft_isalpha(int c)
// {
// 	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
// }

// static int	ft_isalnum(int c)
// {
// 	return (ft_isalpha(c) || ft_isdigit(c));
// }

// static int	ft_isdigit(int c)
// {
// 	return ('0' <= c && c <= '9');
// }
