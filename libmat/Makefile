# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 21:29:02 by kkaneko           #+#    #+#              #
#    Updated: 2022/04/02 03:36:47 by kkaneko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libmat.a
SRCS_NORMAL	:=	mat_puterror.c \
				mat_free.c \
				mat_new.c \
				mat_add_new.c \
				mat_add.c \
				mat_mul_scalar_new.c \
				mat_mul_scalar.c \
				mat_mul_new.c \
				mat_mul.c \
				mat_identity.c \
				mat_dup.c #\
				mat_transpose.c \
				mat_submat.c \
				mat_det.c \
				mat_inv.c \
				mat_inner.c
SRCS_AFFINE :=	mat_affine_new.c \
				mat_affine_free.c \
				mat_rotation_x.c \
				mat_rotation_y.c \
				mat_rotation_z.c \
				mat_rotation_any.c \
				mat_translation_3d.c \
				mat_translation_2d.c \
				mat_translation_2d_new.c \
				mat_zoom_3d.c \
				mat_zoom_2d_new.c \
				mat_zoom_2d.c \
				mat_vector_col_3d.c \
				mat_vector_row_3d.c \
				mat_vector_col_2d.c \
				mat_vector_row_2d.c \
				mat_l2norm.c \
				mat_rotation_2d_new.c \
				mat_rotation_2d.c \
				mat_distance_2d.c
SRCS_DEBUG	:=	mat_print.c
SRCS	:= $(SRCS_NORMAL)
SRC_DIR	:= ./srcs
VPATH	:= $(SRC_DIR)
OBJ_DIR	:= ./objs
OBJS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS	:= $(OBJS:.o=.d)
INC_DIR	:= ./
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP

ifdef WITH_AFFINE
	OBJS += $(addprefix $(OBJ_DIR)/, $(SRCS_AFFINE:.c=.o))
	CFALGS += -lm
endif

ifdef WITH_DEBUG
	OBJS += $(addprefix $(OBJ_DIR)/, $(SRCS_DEBUG:.c=.o))
endif

$(NAME): $(OBJ_DIR) $(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

all:
	make WITH_AFFINE=1 WITH_DEBUG=1

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

affine:
	make WITH_AFFINE=1

debug:
	make WITH_DEBUG=1

-include: $(DEPS)

.PHONY: all clean fclean re affine debug
