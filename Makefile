# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 19:00:52 by nkuchyna          #+#    #+#              #
#    Updated: 2018/05/15 12:06:14 by nkuchyna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	fdf
CCLIB = libft/libft.a
CCMLX = -L  /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
CCFLAGC = -Wall -Wextra -Werror
SRCDIR = src
OBJDIR = obj
INCDIR = includes libft

SRC  = 	fdf.c \
		ft_key_action.c \
		ft_map_processing.c \
		ft_check_content_and_create_s_array.c \
		ft_strsplit_new.c \
		ft_fill_s_array.c \
		ft_transform_image.c \
		ft_build_lines.c \
		ft_fill_img_str.c \
		ft_change_color_adv.c \
		additional_functions.c
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS  = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCS  =  $(addprefix -I, $(INCDIR))

all: $(NAME)

$(NAME): build $(OBJS)
		make -C libft/
		gcc $(CCLIB) $(CCMLX) -o $(NAME) $(OBJS)

build:
		mkdir -p $(OBJDIR)

clean:
		rm -f $(OBJS)
		make clean -C libft

fclean: clean
		rm -f $(NAME)
		make fclean -C libft

re: fclean all

$(OBJDIR)/%.o : $(SRCDIR)/%.c
				gcc -c $(CCFLAGS) $(INCS) -o $@ $< 

.PHONY: clean fclean make re
