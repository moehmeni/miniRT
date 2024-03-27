/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:15:08 by htaheri           #+#    #+#             */
/*   Updated: 2024/03/27 14:30:55 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quadratic	solve_quadratic(float a, float b, float c)
{
	t_quadratic	q;

	q.delta = b * b - 4 * a * c;
	if (q.delta < 0)
		return (q);
	q.t1 = (-b + sqrt(q.delta)) / (2 * a);
	q.t2 = (-b - sqrt(q.delta)) / (2 * a);
	return (q);
}

static int	ray_hit_sphere(t_ray *ray, t_sphere sphere)
{
	t_vec3		oc;
	t_quadratic	q;

	oc = vec3_op(SUB, ray->o, sphere.pos);
	q.a = vec3_dot(ray->dir, ray->dir);
	q.b = 2.0 * vec3_dot(oc, ray->dir);
	q.c = vec3_dot(oc, oc) - (sphere.radius * sphere.radius);
	q = solve_quadratic(q.a, q.b, q.c);
	if (q.delta < 0 || (q.t1 < 0 && q.t2 < 0))
		return (0);
	else if (q.t1 < 0)
		ray->t = q.t2;
	else if (q.t2 < 0)
		ray->t = q.t1;
	else
		ray->t = fmin(q.t1, q.t2);
	return (1);
}

static int	ray_hit_plane(t_ray *ray, t_plane plane)
{
	float	denom;
	float	t;

	denom = vec3_dot(plane.normal, ray->dir);
	if (fabs(denom) < 0.00001)
		return (0);
	t = vec3_dot(vec3_op(SUB, plane.pos, ray->o), plane.normal) / denom;
	if (t < 0)
		return (0);
	ray->t = t;
	return (1);
}

float check_cap_intersection(t_ray *ray, t_vec3 cap_c, t_vec3 cap_n, float r)
{
	float	denom;
	float	t;
	t_vec3	intersection_point;

	denom = vec3_dot(ray->dir, cap_n);
	if (fabs(denom) > 1e-6)
	{
		t = vec3_dot(vec3_op(SUB, cap_c, ray->o), cap_n) / denom;
		if (t < 0) 
			return (-1);
		intersection_point = vec3_op(ADD, ray->o, vec3_mul(ray->dir, t));
		if (vec3_len(vec3_op(SUB, intersection_point, cap_c)) <= r)
			return (t);
	}
	return (-1);
}

int ray_hit_cyl(t_ray *ray, t_cylinder cyl)
{
	t_quadratic	q;
	t_vec3		oc;
	float		t_min;
	int			hit;
	float		ts[2];
	int			i;
	t_vec3		intersection_point;
	float		t_cap;

	oc = vec3_op(SUB, ray->o, cyl.pos);
	q.a = vec3_dot(ray->dir, ray->dir) - pow(vec3_dot(ray->dir, cyl.normal), 2);
	q.b = 2 * (vec3_dot(ray->dir, oc) - vec3_dot(ray->dir, cyl.normal)
		* vec3_dot(oc, cyl.normal));
	q.c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cyl.normal), 2) 
		- pow(cyl.radius, 2);
	q = solve_quadratic(q.a, q.b, q.c);
	if (q.delta < 0)
		return (0);

	t_min = INFINITY;
	hit = 0;

	ts[0] = q.t1;
	ts[1] = q.t2;
	i = 0;
	while (i < 2) 
	{
		if (ts[i] > 0)
		{
			intersection_point = vec3_op(ADD, ray->o,
					vec3_mul(ray->dir, ts[i]));
			if (vec3_dot(vec3_op(SUB, intersection_point, cyl.cap1), cyl.normal) *
				vec3_dot(vec3_op(SUB, intersection_point, cyl.cap2), cyl.normal) <= 0)
			{
				if (ts[i] < t_min)
				{
					t_min = ts[i];
					hit = 1;
				}
			}
		}
		i++;
	}

	t_cap = check_cap_intersection(ray, cyl.cap1, cyl.normal, cyl.radius);
	if (t_cap >= 0 && t_cap < t_min)
	{
		t_min = t_cap;
		hit = 1;
	}

	t_cap = check_cap_intersection(ray, cyl.cap2, cyl.normal, cyl.radius);
	if (t_cap >= 0 && t_cap < t_min)
	{
		t_min = t_cap;
		hit = 1;
	}

	if (hit)
	{
		ray->t = t_min;
		return (1);
	}
	return (0);
}


t_object	*ray_get_hit(t_scene *scene, t_ray *ray)
{
	float	t_min;
	size_t	i;
	int		j;

	t_min = INFINITY;
	i = 0;
	j = -1;
	while (i < scene->obj_count)
	{
		if (scene->objects[i].type == SPHERE)
			ray_hit_sphere(ray, scene->objects[i].sphere);
		else if (scene->objects[i].type == PLANE)
			ray_hit_plane(ray, scene->objects[i].plane);
		else if (scene->objects[i].type == CYLINDER)
			ray_hit_cyl(ray, scene->objects[i].cylinder);
		if (ray->t < t_min)
		{
			t_min = ray->t;
			j = i;
		}
		i++;
	}
	ray->t = t_min;
	if (j == -1)
		return (NULL);
	return (&scene->objects[j]);
}
