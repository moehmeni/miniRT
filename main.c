/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:25:50 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/18 19:46:37 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

void	key_hook(mlx_key_data_t data, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (data.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
}

void terminate(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

int	main(int argc, char **argv)
{
	int			fd;
	mlx_t		*mlx;
	t_object	objs[10];
	t_scene		scene;
	char *line;

	if (argc != 2)
		terminate("Error\nInvalid number of arguments\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		terminate("Error\nInvalid file\n");
	mlx = mlx_init(512, 512, "MiniRT", 1);
	scene = (t_scene){.objects = objs};
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		parse_line(line, &scene);
		free(line);
	}
	// testing if the scene is parsed correctly
	printf("obj count: %zu\n", scene.obj_count);
	for (size_t i = 0; i < scene.obj_count; i++)
	{
		printf("obj type: %d\n", scene.objects[i].type);
	}
	return (0);
	// mlx_key_hook(mlx, key_hook, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	// return (0);
}
