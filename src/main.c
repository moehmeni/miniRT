/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:25:50 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/28 22:34:07 by mmomeni          ###   ########.fr       */
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

t_vec3	ray_dir(t_scene *scene, int x, int y)
{
	t_vec3	right;
	t_vec3	up;
	float	canvas_px[2];
	t_vec3	px_dir;

	scene->viewport.h = 2.0 * tan((scene->camera.fov * M_PI / 180.0) / 2.0);
	scene->viewport.w = scene->viewport.h * (scene->canvas.w / scene->canvas.h);
	right = vec3_norm(vec3_op(CROSS, vec3_norm(scene->camera.normal),
				(t_vec3){0.0, 1.0, 0.0}));
	up = vec3_norm(vec3_op(CROSS, right, vec3_norm(scene->camera.normal)));
	canvas_px[0] = (x + 0.5f) / scene->canvas.w * 2.0 - 1.0;
	canvas_px[1] = 1.0 - (y + 0.5f) / scene->canvas.h * 2.0;
	px_dir = vec3_op(ADD, vec3_op(ADD, vec3_mul(right, canvas_px[0]
					* scene->viewport.w / 2.0), vec3_mul(up, canvas_px[1]
					* scene->viewport.h / 2.0)),
			vec3_norm(scene->camera.normal));
	return (vec3_norm(px_dir));
}

void	render(mlx_t *mlx, t_scene *scene)
{
	size_t		i;
	size_t		j;
	mlx_image_t	*img;
	t_ray		ray;

	img = mlx_new_image(mlx, scene->canvas.w, scene->canvas.h);
	i = 0;
	scene->viewport = viewport_dim(scene->canvas, scene->camera);
	while (i < scene->canvas.w)
	{
		j = 0;
		while (j < scene->canvas.h)
		{
			ray = (t_ray){scene->camera.pos, ray_dir(scene, i, j), INFINITY};
			mlx_put_pixel(img, i, j, ray_get_color(scene, &ray));
			j++;
		}
		i++;
	}
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
		return (ft_putstr_fd("Invalid number of arguments\n", 2), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Invalid file\n", 2), 1);
	scene = (t_scene){.objects = objs, .lights = lights,
		.canvas = (t_canvas){1024, 1024}, .obj_count = 0, .light_count = 0};
	mlx = mlx_init(scene.canvas.w, scene.canvas.h, "MiniRT", 1);
	read_map(&scene, fd);
	render(mlx, &scene);
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
