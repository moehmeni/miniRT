/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:28:43 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/28 22:53:58 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

static t_color	color_scale(t_color color, float scale)
{
	t_color	scaled_color;

	scaled_color = (t_color){color.r * scale, color.g * scale, color.b * scale};
	return (scaled_color);
}

static float	sphere_shading(t_scene *scene, t_ray *ray, t_sphere sphere)
{
	t_vec3	normal;
	t_vec3	light_dir;
	float	light_rate;
	t_vec3	hit_p;

	hit_p = vec3_op(ADD, ray->o, vec3_mul(ray->dir, ray->t));
	normal = vec3_norm(vec3_op(SUB, hit_p, sphere.pos));
	light_dir = vec3_norm(vec3_op(SUB, scene->lights[0].pos, hit_p));
	light_rate = vec3_dot(normal, light_dir);
	return (fmax(0, light_rate));
}

static float	plane_shading(t_scene *scene, t_ray *ray, t_plane plane)
{
	t_vec3	normal;
	t_vec3	light_dir;
	float	light_rate;
	t_vec3	hit_p;

	hit_p = vec3_op(ADD, ray->o, vec3_mul(ray->dir, ray->t));
	normal = vec3_norm(plane.normal);
	light_dir = vec3_norm(vec3_op(SUB, scene->lights[0].pos, hit_p));
	light_rate = vec3_dot(normal, light_dir);
	return (fmax(0, light_rate));
}

static int	shadow_shading(t_scene *scene, t_vec3 *hit1, t_vec3 normal,
		t_color color)
{
	t_ray		shadow_ray;
	float		shadow_intensity;
	t_object	*hit2;

	shadow_ray.o = vec3_op(ADD, *hit1, vec3_mul(normal, 0.005));
	shadow_ray.dir = vec3_norm(vec3_op(SUB, scene->lights[0].pos, *hit1));
	shadow_ray.t = INFINITY;
	hit2 = ray_get_hit(scene, &shadow_ray);
	shadow_intensity = 1;
	if (hit2)
	{
		shadow_intensity = shadow_ray.t / vec3_len(vec3_op(SUB,
					scene->lights[0].pos, vec3_op(ADD, shadow_ray.o,
						vec3_mul(shadow_ray.dir, shadow_ray.t))));
		shadow_intensity = fmin(0.999, shadow_intensity);
	}
	color = color_scale(color, shadow_intensity);
	return (color.r << 24 | color.g << 16 | color.b << 8 | 0xFF);
}

static t_color	calculate_hit_color(t_scene *scene, t_ray *ray, t_object *hit1)
{
	t_color	color;

	color = (t_color){0, 0, 0};
	if (hit1->type == SPHERE)
	{
		color = hit1->sphere.color;
		color = color_scale(color, sphere_shading(scene, ray, hit1->sphere));
	}
	else if (hit1->type == PLANE)
	{
		color = hit1->plane.color;
		color = color_scale(color, plane_shading(scene, ray, hit1->plane));
	}
	else if (hit1->type == CYLINDER)
	{
		color = hit1->cylinder.color;
		color = color_scale(color, cylinder_shading(scene, ray,
					hit1->cylinder));
	}
	return (color);
}

int	ray_get_color(t_scene *scene, t_ray *ray)
{
	t_object	*hit1;
	t_vec3		hit_p;
	t_color		color;
	t_vec3		normal;

	normal = (t_vec3){0, 0, 0};
	hit1 = ray_get_hit(scene, ray);
	if (!hit1)
		return (0);
	hit_p = vec3_op(ADD, ray->o, vec3_mul(ray->dir, ray->t));
	color = calculate_hit_color(scene, ray, hit1);
	if (hit1->type == SPHERE)
		normal = vec3_norm(vec3_op(SUB, hit_p, hit1->sphere.pos));
	else if (hit1->type == PLANE)
		normal = vec3_norm(hit1->plane.normal);
	else if (hit1->type == CYLINDER)
		normal = vec3_norm(vec3_op(SUB, hit_p, hit1->cylinder.cap1));
	return (shadow_shading(scene, &hit_p, normal, color));
}
