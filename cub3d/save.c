/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:26:40 by d2435             #+#    #+#             */
/*   Updated: 2021/02/12 23:26:41 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_start_save(char *str, t_system *sys)
{
	if (!ft_strcmp(str, "--save"))
		ft_save_frame(sys);
	else
		ft_exception("Command not found", sys);
	ft_key_exit(sys);
}

void	ft_save_frame(t_system *sys)
{
	int				fd;
	int				i;
	unsigned int	*line;
	t_bmp			bmp;

	sys->save = 1;
	ft_next_frame(sys);
	ft_memset(&bmp, 0, sizeof(t_bmp));
	ft_init_bpm(sys, &bmp);
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		ft_exception("Can't open/create screenshot file", sys);
	ft_write_on_file(sys, fd, "BM", 2);
	ft_write_on_file(sys, fd, &bmp, sizeof(t_bmp));
	i = 0;
	while (i < sys->cub.res_y)
	{
		line = (unsigned int *)&sys->frame.addr[(sys->cub.res_y - i++ - 1) *
			sys->frame.line_len];
		ft_write_on_file(sys, fd, line, sys->frame.line_len);
	}
	if (close(fd) == -1)
		ft_exception("Can't close bmp file", sys);
	mlx_destroy_image(sys->mlx_vars.mlx, sys->frame.img);
}

void	ft_write_on_file(t_system *sys, int fd, const void *buf, ssize_t len)
{
	if (write(fd, buf, len) != len)
		ft_exception("Fail write on bmp file", sys);
}

void	ft_init_bpm(t_system *sys, t_bmp *bmp)
{
	bmp->tot_size = (sys->cub.res_x * sys->cub.res_y *
		(sys->frame.bpp / 8)) + 54;
	bmp->pixel_offset = 54;
	bmp->h_size = 40;
	bmp->w = sys->cub.res_x;
	bmp->h = sys->cub.res_y;
	bmp->planes = 1;
	bmp->bpp = sys->frame.bpp;
	bmp->img_size = sys->cub.res_x * sys->cub.res_y * (sys->frame.bpp / 8);
}

int		ft_mapmaxwidth(t_list *list_map)
{
	size_t max;

	max = 0;
	while (list_map)
	{
		if (ft_strlen(list_map->content) > max)
			max = ft_strlen(list_map->content);
		list_map = list_map->next;
	}
	return ((int)max);
}
