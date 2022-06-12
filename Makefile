CC			:= gcc
CFLAGS		:= -MMD -MP  -Wall -Wextra -Werror
COPTS		:= -I include -I libft -L libft -l ft \
				-I minilibx-linux -L minilibx-linux \
				-I /opt/X11/include -L /usr/X11/include/../lib -l Xext -l X11 \
				-l m
NAME		:= cub3d
VPATH		:= src:\
				src/hooks:\
				src/parser:\
				src/render:\
				src/utils

# Common Source
SRCS		:= main.c
# Parse Common Source
SRCS		+= config_new_map_common.c \
				config_set_map_common.c \
				config_set_player_common.c \
				config_set_texture_common.c \
				cub_set_common.c \
				cub_set_wall_tex_common.c \
				free_bools_common.c \
				free_texture_common.c \
				parse_arg_color_common.c \
				parse_arg_cub_common.c \
				parse_arg_map_common.c \
				parse_arg_types_common.c \
				parse_arg_utils_common.c \
				parse_common.c \
				validate_map_common.c \
				validate_tex_path_common.c
# Render Common Source
SRCS		+= cast_ray_common.c \
				draw_vertline_common.c \
				draw_walls_common.c \
				raycastvar_set_iterator_common.c \
				raycastvar_set_texture_common.c \
				render_utils_common.c
# Hooks Common Source
SRCS		+= hooks_move_common.c \
				hooks_player_common.c \
				hooks_viewpoint_common.c
# Utils Common Source
SRCS		+= handle_window_common.c \
				mlx_wrapper_common.c \
				vector_common.c

# For Bonus
ifdef WITH_BONUS

# Parse Bonus Source
SRCS		+= config_set_map_bonus.c \
				cub_set_bonus.c \
				cub_set_sprite_bonus.c \
				cub_set_sprite2_bonus.c \
				free_config_bonus.c \
				parse_arg_bonus.c \
				parse_arg_utils_bonus.c \
				parse_arg_sprite_bonus.c \
				parse_config_bonus.c \
				position_generator_bonus.c \
				validate_sprite_bonus.c
# Render Bonus Source
SRCS		+= cast_ray_bonus.c \
				draw_minimap_bonus.c \
				draw_sprite2_bonus.c \
				draw_sprite_bonus.c \
				draw_sprites_bonus.c \
				draw_walls_bonus.c \
				fill_minimap_buf_bonus.c \
				has_hit_longitudinal_door_bonus.c \
				has_hit_transverse_door_bonus.c \
				move_sprites_bonus.c \
				render_bonus.c \
				render_utils_bonus.c \
				sprite_size_bonus.c \
				spritevar_set_frame_index_bonus.c \
				spritevar_set_tex_iter_bonus.c \
				spritevar_sort_bonus.c \
				update_door_state_bonus.c
# Hooks Bonus Source
SRCS		+= hooks_bonus.c \
				hooks2_bonus.c \
				hooks_door_bonus.c \
				hooks_viewpoint_bonus.c \
				hooks_mouse_bonus.c

# Mandatory
else

# Parse Mandatory Source
SRCS		+= config_set_map.c \
				free_config.c \
				parse_arg.c \
				parse_config.c
# Render Mandatory Source
SRCS		+= cast_ray.c \
				draw_walls.c \
				render.c \
# Hooks Mandatory Source
SRCS		+= hooks.c \
				hooks_viewpoint.c

endif

OBJ_DIR		:= obj
OBJS		:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(OBJS:.o=.d)

# For Cross Platform Compilation
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
	./cub3d settings/cub/ok_bonus_order1.cub
	./cub3d settings/cub/ok_bonus_order2.cub
	./cub3d settings/cub/ok_bonus_order3.cub
	./cub3d settings/cub/ok_bonus2.cub
b : run-bonus

err:
	@chmod 000 settings/cub/error_noright.cub
	@chmod 222 settings/cub/error_norright.cub
	-./cub3d settings/cub/error_noright.cub
	-./cub3d settings/cub/error_norright.cub
	-./cub3d settings/cub/error_walltex1.cub
	-./cub3d settings/cub/error_walltex2.cub
	-./cub3d settings/cub/error_walltex3.cub
	-./cub3d settings/cub/error_walltex4.cub
	-./cub3d settings/cub/error_walltex5.cub
	-./cub3d settings/cub/error_walltex6.cub
	-./cub3d settings/cub/error_walltex7.cub
	-./cub3d settings/cub/error_walltex8.cub
	-./cub3d settings/cub/error_walltex9.cub
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
	-./cub3d settings/cub/error_map6.cub
	-./cub3d settings/cub/error_sprite1.cub
	-./cub3d settings/cub/error_sprite2.cub
	-./cub3d settings/cub/error_sprite3.cub
	-./cub3d settings/cub/error_sprite4.cub
	@chmod 644 settings/cub/error_noright.cub
	@chmod 644 settings/cub/error_norright.cub

norm:
	norminette -v
	norminette libft
	norminette include
	norminette src
	@echo "Norm OK!"

func:
	bash find_forbidden_func.sh

help:
	@echo "  Discription: rule"
	@echo "    bonus:"
	@echo "      build with bonus sources"
	@echo "    run-mandatory:"
	@echo "      build with mandatory sources and run with correct cub file"
	@echo "    m:"
	@echo "      Abbreviation of [run-mandatory]"
	@echo "    run-bonus:"
	@echo "      build with bonus sources and run with correct cub file"
	@echo "    b:"
	@echo "      Abbreviation of [run-bonus]"
	@echo "    err:"
	@echo "      run with wrong cub files"
	@echo "    norm:"
	@echo "      run norminette except for minilibx"
	@echo "    func:"
	@echo "      run checking fobidden functions script"
h: help

-include $(DEPS)

.PHONY: all clean fclean re libft empty
