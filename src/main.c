#include "cub3d.h"
#include "parse.h"

void	set_hooks(t_cub *cub);
t_error	parse(int argc, char **argv, t_cub *cub);
void	render(t_cub *cub);

int	main(int argc, char **argv)
{
	t_cub		cub;
	t_error		err;

	err = parse(argc, argv, &cub);
	if (err != NO_ERR)
	{
		fprintf(stderr, "%d\n", err);
		return (1);
	}

	render(&cub);
	set_hooks(&cub);
	mlx_loop(cub.window->mlx);
}
