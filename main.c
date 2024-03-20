/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:25:50 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/20 19:27:39 by mmomeni          ###   ########.fr       */
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

void	terminate(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	read_map(t_scene *scene, int fd)
{
	char	*line;
	size_t	i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_line(line, scene, i++);
		free(line);
	}
	scene->obj_count = i;
}

void	render(mlx_t *mlx, t_scene scene)
{
	size_t		i;
	size_t		j;
	mlx_image_t	*img;
	t_ray		ray;

	img = mlx_new_image(mlx, 512, 512);
	i = 0;
	while (i++ < 512)
	{
		j = 0;
		while (j < 512)
		{
			ray = (t_ray){
				.origin = scene.camera,
			};
			mlx_put_pixel(img, i, j++, color);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	mlx_t		*mlx;
	t_object	objs[10];
	t_scene		scene;

	if (argc != 2)
		terminate("Error\nInvalid number of arguments\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		terminate("Error\nInvalid file\n");
	mlx = mlx_init(512, 512, "MiniRT", 1);
	scene = (t_scene){.objects = objs};
	read_map(&scene, fd);
	render(mlx, scene);
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
