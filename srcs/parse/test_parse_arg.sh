#!/bin/bash

res=$(cat << EOF
NO ./map/test.xpm
SO ./map/test.xpm
WE ./map/test.xpm
EA ./map/test.xpm

F 220,100,0
C 225,30,0

11111
10002
10001
20001
10001
11111

EOF
)
echo "$res" > test1.cub

MAIN=$(cat << EOF

#include <assert.h>
#include <string.h>
#include "cub3d.h"

bool	has_ext(const char *path, const char *ext);
int		parse_file_path(const char *path);
int 	str_to_rgb(const char *s);
char	*append(char *dst, char *src);
void	set_color(t_config *this, const char *line);
bool	validate_arg_num(int ac);
char	*remove_char(const char *s, const char c);
void	set_texture_path(t_config *this, const char *line);
int	init_config(t_config *this, const char *file);
int	parse_arg(t_config *this, int ac, char **av);

int main(void)
{
	printf("has_ext test start!\n");
	assert(has_ext("hoge.cub", "cub") == true);
	assert(has_ext("hoge.c", "cub") == false);
	assert(has_ext("hoge.cu", "cub") == false);
	assert(has_ext("cub.cub", "cub") == true);
	assert(has_ext("cub.cubcub", "cub") == false);
	assert(has_ext(".cub", "cub") == true);
	printf("has_ext test ok!\n");

	printf("append test start!\n");
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	tmp1 = ft_strdup("hoge");
	tmp2 = ft_strdup("fuga");
	tmp3 = append(tmp1, tmp2);
	assert(strcmp(tmp3, "hogefuga") == 0);
	printf("append test ok!\n");

	printf("str_to_rgb test start!\n");
	assert(str_to_rgb("0,0,0") == 0);
	assert(str_to_rgb("255,255,255") == 0xffffff);
	assert(str_to_rgb("255,215,0") == 0xffd700);
	assert(str_to_rgb("0,128,0") == 0x008000);
	printf("str_to_rgb test ok!\n");

	printf("parse_file_path test start!\n");
	assert(parse_file_path("hoge") == FAIL);
	assert(parse_file_path("hoge.cub") == SUCCESS);
	printf("parse_file_path test ok!\n");

	printf("init_config test start!\n");
	t_config cf;
	assert(init_config(&cf, "./test1.cub") == SUCCESS);
	assert(strcmp(cf.no_tex_path, "./path_to_the_north_texture"));
	assert(strcmp(cf.so_tex_path, "./path_to_the_south_texture"));
	assert(strcmp(cf.we_tex_path, "./path_to_the_west_texture"));
	assert(strcmp(cf.ea_tex_path, "./path_to_the_east_texture"));
	assert(cf.floor_color == 0xdc6400);
	assert(cf.ceilling_color == 0xe11e00);
	assert(cf.map[0][0] == '1');
	assert(cf.map[0][1] == '1');
	assert(cf.map[0][2] == '1');
	assert(cf.map[0][3] == '1');
	assert(cf.map[0][4] == '1');
	assert(cf.map[1][0] == '1');
	assert(cf.map[1][1] == '0');
	assert(cf.map[1][2] == '0');
	assert(cf.map[1][3] == '0');
	assert(cf.map[1][4] == '2');
	assert(cf.map[2][0] == '1');
	assert(cf.map[2][1] == '0');
	assert(cf.map[2][2] == '0');
	assert(cf.map[2][3] == '0');
	assert(cf.map[2][4] == '1');
	assert(cf.map[3][0] == '2');
	assert(cf.map[3][1] == '0');
	assert(cf.map[3][2] == '0');
	assert(cf.map[3][3] == '0');
	assert(cf.map[3][4] == '1');
	assert(cf.map[4][0] == '1');
	assert(cf.map[4][1] == '0');
	assert(cf.map[4][2] == '0');
	assert(cf.map[4][3] == '0');
	assert(cf.map[4][4] == '1');
	assert(cf.map[5][0] == '1');
	assert(cf.map[5][1] == '1');
	assert(cf.map[5][2] == '1');
	assert(cf.map[5][3] == '1');
	assert(cf.map[5][4] == '1');
	printf("init_config test end!\n");
}
EOF
)

echo "$MAIN" > main.c

gcc main.c parse_arg.c parse_arg2.c -I ../../includes  -I ../../libmat -I ../../minilibx-linux -L ../../libmat -l mat -I ../../libft -L ../../libft -l ft  && ./a.out

rm a.out test1.cub main.c
