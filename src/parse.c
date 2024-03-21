/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:49:53 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/21 18:12:28 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

t_object	parse_cylinder(char **v)
{
	t_cylinder	cylinder;

	cylinder.pos = parse_vec3(v[1]);
	cylinder.normal = parse_vec3(v[2]);
	cylinder.radius = ft_atof(v[3]) / 2;
	cylinder.height = ft_atof(v[4]);
	cylinder.color = parse_color(v[5]);
	return ((t_object){.type = CYLINDER, .cylinder = cylinder});
}

t_object	parse_plane(char **v)
{
	t_plane	plane;

	plane.pos = parse_vec3(v[1]);
	plane.normal = parse_vec3(v[2]);
	plane.color = parse_color(v[3]);
	return ((t_object){.type = PLANE, .plane = plane});
}

t_object	parse_sphere(char **v)
{
	t_sphere	sphere;

	sphere.pos = parse_vec3(v[1]);
	sphere.radius = ft_atof(v[2]) / 2;
	sphere.color = parse_color(v[3]);
	return ((t_object){.type = SPHERE, .sphere = sphere});
}

t_camera	parse_camera(char **v)
{
	t_camera	camera;

	camera.pos = parse_vec3(v[1]);
	camera.normal = parse_vec3(v[2]);
	camera.fov = ft_atof(v[3]);
	return (camera);
}

t_light	parse_light(char **v)
{
	t_light	light;

	light.pos = parse_vec3(v[1]);
	light.ratio = ft_atof(v[2]);
	light.color = parse_color(v[3]);
	return (light);
}
