/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:21:15 by htaheri           #+#    #+#             */
/*   Updated: 2024/03/15 12:21:07 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minirt.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	vec3_mul(t_vec3 a, double t)
{
	return ((t_vec3){a.x * t, a.y * t, a.z * t});
}

t_vec3	ray_at(t_ray *ray, double t)
{
	return (vec3_add(ray->origin, vec3_mul(ray->direction, t)));
}

int	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

float	vec3_len(t_vec3 a)
{
	return (sqrt(vec3_dot(a, a)));
}

float	vec3_dist(t_vec3 a, t_vec3 b)
{
	float x;
	float y;
	float z;

	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
	return (sqrt(x * x + y * y + z * z));
}

t_vec3 norm(t_vec3 a)
{
	float len;

	len = vec3_len(a);
	return ((t_vec3){a.x / len, a.y / len, a.z / len});
}

t_vec3 cross_product(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x});
}
