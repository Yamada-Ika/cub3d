/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:29:56 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/11 00:01:01 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"
# include "mlx_color.h"

typedef struct s_config
{
	char	*no_tex_path;
	char	*so_tex_path;
	char	*we_tex_path;
	char	*ea_tex_path;
	t_list	*sprite_paths;
	size_t	sprite_num;
	int		floor_color;
	int		ceilling_color;
	char	**map;
	size_t	map_col_size;
	size_t	map_row_size;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}	t_config;

int		parse(t_config *cf, int ac, char **av);
int		parse_arg(t_config *this, int ac, char **av);
int		parse_config(t_config *cf);
bool	has_ext(const char *path, const char *ext);
int		parse_file_path(const char *path);
char	*append(char *dst, char *src);
void	set_color(t_config *this, const char *line);
size_t	count_row(char **strs);
size_t	count_col(char **strs);
bool	validate_arg_num(int ac);
void	set_map(t_config *this, char *line);
bool	is_texture_info(const char *s);
bool	is_color_info(const char *s);
bool	is_sprite_info(const char *s);
bool	start_with(const char *s, const char *head);
int		parse_map(t_config *cf);
void	set_texture_path(t_config *this, const char *line);
char	*remove_char(const char *s, const char c);
size_t	count_row(char **strs);
size_t	count_col(char **strs);
size_t	next_nonspace(const char *s);
void	set_sprite(t_config *this, const char *line);
int		parse_player_info(t_config *cf);
void	debug_config(t_config *this);
void	debug_game(t_game *g);
void	print_progress(const char *act);

#endif
