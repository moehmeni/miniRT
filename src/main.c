/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:25:50 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/21 20:23:49 by mmomeni          ###   ########.fr       */
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

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_line(line, scene);
		free(line);
	}
}

void	render(mlx_t *mlx, t_scene scene)
{
	size_t		i;
	size_t		j;
	mlx_image_t	*img;
	t_ray		ray;

	img = mlx_new_image(mlx, scene.viewport.w, scene.viewport.h);
	i = 0;
	while (i < scene.viewport.w)
	{
		j = 0;
		while (j < scene.viewport.h)
		{
			ray = (t_ray){scene.camera.pos, (t_vec3){i, j, 0}, INFINITY};
			ray.dir = vec3_norm(vec3_op(SUB, ray.dir, scene.camera.pos));
			mlx_put_pixel(img, i, j, ray_get_color(&scene, &ray));
			j++;
		}
		i++;
	}
	printf("Rendering done\n");
	mlx_image_to_window(mlx, img, 0, 0);
}

int	main(int argc, char **argv)
{
	int			fd;
	mlx_t		*mlx;
	t_object	objs[10];
	t_light		lights[3];
	t_scene		scene;

	if (argc != 2)
		terminate("Error\nInvalid number of arguments\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		terminate("Error\nInvalid file\n");
	scene = (t_scene){.objects = objs, .lights = lights,
		.viewport = (t_viewport){512, 512}, .obj_count = 0, .light_count = 0};
	mlx = mlx_init(scene.viewport.w, scene.viewport.h, "MiniRT", 1);
	read_map(&scene, fd);
	render(mlx, scene);
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}