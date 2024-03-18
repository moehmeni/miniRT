/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:15:08 by htaheri           #+#    #+#             */
/*   Updated: 2024/03/18 16:09:52 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	canvas2viewoprt(t_canvas *canvas, t_vec3 *viewport, int x, int y)
{
	t_vec3	point;

	point.x = x * viewport->x / canvas->width;
	point.y = y * viewport->y / canvas->height;
	point.z = viewport->z;
	return (point);
}

t_quadratic	solve_quadratic(float a, float b, float c)
{
	t_quadratic	q;

	q.hit = 1;
	q.delta = b * b - 4 * a * c;
	if (q.delta < 0)
	{
		q.hit = 0;
		return (q);
	}
	q.sq_delta = sqrt(q.delta);
	q.t1 = (-b + q.sq_delta) / (2 * a);
	q.t2 = (-b - q.sq_delta) / (2 * a);
	return (q);
}

int	intersect_ray_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vec3		oc;
	t_quadratic	q;

	q.hit = 1;
	oc = vec3_op(SUB, ray->origin, sphere->position);
	q.a = vec3_dot(ray->direction, ray->direction);
	q.b = 2.0 * vec3_dot(oc, ray->direction);
	q.c = vec3_dot(oc, oc) - (sphere->radius * sphere->radius);
	q = solve_quadratic(q.a, q.b, q.c);
	if (q.hit && (q.t1 < 0 || q.t2 < 0))
		return (0);
	else if (q.t1 < 0)
		ray->t = q.t2;
	else if (q.t2 < 0)
		ray->t = q.t1;
	else
		ray->t = fmin(q.t1, q.t2);
	return (1);
}

int	intersect_ray_plane(t_ray *ray, t_plane *plane)
{
	float	denom;
	float	numer;

	denom = vec3_dot(plane->normal, ray->direction);
	if (fabs(denom) > 0)
	{
		numer = vec3_dot(vec3_op(SUB, plane->position, ray->origin),
							plane->normal);
		ray->t = numer / denom;
		return (ray->t >= 0);
	}
	return (0);
}

int	intersect_ray_cylinder(t_ray *ray, t_cylinder *cyl)
{
	t_quadratic	q;
	t_vec3		oc;

	oc = vec3_op(SUB, ray->origin, cyl->position);
	q.a = vec3_dot(ray->direction, ray->direction) - vec3_dot(ray->direction,
			cyl->normal) * vec3_dot(ray->direction, cyl->normal);
	q.b = 2 * (vec3_dot(ray->direction, oc) - vec3_dot(ray->direction,
				cyl->normal) * vec3_dot(oc, cyl->normal));
	q.c = vec3_dot(oc, oc) - vec3_dot(oc, cyl->normal) * vec3_dot(oc,
			cyl->normal) - cyl->radius * cyl->radius;
	q = solve_quadratic(q.a, q.b, q.c);
	if (q.hit && (q.t1 < 0 || q.t2 < 0))
		return (0);
	else if (q.t1 < 0)
		ray->t = q.t2;
	else if (q.t2 < 0)
		ray->t = q.t1;
	else
		ray->t = fmin(q.t1, q.t2);
	return (1);
}

t_object	*intersect_ray_object(t_scene *scene, t_ray *ray)
{
	t_object	*nearest;
	t_object	*current;
	float		t_min;

	nearest = NULL;
	current = scene->objects;
	t_min = INFINITY;
	while (current)
	{
		if (current->type == SPHERE)
			intersect_ray_sphere(ray, current->sphere);
		else if (current->type == PLANE)
			intersect_ray_plane(ray, current->plane);
		else if (current->type == CYLINDER)
			intersect_ray_cylinder(ray, current->cylinder);
		if (ray->t < t_min)
			t_min = ray->t;
		current = current->next;
	}
	ray->t = t_min;
	return (nearest);
}

t_color	color_at(t_scene *scene, t_ray *ray)
{
	t_object	*hit;
	float		t;

	hit = intersect_ray_object(scene, ray);
	if (hit)
	{
		if (hit->type == SPHERE)
			return (hit->sphere->color);
		else if (hit->type == PLANE)
			return (hit->plane->color);
		else if (hit->type == CYLINDER)
			return (hit->cylinder->color);
	}
	return ((t_color){0, 0, 0});
}
