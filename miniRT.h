/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_hamid.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:23:44 by htaheri           #+#    #+#             */
/*   Updated: 2024/03/16 15:41:46 by mmomeni          ###   ########.fr       */
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

typedef struct s_vec3
{
	double x;
	double y;
	double z;
} t_vec3;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

/* ----------------------------*/ /*scene*/

typedef struct s_amblight
{
	double ratio;
	t_color color;
} t_amblight;

typedef struct s_light
{
	t_vec3 position;
	double ratio;
	t_color color;
} t_light;

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
} t_ray;

typedef struct s_camera
{
	t_vec3 position;
	double fov;
} t_camera;

/* ----------------------------*/ /*objects*/

typedef struct s_sphere
{
	t_vec3 position;
	double radius;
	t_color color;
} t_sphere;

typedef struct s_plane
{
	t_vec3 position;
	t_color color;
} t_plane;

typedef struct s_cylinder
{
	t_vec3 position;
	double height;
	double radius;
	t_color color;
} t_cylinder;

/* ----------------------------*/ /*functions*/

t_vec3 vec3_op(enum e_vec3_op op, t_vec3 a, t_vec3 b);
t_vec3 vec3_norm(t_vec3 a);
float vec3_dot(t_vec3 a, t_vec3 b);
float vec3_len(t_vec3 a);
float vec3_dist(t_vec3 a, t_vec3 b);

int intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t);

#endif
