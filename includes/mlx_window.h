/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:08:51 by kkaneko           #+#    #+#             */
/*   Updated: 2022/04/03 17:17:21 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_WINDOW_H
# define MLX_WINDOW_H
# define ESC 65307
# define L_ARROW 65361
# define U_ARROW 65362
# define R_ARROW 65363
# define D_ARROW 65364
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define CLICK_L 1
# define CLICK_R 2
# define CLICK_M 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define EV_CROSS_BUTTON 17

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_window
{
	int		width;
	int		height;
	void	*mlx;
	void	*mlx_win;
	t_img	*img_front;
	t_img	*img_back;
}	t_window;

void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_window	*init_window(int width, int height, char *title);
t_img		*init_img(t_window *window);

#endif
