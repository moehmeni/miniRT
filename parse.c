/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:34:57 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/19 19:12:04 by mmomeni          ###   ########.fr       */
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

static t_object	parse_cylinder(char **v)
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
	return((t_object){.type = CYLINDER,
										.cylinder = (t_cylinder){pos, normal,
											ft_atof(v[3]) / 2, color}});
}

static t_object		parse_plane(char **v)
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
	return (t_object){.type = PLANE,
										.plane = (t_plane){pos, normal, color}};
}

static t_object		parse_sphere(char **v)
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
	return (t_object){.type = SPHERE,
										.sphere = (t_sphere){pos, radius,
											color}};
}

void	parse_line(char *line, t_scene *scene, size_t i)
{
	char			**s;
	t_object	obj;

	s = ft_split(line, ' ');
	if (!ft_strcmp(s[0], "A"))
	{
		// TODO:
	}
	else if (!ft_strcmp(s[0], "C"))
	{
		// TODO:
	}
	else if (!ft_strcmp(s[0], "L"))
	{
		// TODO:
	}
	else if (!ft_strcmp(s[0], "pl"))
		scene->objects[i] = parse_plane(s);
	else if (!ft_strcmp(s[0], "sp"))
		scene->objects[i] = parse_sphere(s);
	else if (!ft_strcmp(s[0], "cy"))
		scene->objects[i]= parse_cylinder(s);
	else
		terminate("Error\nInvalid object type found in the scene\n");
	ft_free_split(s);
}
