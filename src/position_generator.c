#include "cub3d.h"

#define A 48271
#define B 0
#define M INT_MAX

static long long g_seed;

long long	mytime(void)
{
	long long res;
	char	*end;
	static long long cnt = 0;

	res = ft_strtoll(__TIME__, &end, 10);
	end++;
	res += ft_strtoll(end, &end, 10);
	end++;
	res += ft_strtoll(end, &end, 10);
	cnt++;
	return (res * cnt);
}

static double	random_generator(void)
{
	g_seed = (A * g_seed + B) % M;
	return (double)(g_seed+1.0)/(M+1.0);
}

void	sprite_position_generator(t_cub *cub, double *x, double *y)
{
	g_seed = mytime();
	while (true)
	{
		double	cand_x = random_generator() * (cub->map->heigth - 1);
		double	cand_y = random_generator() * (cub->map->width - 1);
		if (cub->map->map[(int)cand_x][(int)cand_y] != 0)
			continue ;
		*x = cand_x;
		*y = cand_y;
		break ;
	}
}

