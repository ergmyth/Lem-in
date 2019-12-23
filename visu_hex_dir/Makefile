#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 10:33:18 by eklompus          #+#    #+#              #
#    Updated: 2019/11/16 10:33:22 by eklompus         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = visu_hex

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror

ALL_C =	vis_lemin.c \
		print_error.c \
		init_sdl.c \
		load_image.c \
		load_font.c \
		read_file.c \
		rooms_parse.c \
		links_parse.c \
		line_parse.c \
		check_all.c \
		process_events.c \
		draw_elems.c \
		init_timers.c \
		calc_sizes.c \
		destroy.c \
		draw_all.c \
		get_dims.c \
		moves.c \
		draw_roomants.c

SRCDIR = ./srcs
OBJDIR = ./objs

ALL_OBJ = $(ALL_C:%.c=%.o)

OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

INC_DIR =	./includes \
			./../libft/includes \
			./../ft_printf/includes

INC_FLAG = $(addprefix -I,$(INC_DIR)) `sdl2-config --cflags`

LIB_DIR =	./../libft \
			./../ft_printf \

LIB_DIR_FLAG = $(addprefix -L,$(LIB_DIR))

LIBS = 		ft \
			SDL2 \
			SDL2_image \
			SDL2_ttf \
			SDL2_gfx \
			m \
			ftprintf

LIBS_FLAG = $(addprefix -l,$(LIBS)) `sdl2-config --libs`

HEADERS = ./includes/vis_lemin.h

COMP_LIB = make -C ./../libft
COMP_PRINTF = make -C ./../ft_printf


all: $(NAME)

lib:
	$(COMP_LIB)

ft_printf:
	$(COMP_PRINTF)

$(NAME): ./../libft/libft.a ./../ft_printf/libftprintf.a $(OBJS)
	$(CC) $(CC_FLAGS) $^ $(LIB_DIR_FLAG) $(LIBS_FLAG) -o $@

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CC_FLAGS) $(INC_FLAG) -c $< -o $@

./../ft_printf/libftprintf.a: ft_printf

./../libft/libft.a: lib

clean:
	$(COMP_LIB) clean
	$(COMP_PRINTF) clean
	rm -rf $(OBJDIR)

fclean: clean
	$(COMP_LIB) fclean
	$(COMP_PRINTF) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: lib ft_printf clean fclean all re
