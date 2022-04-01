NAME	:=	cub3d
CC		:=	gcc
CFLAGS	:=	-MMD -MP -fsanitize=address -pg
OBJ_DIR	:= ./objs
VPATH	:=	srcs:\
			srcs/utils:\
			srcs/parse:\
			srcs/minimap:\
			srcs/render:\
			srcs/hooks/
SRCS	:=	main.c \
			parse_map.c \
			cub_test_2.c \
			hooks.c \
			handle_window.c \
			handle_color.c \
			render_minimap.c \
			spawn.c \
			clear_window.c \
			exit_with_error.c \
			handle_perspective.c \
			handle_movement.c
OBJS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS	:= $(OBJS:.o=.d)
LIBMAT_DIR := ./libmat
LIBMAT := libmat.a

MLX_DIR		:= ./minilibx-linux
ifeq ($(shell uname), Linux)
	MLX	:= libmlx_Linux.a
	WITH_MLX	:= $(MLX_DIR)/$(MLX) -L $(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(shell uname), Darwin)
	MLX	:= libmlx_Darwin.a
	WITH_MLX	:= $(MLX_DIR)/$(MLX) -L $(MLX_DIR) -L/usr/X11/include/../lib -lmlx -lXext -lX11 -lm
endif

# WITH_MLX	:= $(MLX_DIR)/$(MLX) -L $(MLX_DIR) -L/usr/X11/include/../lib -lmlx -lXext -lX11 -lm
INCLUDE :=	-I ./includes -I $(LIBMAT_DIR) -I $(MLX_DIR)

$(NAME): $(OBJ_DIR) $(OBJS)
	make affine -C $(LIBMAT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBMAT_DIR)/$(LIBMAT) $(WITH_MLX) -o $@ $(INCLUDE)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJ_DIR):
	mkdir -p $@

all: $(NAME)

clean:
	make clean -C $(LIBMAT_DIR)
	make clean -C $(MLX_DIR)
	rm -rf $(OBJ_DIR)

fclean:		clean
	rm -f $(NAME)
	rm -f $(LIBMAT_DIR)/$(LIBMAT)
	rm -f $(MLX_DIR)/$(MLX)

re:			fclean all

-include $(DEPS)

.PHONY:     all clean fclean re
