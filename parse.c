/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:34:57 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/18 20:58:43 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

static void	parse_vec3(char *str, float *vec)
{
	char	**vec_heap;

	vec_heap = ft_split(str, ',');
	vec[0] = ft_atof(vec_heap[0]);
	vec[1] = ft_atof(vec_heap[1]);
	vec[2] = ft_atof(vec_heap[2]);
	ft_free_split(vec_heap);
}

static void	parse_cylinder(char **v, t_scene *scene, size_t *i)
{
	float	vec[3];
	t_vec3	pos;
	t_vec3	normal;
	t_color	color;

	parse_vec3(v[1], vec);
	pos = (t_vec3){vec[0], vec[1], vec[2]};
	parse_vec3(v[2], vec);
	normal = (t_vec3){vec[0], vec[1], vec[2]};
	parse_vec3(v[5], vec);
	color = (t_color){vec[0], vec[1], vec[2]};
	scene->objects[*i++] = (t_object){.type = CYLINDER,
										.cylinder = (t_cylinder){pos, normal,
											ft_atof(v[3]) / 2, color}};
}

static void	parse_plane(char **v, t_scene *scene, size_t *i)
{
	float	vec[3];
	t_vec3	pos;
	t_vec3	normal;
	t_color	color;

	parse_vec3(v[1], vec);
	pos = (t_vec3){vec[0], vec[1], vec[2]};
	parse_vec3(v[2], vec);
	normal = (t_vec3){vec[0], vec[1], vec[2]};
	parse_vec3(v[3], vec);
	color = (t_color){vec[0], vec[1], vec[2]};
	scene->objects[*i++] = (t_object){.type = PLANE,
										.plane = (t_plane){pos, normal, color}};
}

static void	parse_sphere(char **v, t_scene *scene, size_t *i)
{
	float	vec[3];
	t_vec3	pos;
	t_color	color;
	float	radius;

	parse_vec3(v[1], vec);
	pos = (t_vec3){vec[0], vec[1], vec[2]};
	radius = ft_atof(v[2]) / 2;
	parse_vec3(v[3], vec);
	color = (t_color){vec[0], vec[1], vec[2]};
	scene->objects[*i++] = (t_object){.type = SPHERE,
										.sphere = (t_sphere){pos, radius,
											color}};
}

void	parse_line(char *line, t_scene *scene)
{
	char			**s;
	static size_t	i;

	if (!i)
		i = 0;
	s = ft_split(line, ' ');
	if (ft_strcmp(s[0], "A"))
	{
		// TODO:
	}
	else if (ft_strcmp(s[0], "C"))
	{
		// TODO:
	}
	else if (ft_strcmp(s[0], "L"))
	{
		// TODO:
	}
	else if (ft_strcmp(s[0], "pl"))
		parse_plane(s, scene, &i);
	else if (ft_strcmp(s[0], "sp"))
		parse_sphere(s, scene, &i);
	else if (ft_strcmp(s[0], "cy"))
		parse_cylinder(s, scene, &i);
	else
		terminate("Error\nInvalid object type found in the scene\n");
	ft_free_split(s);
	scene->obj_count = i;
}
