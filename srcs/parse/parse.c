#include "cub3d.h"

int	parse_arg(t_config *this, int ac, char **av);
int	parse_config(t_config *cf);

int parse(t_config *cf, int ac, char **av)
{
	t_error	err;

	err = parse_arg(cf, ac, av);
	if (err != NO_ERR) // configに色々セット
		return (err);
	err = parse_config(cf);
	if (err != NO_ERR) // configをパース
		return (err);
	return (NO_ERR);
}
