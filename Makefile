NAME	:=	cub3d
CC		:=	gcc
CFLAGS	:=	-MMD -MP

ifdef WITH_DEBUG
	CFLAGS += -fno-optimize-sibling-calls -fsanitize=address -g -fsanitize-address-use-after-return=runtime
endif

OBJ_DIR	:= ./objs
VPATH	:=	srcs:\
			srcs/utils:\
			srcs/parse:\
			srcs/minimap:\
			srcs/render:\
			srcs/hooks/
SRCS	:=	main.c \
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
# parser
SRCS	+= destroy_config.c parse_arg2.c\
init_game.c      parse_config.c\
parse.c          utils.c\
parse_arg.c
OBJS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS	:= $(OBJS:.o=.d)
LIBMAT_DIR := ./libmat
LIBMAT := libmat.a
LIBFT_DIR := ./libft
LIBFT := libft.a

MLX_DIR		:= ./minilibx-linux
ifeq ($(shell uname), Linux)
	MLX	:= libmlx_Linux.a
	WITH_MLX	:= $(MLX_DIR)/$(MLX) -L $(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(shell uname), Darwin)
	MLX	:= libmlx_Darwin.a
	WITH_MLX	:= $(MLX_DIR)/$(MLX) -L $(MLX_DIR) -L/usr/X11/include/../lib -lmlx -lXext -lX11 -lm
endif

# WITH_MLX	:= $(MLX_DIR)/$(MLX) -L $(MLX_DIR) -L/usr/X11/include/../lib -lmlx -lXext -lX11 -lm
INCLUDE :=	-I ./includes -I $(LIBMAT_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR)

$(NAME): $(OBJ_DIR) $(OBJS)
	make affine -C $(LIBMAT_DIR)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBMAT_DIR)/$(LIBMAT) $(LIBFT_DIR)/$(LIBFT) $(WITH_MLX) -o $@ $(INCLUDE)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJ_DIR):
	mkdir -p $@

all: $(NAME)

clean:
	make clean -C $(LIBMAT_DIR)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean:		clean
	rm -f $(NAME)
	rm -f $(LIBMAT_DIR)/$(LIBMAT)
	rm -f $(MLX_DIR)/$(MLX)
	rm -f $(LIBFT_DIR)/$(LIBFT)

re:			fclean all

test:
	./cub3d ./map/sample.cub

debug:	fclean
	make WITH_DEBUG=1
	make test

-include $(DEPS)

.PHONY:     all clean fclean re
