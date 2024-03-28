/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:20:17 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/28 22:53:43 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

static float	cylinder_cap_hit(t_ray *ray, t_vec3 cap_c, t_vec3 cap_n,
		float r)
{
	float	denom;
	float	t;
	t_vec3	p;

	denom = vec3_dot(ray->dir, cap_n);
	if (fabs(denom) > 1e-6)
	{
		t = vec3_dot(vec3_op(SUB, cap_c, ray->o), cap_n) / denom;
		if (t < 0)
			return (-1);
		p = vec3_op(ADD, ray->o, vec3_mul(ray->dir, t));
		if (vec3_len(vec3_op(SUB, p, cap_c)) <= r)
			return (t);
	}
	return (-1);
}

static void	cylinder_caps_hit(t_ray *ray, t_cylinder cyl)
{
	float	t_cap;
	float	t_min;

	t_min = -1;
	t_cap = cylinder_cap_hit(ray, cyl.cap1, cyl.normal, cyl.radius);
	if (t_cap >= 0 && t_cap < t_min)
		t_min = t_cap;
	t_cap = cylinder_cap_hit(ray, cyl.cap2, cyl.normal, cyl.radius);
	if (t_cap >= 0 && t_cap < t_min)
		t_min = t_cap;
	if (t_min >= 0)
		ray->t = t_min;
}

static t_quadratic	cylinder_solve_eq(t_ray *ray, t_cylinder cyl)
{
	t_quadratic	q;
	t_vec3		oc;

	oc = vec3_op(SUB, ray->o, cyl.pos);
	q.a = vec3_dot(ray->dir, ray->dir) - pow(vec3_dot(ray->dir, cyl.normal), 2);
	q.b = 2 * (vec3_dot(ray->dir, oc) - vec3_dot(ray->dir, cyl.normal)
			* vec3_dot(oc, cyl.normal));
	q.c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cyl.normal), 2) - pow(cyl.radius,
			2);
	q = solve_quadratic(q.a, q.b, q.c);
	return (q);
}

float	cylinder_shading(t_scene *scene, t_ray *ray, t_cylinder cylinder)
{
	t_vec3	hit_p;
	t_vec3	projected_point_on_axis;
	t_vec3	light_dir;
	float	light_rate;

	hit_p = vec3_op(ADD, ray->o, vec3_mul(ray->dir, ray->t));
	projected_point_on_axis = vec3_op(ADD, cylinder.cap1,
			vec3_mul(cylinder.normal, vec3_dot(vec3_op(SUB, hit_p,
						cylinder.cap1), cylinder.normal)));
	light_dir = vec3_norm(vec3_op(SUB, scene->lights[0].pos, hit_p));
	light_rate = vec3_dot(vec3_norm(vec3_op(SUB, hit_p,
					projected_point_on_axis)), light_dir);
	return (fmax(0, light_rate));
}

int	ray_hit_cyl(t_ray *ray, t_cylinder cyl)
{
	float		t_min;
	float		ts[2];
	int			i;
	t_vec3		p;
	t_quadratic	q;

	t_min = INFINITY;
	q = cylinder_solve_eq(ray, cyl);
	if (q.delta < 0)
		return (0);
	ts[0] = q.t1;
	ts[1] = q.t2;
	i = 0;
	while (i < 2 && ts[i] >= 0)
	{
		p = vec3_op(ADD, ray->o, vec3_mul(ray->dir, ts[i]));
		if (vec3_dot(vec3_op(SUB, p, cyl.cap1),
						cyl.normal) *
					vec3_dot(vec3_op(SUB, p, cyl.cap2),
								cyl.normal) <=
				0 &&
			ts[i] < t_min)
			t_min = ts[i];
		i++;
	}
	ray->t = t_min;
	cylinder_caps_hit(ray, cyl);
	return (ray->t < INFINITY);
}
