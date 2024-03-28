/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:25:50 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/28 12:30:41 by htaheri          ###   ########.fr       */
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

float deg_to_rad(float degrees) {
	return degrees * M_PI / 180.0;
}

// Calculate direction vector from camera to a point on the viewport
t_vec3 calculate_ray_direction(t_camera cam, int viewport_width, int viewport_height, int x, int y) {
    float aspect_ratio = viewport_width / (float)viewport_height;
    float fov_rad = deg_to_rad(cam.fov);
    float viewport_height_world = 2.0 * tan(fov_rad / 2.0); // Height in world units
    float viewport_width_world = viewport_height_world * aspect_ratio; // Width in world units

    // Camera basis vectors
    t_vec3 forward = vec3_norm(cam.normal); // Camera's looking direction
    t_vec3 world_up = {0.0, 1.0, 0.0}; // World's up direction
    t_vec3 right = vec3_norm(vec3_op(CROSS, forward, world_up)); // Perpendicular to forward and up
    t_vec3 up = vec3_norm(vec3_op(CROSS, right, forward)); // Perpendicular to right and forward (re-cross to ensure orthogonality)

    // Convert pixel position (x, y) to NDC (Normalized Device Coordinates)
    float pixel_NDC_x = (x + 0.5f) / viewport_width * 2.0 - 1.0;
    float pixel_NDC_y = 1.0 - (y + 0.5f) / viewport_height * 2.0; // Flip y-axis

    // Convert NDC to world space
    float pixel_world_x = pixel_NDC_x * viewport_width_world / 2.0;
    float pixel_world_y = pixel_NDC_y * viewport_height_world / 2.0;

    // Calculate the direction vector for this pixel
    t_vec3 pixel_direction = vec3_op(ADD, vec3_op(ADD, vec3_mul(right, pixel_world_x), vec3_mul(up, pixel_world_y)), forward);
    return vec3_norm(pixel_direction);
}


void	render(mlx_t *mlx, t_scene scene)
{
	size_t		i;
	size_t		j;
	mlx_image_t	*img;
	t_ray		ray;

	img = mlx_new_image(mlx, scene.canvas.w, scene.canvas.h);
	i = 0;
	scene.viewport = viewport_dim(scene.canvas, scene.camera);
	while (i < scene.canvas.w)
	{
		j = 0;
		while (j < scene.canvas.h)
		{
			ray = (t_ray){scene.camera.pos, calculate_ray_direction(scene.camera, scene.canvas.w, scene.canvas.h, i, j), INFINITY};
			// ray = (t_ray){scene.camera.pos, viewport_px_pos(scene.canvas, scene.viewport, i, j), INFINITY};
			// ray.dir = vec3_norm(vec3_op(SUB, ray.dir, scene.camera.pos));
			mlx_put_pixel(img, i, j, ray_get_color(&scene, &ray, scene.lights[0]));
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
		terminate("Error\nInvalid number of arguments\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		terminate("Error\nInvalid file\n");
	scene = (t_scene){.objects = objs, .lights = lights,
		.canvas = (t_canvas){1024, 1024}, .obj_count = 0, .light_count = 0};
	mlx = mlx_init(scene.canvas.w, scene.canvas.h, "MiniRT", 1);
	read_map(&scene, fd);
	render(mlx, scene);
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
