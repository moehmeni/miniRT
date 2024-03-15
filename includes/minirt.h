/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:23:44 by htaheri           #+#    #+#             */
/*   Updated: 2024/03/15 16:13:37 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
#include <stdbool.h>


typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
}			t_sphere;

typedef struct s_plane
{
	t_vec3	normal;
	t_vec3	point;
}			t_plane;

typedef struct s_cylinder
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3  start_cap;
	double	height;
	double	radius;
}			t_cylinder;

typedef struct s_canvas
{
	int		width;
	int		height;
}			t_canvas;

// vectors functions
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_mul(t_vec3 a, double t);
t_vec3	ray_at(t_ray *ray, double t);
int		vec3_dot(t_vec3 a, t_vec3 b);

// ray intersection functions
int		intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t);

#endif