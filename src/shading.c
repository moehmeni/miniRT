/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:28:43 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/25 16:17:53 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

t_color	color_scale(t_color color, double scale)
{
	t_color	scaled_color;

	scaled_color = (t_color){color.r * scale, color.g * scale, color.b * scale};
	return (scaled_color);
}

t_vec3	ray_at(t_ray ray, double t)
{
	t_vec3	rayhit;

	rayhit = (t_vec3){ray.o.x + ray.dir.x * t, ray.o.y + ray.dir.y * t, ray.o.z
		+ ray.dir.z * t};
	return (rayhit);
}

double	sphere_shading(t_ray ray, t_sphere sphere, t_light light)
{
	t_vec3	normal;
	t_vec3	light_dir;
	double	light_rate;
	t_vec3	rayhit;

	rayhit = ray_at(ray, ray.t);
	normal = vec3_norm(vec3_op(SUB, rayhit, sphere.pos));
	light_dir = vec3_norm(vec3_op(SUB, light.pos, rayhit));
	light_rate = vec3_dot(normal, light_dir);
	if (light_rate < 0)
		light_rate = 0;
	return (light_rate);
}

double	plane_shading(t_ray ray, t_plane plane, t_light light)
{
	t_vec3	normal;
	t_vec3	light_dir;
	double	light_rate;
	t_vec3	rayhit;

	rayhit = ray_at(ray, ray.t);
	normal = vec3_norm(plane.normal);
	light_dir = vec3_norm(vec3_op(SUB, light.pos, rayhit));
	light_rate = vec3_dot(normal, light_dir);
	if (light_rate < 0)
		light_rate = 0;
	return (light_rate);
}

double cylinder_shading(t_ray ray, t_cylinder cylinder, t_light light)
{
	t_vec3	normal;
	t_vec3	light_dir;
	double	light_rate;
	t_vec3	rayhit;

	rayhit = ray_at(ray, ray.t);
	normal = vec3_norm(vec3_op(SUB, rayhit, cylinder.pos));
	light_dir = vec3_norm(vec3_op(SUB, light.pos, rayhit));
	light_rate = vec3_dot(normal, light_dir);
	if (light_rate < 0)
		light_rate = 0;
	return (light_rate);
}

int	ray_get_color(t_scene *scene, t_ray *ray, t_light light)
{
	t_object	*hit;
	t_color		color;

	color = (t_color){0, 0, 0};
	hit = ray_get_hit(scene, ray);
	if (!hit)
		return (0);
	if (hit->type == SPHERE)
	{
		color = hit->sphere.color;
		color = color_scale(color, sphere_shading(*ray, hit->sphere, light));
	}
	else if (hit->type == PLANE)
	{
		color = hit->plane.color;
		color = color_scale(color, plane_shading(*ray, hit->plane, light));
	}
	else if (hit->type == CYLINDER)
	{
		color = hit->cylinder.color;
		color = color_scale(color, cylinder_shading(*ray, hit->cylinder, light));
	}
	return (color.r << 24 | color.g << 16 | color.b << 8 | 0xFF);
}
