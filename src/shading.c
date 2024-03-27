/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:28:43 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/27 13:53:25 by htaheri          ###   ########.fr       */
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
	t_vec3	rayhit1;

	rayhit1 = (t_vec3){ray.o.x + ray.dir.x * t, ray.o.y + ray.dir.y * t, ray.o.z
		+ ray.dir.z * t};
	return (rayhit1);
}

double	sphere_shading(t_ray ray, t_sphere sphere, t_light light)
{
	t_vec3	normal;
	t_vec3	light_dir;
	double	light_rate;
	t_vec3	rayhit1;

	rayhit1 = ray_at(ray, ray.t);
	normal = vec3_norm(vec3_op(SUB, rayhit1, sphere.pos));
	light_dir = vec3_norm(vec3_op(SUB, light.pos, rayhit1));
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
	t_vec3	rayhit1;

	rayhit1 = ray_at(ray, ray.t);
	normal = vec3_norm(plane.normal);
	light_dir = vec3_norm(vec3_op(SUB, light.pos, rayhit1));
	light_rate = vec3_dot(normal, light_dir);
	if (light_rate < 0)
		light_rate = 0;
	return (light_rate);
}

double cylinder_shading(t_ray ray, t_cylinder cylinder, t_light light) {
    t_vec3 light_dir;
    double light_rate;
    t_vec3 rayhit1 = ray_at(ray, ray.t);
	
	t_vec3 cap1 = vec3_op(SUB, cylinder.pos, vec3_mul(cylinder.normal, cylinder.height / 2));
	
    t_vec3 hit_to_center = vec3_op(SUB, cap1, rayhit1);

    // Project this vector onto the cylinder's axis to find the component of the vector that's aligned with the axis
    float projection_length = vec3_dot(hit_to_center, cylinder.normal);

    // Calculate the projection point on the axis
    t_vec3 projection_on_axis = vec3_op(ADD, rayhit1, vec3_mul(cylinder.normal, projection_length));

    // The normal at the hit point is then the vector from the hit point to this projected point, normalized
    // Note: We actually want the vector pointing outward, so it's from the hit point away from the axis
    t_vec3 normal = vec3_norm(vec3_op(SUB, rayhit1, projection_on_axis));

    // Calculate the direction of the light relative to the hit point and normalize it
    light_dir = vec3_norm(vec3_op(SUB, light.pos, rayhit1));

    // Calculate the dot product between the normal and the light direction
    light_rate = vec3_dot(normal, light_dir);

    // Negative light_rate implies the light is hitting the surface from behind, which should not light the surface
    if (light_rate < 0) light_rate = 0.6;

    return light_rate;
}


int	ray_get_color(t_scene *scene, t_ray *ray, t_light light)
{
	t_object	*hit1;
    t_vec3      rayhit1;
	t_object	*hit2;
	t_color		color;
	t_ray		shadow_ray;
	t_vec3		normal;

	color = (t_color){0, 0, 0};
	hit1 = ray_get_hit(scene, ray);
	normal = (t_vec3){0, 0, 0};
	if (!hit1)
		return (0);
	rayhit1 = ray_at(*ray, ray->t);
	if (hit1->type == SPHERE)
	{
		color = hit1->sphere.color;
		normal = vec3_norm(vec3_op(SUB, rayhit1, hit1->sphere.pos));
		color = color_scale(color, sphere_shading(*ray, hit1->sphere, light));
	}
	else if (hit1->type == PLANE)
	{
		color = hit1->plane.color;
		normal = vec3_norm(hit1->plane.normal);
		color = color_scale(color, plane_shading(*ray, hit1->plane, light));
	}
	else if (hit1->type == CYLINDER)
	{
		color = hit1->cylinder.color;
		normal = vec3_norm(vec3_op(SUB, rayhit1, hit1->cylinder.pos));
		color = color_scale(color, cylinder_shading(*ray, hit1->cylinder, light));
	}
	shadow_ray.o = vec3_op(ADD, rayhit1, vec3_mul(normal, 0.005));
	shadow_ray.dir = vec3_norm(vec3_op(SUB, light.pos, rayhit1));
	shadow_ray.t = INFINITY;
	hit2 = ray_get_hit(scene, &shadow_ray);
	double shadow_intensity = 1;
	if (hit2)
		shadow_intensity = 0.3;
	color = color_scale(color, shadow_intensity);
	return (color.r << 24 | color.g << 16 | color.b << 8 | 0xFF);
}
