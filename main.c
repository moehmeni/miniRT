/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:25:50 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/17 20:45:37 by mmomeni          ###   ########.fr       */
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

int	*parse_vec3(char *str)
{
	int	vec[3];
	int	*vec_heap;

	vec_heap = ft_split(str, ",");
	vec[0] = vec_heap[0];
	vec[1] = vec_heap[1];
	vec[2] = vec_heap[2];
	ft_free_split(vec_heap);
	return (vec);
}

void	parse_line(char *line, t_scene *scene)
{
	char	**spl;

	spl = ft_split(line, ' ');
	if (ft_strcmp(spl[0], "A"))
	{
		
	}
	ft_free_split(spl);
}

int	main(int argc, char **argv)
{
	int			fd;
	mlx_t		*mlx;
	t_object	objs[10];
	t_scene		scene;

	if (argc != 2)
		return (ft_putstr("Usage: ./minirt [file.rt]\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr("Error\n"), 1);
	mlx = mlx_init(512, 512, "MiniRT", 1);
	scene = (t_scene){.canvas = NULL, .objects = objs};
	while (get_next_line((fd)))
	{
	}
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
