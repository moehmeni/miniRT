/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:25:50 by mmomeni           #+#    #+#             */
/*   Updated: 2024/03/09 18:18:56 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"


int main(int argc, char **argv)
{
    int fd;
    
    if (argc != 2)
        return (ft_putstr("Usage: ./miniRT [file.rt]\n"), 1);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (ft_putstr("Error\n"), 1);
    while (get_next_line((fd)))
    {
        
    }
    return (0);
}
