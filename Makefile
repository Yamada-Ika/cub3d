CC			:= gcc
CFLAGS		:= -MMD -MP -g -fsanitize=address #-Wall -Wextra -Werror
COPTS		:= -I include -I libft -L libft -l ft \
				-I minilibx-linux -L minilibx-linux \
				-I /opt/X11/include -L /usr/X11/include/../lib -l Xext -l X11 \
				-l m

# cub3d
NAME		:= cub3d
VPATH		:= src:\
				src/parser:\
				src/render:\
				src/utils
SRCS		:= render.c\
draw_wall3.c\
minimap.c\
draw_sprite.c\
draw_wall2.c\
draw_wall.c\
vector.c\
position_generator.c\
parse_arg_map.c\
parse_arg_utils.c\
parse_arg.c\
parse_arg_color.c\
parse_arg_texture.c\
parse_arg_load_cub.c\
parse_config.c\
parse.c\
main.c\
handle_window.c\
hooks.c\
mlx_wrapper.c
OBJS		:= $(addprefix obj/, $(SRCS:.c=.o))
DEPS		:= $(OBJS:.o=.d)

# minilib
MLX_DIR		:= minilibx-linux
ifeq ($(shell uname), Linux)
	MLX_A	:= libmlx_Linux.a
	COPTS	+= -lmlx_Linux
else ifeq ($(shell uname), Darwin)
	MLX_A	:= libmlx_Darwin.a
	COPTS	+= -lmlx_Darwin
endif
MLX_A	:= $(addprefix $(MLX_DIR)/, $(MLX_A))

# libft
LIBFT_DIR	:= libft
LIBFT_A		:= libft.a
LIBFT_A		:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_A))

all: $(NAME)

ifeq ($(shell uname), Linux)
$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	$(CC) -Wl,-start-group $(CFLAGS) $(COPTS) $(OBJS) -o $(NAME) -Wl,-end-group
else ifeq ($(shell uname), Darwin)
$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(COPTS) $(OBJS) -o $(NAME)
endif

$(LIBFT_A): empty
	make -C $(LIBFT_DIR)

empty:

$(MLX_A): empty
	make -C $(MLX_DIR)

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I include -I minilibx-linux -I libft -I /opt/X11/include

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re:	fclean all

run: all
	./cub3d image/tutorial.cub

err: all
	./cub3d image/error_noright.cub
	./cub3d image/error_walltex1.cub
	./cub3d image/error_walltex2.cub
	./cub3d image/error_walltex3.cub
	./cub3d image/error_walltex4.cub

-include $(DEPS)

.PHONY: all clean fclean re libft empty
