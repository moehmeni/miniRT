/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:28:43 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/21 20:16:38 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

int	ray_get_color(t_scene *scene, t_ray *ray)
{
	t_object	*hit;
	t_color		color;

	color = (t_color){0, 0, 0};
	hit = ray_get_hit(scene, ray);
	if (hit)
	{
		if (hit->type == SPHERE)
			color = hit->sphere.color;
		else if (hit->type == PLANE)
			color = hit->plane.color;
		else if (hit->type == CYLINDER)
			color = hit->cylinder.color;
	}
	return (color.r << 16 | color.g << 8 | color.b);
}
