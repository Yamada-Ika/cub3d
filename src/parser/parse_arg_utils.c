#include "parse.h"

char	*skip_spaces(char *s)
{
	while (*s != '\0' && *s == ' ')
		s++;
	return (s);
}

bool	is_texture_symbol(const char *s)
{
	return (
		ft_strncmp(s, "NO", 2) == 0
		|| ft_strncmp(s, "SO", 2) == 0
		|| ft_strncmp(s, "WE", 2) == 0
		|| ft_strncmp(s, "EA", 2) == 0
	);
}

bool	is_color_symbol(const char *s)
{
	return (
		ft_strncmp(s, "F", 1) == 0
		|| ft_strncmp(s, "C", 1) == 0
	);
}

bool	is_sprite_symbol(const char *s)
{
	return (
		ft_strncmp(s, "SP ", 3) == 0
	);
}
