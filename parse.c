/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:34:57 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/18 16:13:30 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

int	*parse_vec3(char *str)
{
	int	vec[3];
	int	*vec_heap;

	vec_heap = ft_split(str, ",");
	vec[0] = vec_heap[0];
	vec[1] = vec_heap[1];
	vec[2] = vec_heap[2];
	ft_free_split(vec_heap);
	return (vec);
}

void parse_cylinder(char **v, t_scene *scene, size_t *i)
{
    int *vec;
    t_vec3 pos;
    t_vec3 normal;
    t_vec3 start_cap;
    t_color color;

    vec = parse_vec3(v[1]);
    pos = (t_vec3){vec[0], vec[1], vec[2]};
    vec = parse_vec3(v[2]);
    normal = (t_vec3){vec[0], vec[1], vec[2]};
    vec = parse_vec3(v[5]);
    color = (t_color){vec[0], vec[1], vec[2]};
    
    scene->objects[*i++] = (t_object){.type = CYLINDER,
        .cylinder = (t_cylinder){pos, normal, 0, color}};
}

void parse_cylinder(char **v, t_scene *scene)
{
    
}


void	parse_line(char *line, t_scene *scene)
{
	char **s;
	static size_t i;
	int *pos;
	int *color;

	if (!i)
		i = 0;
	s = ft_split(line, ' ');
	pos = parse_vec3(s[1]);
	if (ft_strcmp(s[0], "A"))
	// TODO:
	{
	}
	if (ft_strcmp(s[0], "C"))
	// TODO:
	{
	}
	if (ft_strcmp(s[0], "L"))
	// TODO:
	{
	}
	if (ft_strcmp(s[0], "pl"))
        
        
	if (ft_strcmp(s[0], "cy"))
        parse_cylinder(s, scene, &i);

	ft_free_split(spl);
}
