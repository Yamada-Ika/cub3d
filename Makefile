CC			:= gcc
CFLAGS		:= -MMD -MP -g -fsanitize=address #-Wall -Wextra -Werror
COPTS		:= -I include -I libft -L libft -l ft \
				-I minilibx-linux -L minilibx-linux \
				-I /opt/X11/include -L /usr/X11/include/../lib -l Xext -l X11 \
				-l m

# libft
LIBFT_DIR	:= libft
LIBFT_A		:= libft.a
LIBFT_A		:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_A))

# cub3d
NAME		:= cub3d
SRCS		:= handle_window.c      mlx_wrapper.c\
hooks.c              parse.c\
main.c               position_generator.c\
minimap.c
OBJS		:= $(SRCS:%.c=%.o)
SRCS		:= $(addprefix src/, $(SRCS))
OBJS		:= $(addprefix obj/, $(OBJS))

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

obj/%.o: src/%.c
	# $(CC) $(CFLAGS) -o $@ -c $^ -Iinclude -Iminilibx-linux -Ilibft
	$(CC) $(CFLAGS) -o $@ -c $^ $(COPTS)

$(MLX_A): empty
	make -C $(MLX_DIR)

clean:
	rm -rf obj/*.o
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re:	fclean all

run: all
	./cub3d image/tutorial.cub

texture:
	gcc test/texture.c $(COPTS) -o test_texture && ./test_texture
	rm -rf test_texture

circle:
	gcc test/circle.c $(COPTS) -o test_circle && ./test_circle
	rm -rf test_circle

.PHONY: all clean fclean re libft empty
