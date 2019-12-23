ALL_C =	lemin.c \
        		read_input.c \
        		rooms_parse.c \
        		line_parse.c \
        		links_parse.c \
        		print.c \
        		check_all.c \
        		graph_create.c \
        		calc_total_len.c \
        		paths_work.c \
        		find_all_paths.c \
        		dijkstra_algo.c \
        		destroy.c \
        		ants_walk.c \
        		print_given_data.c \
        		suurballe.c \
        		neigs_work.c \
        		bellman_ford.c \
        		recalc_paths.c

SRCDIR = ./srcs
OBJDIR = ./objs

ALL_OBJ = $(ALL_C:%.c=%.o)

OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

NAME = lem-in
VIS_NAME = visu_hex
VIS_DIR = visu_hex_dir

INCLUDES = ./includes/lemin.h \
			./includes/ants_walk.h

COMP_LIB = make -C libft
COMP_PRINTF = make -C ft_printf
COMP_VISU_HEX = make -C $(VIS_DIR)

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(VIS_NAME)

$(VIS_NAME): comp_visu_hex
	cp $(VIS_DIR)/$(VIS_NAME) $(VIS_NAME)

$(NAME): ./libft/libft.a ./ft_printf/libftprintf.a $(OBJS)
	gcc $(FLAGS) $(OBJS) -L./libft -lft -L./ft_printf -lftprintf -o $@

$(OBJDIR):
	/bin/mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES) | $(OBJDIR)
	gcc $(FLAGS) -I./includes -I./libft/includes -I./ft_printf/includes -c $< -o $@

./ft_printf/libftprintf.a: ft_printf

./libft/libft.a: lib

comp_visu_hex:
	$(COMP_VISU_HEX)

lib:
	@$(COMP_LIB)

ft_printf:
	@$(COMP_PRINTF)

clean:
	@/bin/rm -rf $(OBJDIR)
	@$(COMP_LIB) clean
	@$(COMP_PRINTF) clean
	@$(COMP_VISU_HEX) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@/bin/rm -rf $(VIS_NAME)
	@$(COMP_LIB) fclean
	@$(COMP_PRINTF) fclean
	@$(COMP_VISU_HEX) fclean

re: fclean all

.PHONY: visu_hex lib ft_printf clean fclean all re
