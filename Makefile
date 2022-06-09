CC			:= gcc
CFLAGS		:= -MMD -MP -g -fsanitize=address #-Wall -Wextra -Werror
COPTS		:= -I include -I libft -L libft -l ft \
				-I minilibx-linux -L minilibx-linux \
				-I /opt/X11/include -L /usr/X11/include/../lib -l Xext -l X11 \
				-l m

# cub3d
NAME		:= cub3d
VPATH		:= src:\
				src/hooks:\
				src/parser:\
				src/render:\
				src/utils

SRCS		:= main.c
# utils
SRCS		+= handle_window.c \
				mlx_wrapper.c \
				vector.c

# For Bonus
ifdef WITH_BONUS

# Parse
SRCS		+= config_new_map.c \
				config_set_player.c \
				config_set_texture.c \
				cub_set.c \
				free_bools.c \
				free_config.c \
				free_texture.c \
				parse.c \
				parse_arg_bonus.c \
				parse_arg_color.c \
				parse_arg_map_bonus.c \
				parse_arg_utils.c \
				parse_config.c \
				parse_config_map.c \
				parse_config_sprite.c \
				parse_config_texture.c \
				parse_cub.c \
				parse_map.c \
				parse_map_utils.c \
				parse_sprite_paths_bonus.c \
				parse_types.c \
				position_generator.c \
				validate_map.c \
				validate_sprite.c \
				validate_tex_path.c
# Render
SRCS		+= cast_ray_bonus.c \
				draw_vertline.c \
				draw_wall.c \
				draw_wall2.c \
				raycastvar_set_iterator.c \
				raycastvar_set_texture.c \
				render_utils.c \
				draw_minimap_bonus.c \
				draw_sprite2_bonus.c \
				draw_sprite_bonus.c \
				draw_sprites_bonus.c \
				fill_minimap_buf_bonus.c \
				has_hit_longitudinal_door_bonus.c \
				has_hit_transverse_door_bonus.c \
				move_sprites_bonus.c \
				render_bonus.c \
				sprite_size_bonus.c \
				spritevar_set_frame_index_bonus.c \
				spritevar_set_tex_iter_bonus.c \
				spritevar_sort_bonus.c \
				update_door_state_bonus.c
# Hooks
SRCS		+= hooks_bonus.c \
				hooks_door_bonus.c \
				hooks_move.c \
				hooks_player.c \
				hooks_viewpoint_bonus.c

# Mandatory
else

# Parse
SRCS		+= config_new_map.c \
				config_set_player.c \
				config_set_texture.c \
				cub_set.c \
				free_bools.c \
				free_config.c \
				free_texture.c \
				parse.c \
				parse_arg.c \
				parse_arg_color.c \
				parse_arg_map.c \
				parse_arg_utils.c \
				parse_config.c \
				parse_config_map.c \
				parse_config_sprite.c \
				parse_config_texture.c \
				parse_cub.c \
				parse_map.c \
				parse_map_utils.c \
				parse_types.c \
				position_generator.c \
				validate_map.c \
				validate_sprite.c \
				validate_tex_path.c
# Render
SRCS		+= cast_ray.c \
				draw_vertline.c \
				draw_wall.c \
				draw_wall2.c \
				raycastvar_set_iterator.c \
				raycastvar_set_texture.c \
				render.c \
				render_utils.c
# hooks
SRCS		+= hooks.c \
				hooks_move.c \
				hooks_player.c \
				hooks_viewpoint.c

endif

OBJ_DIR		:= obj
OBJS		:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
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

ifeq ($(shell uname), Linux)
$(NAME): $(LIBFT_A) $(MLX_A) $(OBJ_DIR) $(OBJS)
	$(CC) -Wl,-start-group $(CFLAGS) $(COPTS) $(OBJS) -o $(NAME) -Wl,-end-group
else ifeq ($(shell uname), Darwin)
$(NAME): $(LIBFT_A) $(MLX_A) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(COPTS) $(OBJS) -o $(NAME)
endif

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT_A): empty
	make -C $(LIBFT_DIR)

empty:

$(MLX_A): empty
	make -C $(MLX_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I include -I minilibx-linux -I libft -I /opt/X11/include

clean:
	rm -rf $(OBJ_DIR)
	rm -f norm_info
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(MLX_A)
	make -C $(LIBFT_DIR) fclean

re:	fclean all

bonus:
	make WITH_BONUS=1

run-mandatory: all
	./cub3d settings/cub/ok_mandatory1.cub
m: run-mandatory

run-bonus:
	make bonus
	./cub3d settings/cub/ok_bonus1.cub
	# ./cub3d settings/cub/ok_bonus_order1.cub
	# ./cub3d settings/cub/ok_bonus_order2.cub
	# ./cub3d settings/cub/ok_bonus_order3.cub
	./cub3d settings/cub/ok_bonus2.cub
b : run-bonus

err:
	@chmod 000 settings/cub/error_noright.cub
	-./cub3d settings/cub/error_noright.cub
	-./cub3d settings/cub/error_walltex1.cub
	-./cub3d settings/cub/error_walltex2.cub
	-./cub3d settings/cub/error_walltex3.cub
	-./cub3d settings/cub/error_walltex4.cub
	-./cub3d settings/cub/error_walltex5.cub
	-./cub3d settings/cub/error_walltex6.cub
	-./cub3d settings/cub/error_walltex7.cub
	-./cub3d settings/cub/error_color1.cub
	-./cub3d settings/cub/error_color2.cub
	-./cub3d settings/cub/error_color3.cub
	-./cub3d settings/cub/error_color4.cub
	-./cub3d settings/cub/error_color5.cub
	-./cub3d settings/cub/error_color6.cub
	-./cub3d settings/cub/error_color7.cub
	-./cub3d settings/cub/error_color8.cub
	-./cub3d settings/cub/error_color9.cub
	-./cub3d settings/cub/error_color10.cub
	-./cub3d settings/cub/error_color11.cub
	-./cub3d settings/cub/error_color12.cub
	-./cub3d settings/cub/error_map1.cub
	-./cub3d settings/cub/error_map2.cub
	-./cub3d settings/cub/error_map3.cub
	-./cub3d settings/cub/error_map4.cub
	-./cub3d settings/cub/error_map5.cub
	-./cub3d settings/cub/error_sprite1.cub
	-./cub3d settings/cub/error_sprite2.cub
	-./cub3d settings/cub/error_sprite3.cub
	-./cub3d settings/cub/error_sprite4.cub
	@chmod 644 settings/cub/error_noright.cub

norm:
	norminette -v
	norminette libft >> norm_info
	norminette include >> norm_info
	norminette src >> norm_info

-include $(DEPS)

.PHONY: all clean fclean re libft empty
