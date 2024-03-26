/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:51:05 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/26 17:53:31 by htaheri          ###   ########.fr       */
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

void	parse_line(char *line, t_scene *scene, int i)
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
		scene->objects[scene->obj_count++] = parse_plane(s, i);
	else if (!ft_strcmp(s[0], "sp"))
		scene->objects[scene->obj_count++] = parse_sphere(s, i);
	else if (!ft_strcmp(s[0], "cy"))
		scene->objects[scene->obj_count++] = parse_cylinder(s, i);
	else
		terminate("Error\nInvalid object type found in the scene\n");
	ft_free_split(s);
}

t_vec3	viewport_px_pos(t_canvas canvas, t_viewport v, int x, int y)
{
	t_vec3	point;

	point.x = (2 * (x + 0.5) / canvas.w - 1) * v.w;
	point.y = (1 - 2 * (y + 0.5) / canvas.h) * v.h;
	point.z = 1;
	return (point);
}

t_viewport	viewport_dim(t_canvas canvas, t_camera camera)
{
	t_viewport	v;

	v.w = 2 * tan(camera.fov / 2);
	v.h = v.w * (canvas.h / canvas.w);
	return (v);
}
