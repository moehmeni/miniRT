# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 17:01:34 by mmomeni           #+#    #+#              #
#    Updated: 2024/03/21 20:17:01 by mmomeni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		minirt
SRC_DIR=	src
CFLAGS=		-Wall -Wextra -Werror
GLFWFLAGS=	-framework Cocoa -framework OpenGL -framework IOKit
MLXFLAGS=	-L ~/.brew/cellar/glfw/3.3.8/lib -lglfw -L ./MLX42/build -lmlx42
FUNCS=		$(SRC_DIR)/vector.c $(SRC_DIR)/intersect.c $(SRC_DIR)/parse.c $(SRC_DIR)/color.c $(SRC_DIR)/utils.c
SRCS=		$(SRC_DIR)/main.c $(FUNCS)
LIBFT_DIR=	libft
LIBFT=		$(LIBFT_DIR)/libft.a
LIBFTFLAGS=	-L$(LIBFT_DIR) -lft

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFTFLAGS) $(MLXFLAGS) $(GLFWFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

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
	norminette $(SRCS)

.PHONY: all clean fclean re bonus brew mlx
