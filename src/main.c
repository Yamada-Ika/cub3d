#include "cub3d.h"

t_error	parse(int argc, char **argv, t_cub *cub);
void	render(t_cub *cub);
void	install_event_hooks(t_cub *cub);
void	loop(t_cub *cub);

void	run(t_cub *cub)
{
	render(cub);
	install_event_hooks(cub);
	loop(cub);
}

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
	run(&cub);
}
