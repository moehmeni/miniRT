/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:15:08 by htaheri           #+#    #+#             */
/*   Updated: 2024/03/15 15:50:50 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

// IntersectRaySphere(O, D, sphere) {
//     r = sphere.radius
//     CO = O - sphere.center

//     a = dot(D, D)
//     b = 2*dot(CO, D)
//     c = dot(CO, CO) - r*r

//     discriminant = b*b - 4*a*c
//     if discriminant < 0 {
//         return inf, inf
//     }

//     t1 = (-b + sqrt(discriminant)) / (2*a)
//     t2 = (-b - sqrt(discriminant)) / (2*a)
//     return t1, t2
// }


// A function capable of converting x, y coordinates from the canvas to the viewport.

t_vec3 canvas2viewoprt(t_canvas *canvas, t_vec3 *viewport, int x, int y)
{
	t_vec3	point;

	point.x = x * viewport->x / canvas->width;
	point.y = y * viewport->y / canvas->height;
	point.z = viewport->z;
	return (point);
}

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sq_delta;
	float	t1;
	float	t2;
	bool	hit;
}	t_quadratic;

t_quadratic solve_quadratic(double a, double b, double c)
{
	t_quadratic	q;

	q.hit = true;
	q.delta = b * b - 4 * a * c;
	if (q.delta < 0)
	{
		q.hit = false;
		return (q);
	}
	q.sq_delta = sqrt(q.delta);
	q.t1 = (-b + q.sq_delta) / (2 * a);
	q.t2 = (-b - q.sq_delta) / (2 * a);
	return (q);
}

t_quadratic	intersect_ray_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vec3		oc;
	t_quadratic	q;

	q.hit = true;
	oc = vec3_sub(ray->origin, sphere->center);
	q.a = vec3_dot(ray->direction, ray->direction);
	q.b = 2.0 * vec3_dot(oc, ray->direction);
	q.c = vec3_dot(oc, oc) - (sphere->radius * sphere->radius);
	q = solve_quadratic(q.a, q.b, q.c);
	if (q.hit && (q.t1 < 0 || q.t2 < 0))
		q.hit = false;
	else if (q.t1 < 0)
		q.t1 = q.t2;
	else if (q.t2 < 0)
		q.t2 = q.t1;
	// t_vec3 p1 = ray_at(ray, q.t1);
	// t_vec3 norm_p1 = vec3_sub(p1, sphere->center);
	return (q);
}

int	intersect_ray_plane(t_ray *ray, t_plane *plane, double *t)
{
	double	denom;
	double	numer;

	denom = vec3_dot(plane->normal, ray->direction);
	if (fabs(denom) > 0.0001)
	{
		numer = vec3_dot(vec3_sub(plane->point, ray->origin), plane->normal);
		*t = numer / denom;
		return (*t >= 0);
	}
	return (0);
}

// int	main(void)
// {
// 	t_ray		ray;
// 	t_sphere	sphere;
// 	double		t;
// 	t_plane		plane;

// 	plane.normal = (t_vec3){0, 0, 1};
// 	plane.point = (t_vec3){0, 0, 0};
// 	if (intersect_ray_plane(&ray, &plane, &t))
// 		printf("Intersected at t = %f\n", t);
// 	else
// 		printf("No intersection\n");
// 	ray.origin = (t_vec3){0, 0, 0};
// 	ray.direction = (t_vec3){0, 0, 1};
// 	sphere.center = (t_vec3){0, 0, 0};
// 	sphere.radius = 1;
// 	if (intersect_ray_sphere(&ray, &sphere, &t))
// 		printf("Intersected at t = %f\n", t);
// 	else
// 		printf("No intersection\n");
// 	return (0);
// }



