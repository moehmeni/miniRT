# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 17:01:34 by mmomeni           #+#    #+#              #
#    Updated: 2024/03/01 13:54:20 by mmomeni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		miniRT
CFLAGS=		-Wall -Wextra -Werror
GLFWFLAGS=	-framework Cocoa -framework OpenGL -framework IOKit
MLXFLAGS=	-L ~/.brew/cellar/glfw/3.3.8/lib -lglfw -L ./MLX42/build -lmlx42
FUNCS=		render.c utils.c parse.c transform.c line.c
SRCS=		main.c $(FUNCS)
LIBFT_DIR=	libft
LIBFT=		$(LIBFT_DIR)/libft.a
LIBFTFLAGS=	-L$(LIBFT_DIR) -lft

all: bonus

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFTFLAGS) $(MLXFLAGS) $(GLFWFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(RM) $(BONUS_DIR)/$(BONUS_NAME)

re: fclean all

brew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

mlx:
	cd MLX42;\
	cmake -B build;\
	make -C build -j4;\

debug: CFLAGS += -fsanitize=address -g
debug: all bonus

norm:
	norminette *.c bonus libft

.PHONY: all clean fclean re bonus brew mlx
