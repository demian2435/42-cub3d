/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:38:52 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/01 18:54:43 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

int main(void)
{
	int RENDER_X;
	int RENDER_Y;
	char *TEXTURE_NORTH;
	char *TEXTURE_SOUTH;
	char *TEXTURE_WEST;
	char *TEXTURE_EAST;
	char *TEXTURE_SPRITE;
	int FLOOR_COLOR[3];
	int CEILING_COLOR[3];
	char *map;

	int fd = open(".cub", O_RDONLY);
	char *line;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'R' && *(line + 1) == ' ')
		{
			line += 2;
			RENDER_X = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			line++;
			RENDER_Y = ft_atoi(line);
			continue;
		}
		else if (*line == 'N' && *(line + 1) == 'O')
		{
			line += 3;
			TEXTURE_NORTH = ft_strdup(line);
			continue;
		}
		else if (*line == 'S' && *(line + 1) == 'O')
		{
			line += 3;
			TEXTURE_SOUTH = ft_strdup(line);
			continue;
		}
		else if (*line == 'W' && *(line + 1) == 'E')
		{
			line += 3;
			TEXTURE_WEST = ft_strdup(line);
			continue;
		}
		else if (*line == 'E' && *(line + 1) == 'A')
		{
			line += 3;
			TEXTURE_EAST = ft_strdup(line);
			continue;
		}
		else if (*line == 'S' && *(line + 1) == ' ')
		{
			line += 2;
			TEXTURE_SPRITE = ft_strdup(line);
			continue;
		}
		else if (*line == 'F' && *(line + 1) == ' ')
		{
			line += 2;
			FLOOR_COLOR[0] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			line++;
			FLOOR_COLOR[1] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			line++;
			FLOOR_COLOR[2] = ft_atoi(line);
			continue;
		}
		else if (*line == 'C' && *(line + 1) == ' ')
		{
			line += 2;
			CEILING_COLOR[0] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			line++;
			CEILING_COLOR[1] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			line++;
			CEILING_COLOR[2] = ft_atoi(line);
			continue;
		}
	}
	printf("RENDER_X: %d  RENDER_Y:%d\n", RENDER_X, RENDER_Y);
	printf("TEXTURE_NORTH: %s\n", TEXTURE_NORTH);
	printf("TEXTURE_SOUTH: %s\n", TEXTURE_SOUTH);
	printf("TEXTURE_WEST: %s\n", TEXTURE_WEST);
	printf("TEXTURE_EAST: %s\n", TEXTURE_EAST);
	printf("TEXTURE_SPRITE: %s\n", TEXTURE_SPRITE);
	printf("FLOOR_COLOR [R: %d, G: %d, B: %d]\n", FLOOR_COLOR[0], FLOOR_COLOR[1], FLOOR_COLOR[2]);
	printf("CEILING_COLOR [R: %d, G: %d, B: %d]\n", CEILING_COLOR[0], CEILING_COLOR[1], CEILING_COLOR[2]);
	
}