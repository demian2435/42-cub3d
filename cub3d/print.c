/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:26:44 by d2435             #+#    #+#             */
/*   Updated: 2021/02/12 23:26:45 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_pixel_exa(int x, int y, int color, t_system *sys)
{
	char	*dst;

	dst = sys->frame.addr + (y * sys->frame.line_len +
		x * (sys->frame.bpp / 8));
	*(unsigned int *)dst = color;
}

int		ft_convert_color(int r, int g, int b)
{
	return ((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff);
}

void	ft_skip_spaces(t_system *sys)
{
	while (ft_isspace(*sys->parse.line))
		sys->parse.line++;
}
