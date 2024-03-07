/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:27:43 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/07 15:24:17 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <fcntl.h>

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		eol;
}			t_point;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_amblight
{
	double	ratio;
	t_color	color;
}			t_amblight;

typedef struct s_camera
{
	double	x;
	double	y;
	double	z;
	double	x_rot;
	double	y_rot;
	double	z_rot;
	double	fov;
}			t_camera;

typedef struct s_light
{
	double	x;
	double	y;
	double	z;
	double	ratio;
	t_color	color;
}			t_light;


typedef struct s_sphere
{
    double	x;
    double	y;
    double	z;
    double	r;
    t_color	color;
}			t_sphere;

typedef struct s_plane
{
    double	x;
    double	y;
    double	z;
    double	x_rot;
    double	y_rot;
    double	z_rot;
    t_color	color;
}			t_plane;


typedef struct s_cylinder 

#endif
