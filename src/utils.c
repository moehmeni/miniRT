/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:51:05 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/21 18:06:36 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

t_vec3	parse_vec3(char *str)
{
	char	**vec_heap;
	t_vec3	vec;

	vec_heap = ft_split(str, ',');
	vec.x = ft_atof(vec_heap[0]);
	vec.y = ft_atof(vec_heap[1]);
	vec.z = ft_atof(vec_heap[2]);
	ft_free_split(vec_heap);
	return (vec);
}

t_color	parse_color(char *str)
{
	t_vec3	vec;

	vec = parse_vec3(str);
	return ((t_color){vec.x, vec.y, vec.z});
}

void	parse_line(char *line, t_scene *scene)
{
	char	**s;

	s = ft_split(line, ' ');
	if (!ft_strcmp(s[0], "A"))
		scene->amblight = (t_amblight){ft_atof(s[1]), parse_color(s[2])};
	else if (!ft_strcmp(s[0], "C"))
		scene->camera = parse_camera(s);
	else if (!ft_strcmp(s[0], "L"))
		scene->lights[scene->light_count++] = parse_light(s);
	else if (!ft_strcmp(s[0], "pl"))
		scene->objects[scene->obj_count++] = parse_plane(s);
	else if (!ft_strcmp(s[0], "sp"))
		scene->objects[scene->obj_count++] = parse_sphere(s);
	else if (!ft_strcmp(s[0], "cy"))
		scene->objects[scene->obj_count++] = parse_cylinder(s);
	else
		terminate("Error\nInvalid object type found in the scene\n");
	ft_free_split(s);
}
