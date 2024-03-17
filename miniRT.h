/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:23:44 by htaheri           #+#    #+#             */
/*   Updated: 2024/03/17 12:34:44 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./MLX42/include/MLX42/MLX42.h"
#include "./libft/libft.h"

/* ----------------------------*/ /*types*/

enum e_vec3_op
{
	SUB,
	ADD,
	MUL,
	CROSS,
};

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_ObjectType;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sq_delta;
	float	t1;
	float	t2;
	int		hit;
}			t_quadratic;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/* ----------------------------*/ /*scene*/

typedef struct s_amblight
{
	double	ratio;
	t_color	color;
}	t_amblight;

typedef struct s_light
{
	t_vec3	position;
	double	ratio;
	t_color	color;
}	t_light;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_camera
{
	t_vec3	position;
	double	fov;
}	t_camera;

/* ----------------------------*/ /*objects*/

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
	double	radius;
	t_color	color;
}			t_cylinder;

typedef struct s_canvas
{
	int		width;
	int		height;
}			t_canvas;

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
/* ----------------------------*/ /*functions*/

t_vec3	vec3_op(enum e_vec3_op op, t_vec3 a, t_vec3 b);
t_vec3	vec3_norm(t_vec3 a);
float	vec3_dot(t_vec3 a, t_vec3 b);
float	vec3_len(t_vec3 a);
float	vec3_dist(t_vec3 a, t_vec3 b);

int	intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t);

#endif
