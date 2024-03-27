/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:21:15 by htaheri           #+#    #+#             */
/*   Updated: 2024/03/26 17:36:55 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

t_vec3	vec3_op(enum e_vec3_op op, t_vec3 a, t_vec3 b)
{
	if (op == SUB)
		return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
	else if (op == ADD)
		return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
	else if (op == MUL)
		return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
	else if (op == CROSS)
		return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
			- a.y * b.x});
	return ((t_vec3){0, 0, 0});
}

t_vec3	vec3_norm(t_vec3 a)
{
	return ((t_vec3){a.x / vec3_len(a), a.y / vec3_len(a), a.z / vec3_len(a)});
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	vec3_len(t_vec3 a)
{
	return (vec3_dist(a, (t_vec3){0, 0, 0}));
}

float	vec3_dist(t_vec3 a, t_vec3 b)
{
	float	x;
	float	y;
	float	z;

	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
	return (sqrt(x * x + y * y + z * z));
}
t_vec3 vec3_mul(t_vec3 a, float b)
{
	return ((t_vec3){a.x * b, a.y * b, a.z * b});
}
