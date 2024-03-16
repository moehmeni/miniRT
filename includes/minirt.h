/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:23:44 by htaheri           #+#    #+#             */
/*   Updated: 2024/03/16 15:19:31 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>


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

typedef struct s_color
{
	int		red;
	int		green;
	int		blue;
}			t_color;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_color	color;
}			t_sphere;

typedef struct s_plane
{
	t_vec3	normal;
	t_vec3	point;
	t_color	color;
}			t_plane;

typedef struct s_cylinder
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	start_cap;
	double	height;
	double	radius;
	t_color	color;
}			t_cylinder;

typedef struct s_canvas
{
	int		width;
	int		height;
}			t_canvas;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_ObjectType;

typedef struct s_object
{
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_ObjectType	type;
	struct s_object	*next;
}			t_object;

typedef struct s_scene
{
	t_canvas	canvas;
	t_object	*objects;
}			t_scene;

// vectors functions
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_mul(t_vec3 a, double t);
t_vec3		ray_at(t_ray *ray, double t);
int			vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		cross_product(t_vec3 a, t_vec3 b);
float		vec3_len(t_vec3 a);
float		vec3_dist(t_vec3 a, t_vec3 b);
t_vec3		vec3_norm(t_vec3 a);

// quadratic functions
t_quadratic	solve_quadratic(double a, double b, double c);

// ray intersection functions
int			intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t);
int			intersect_ray_plane(t_ray *ray, t_plane *plane, double *t);
int			intersect_ray_cylinder(t_ray *ray, t_cylinder *cyl, double *t);

#endif