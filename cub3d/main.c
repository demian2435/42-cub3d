/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:38:52 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/14 11:17:48 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_start_game(t_system *sys)
{
	sys->mlx_vars.win = mlx_new_window(sys->mlx_vars.mlx,
		sys->cub.res_x, sys->cub.res_y, "Cub3D D2435");
	mlx_do_key_autorepeaton(sys->mlx_vars.mlx);
	mlx_hook(sys->mlx_vars.win, 2, 0x1, ft_key_press, sys);
	mlx_hook(sys->mlx_vars.win, 3, 0x2, ft_key_release, sys);
	mlx_hook(sys->mlx_vars.win, 17, 0, ft_key_exit, sys);
	mlx_loop_hook(sys->mlx_vars.mlx, ft_next_frame, sys);
	mlx_loop(sys->mlx_vars.mlx);
}

void	ft_init_system(t_system *sys)
{
	sys->mlx_vars.mlx = mlx_init();
	sys->cub.res_x = -1;
	sys->cub.res_y = -1;
	sys->cub.f_rgb[0] = -1;
	sys->cub.f_rgb[1] = -1;
	sys->cub.f_rgb[2] = -1;
	sys->cub.c_rgb[0] = -1;
	sys->cub.c_rgb[1] = -1;
	sys->cub.c_rgb[2] = -1;
	sys->cub.map_w = -1;
	sys->cub.map_h = -1;
	sys->player.pos_x = -1;
	sys->player.pos_y = -1;
	sys->max_x = 2560;
	sys->max_y = 1600;
}

void	ft_parse_cub(int fd, t_system *sys)
{
	t_list	*list_map_temp;
	int		i;

	ft_parse_cub_bis(fd, sys);
	list_map_temp = sys->parse.list_map;
	sys->cub.map_h = ft_lstsize(list_map_temp);
	sys->cub.map_w = ft_mapmaxwidth(list_map_temp);
	if ((sys->cub.map = (char **)malloc((sys->cub.map_h + 1) *
		sizeof(char *))) == NULL)
		ft_exception("Malloc fail during map creation (step 1)", sys);
	i = 0;
	while (list_map_temp)
	{
		if ((sys->cub.map[i] = ft_strndupfill(list_map_temp->content,
			sys->cub.map_w, ' ')) == NULL)
			ft_exception("Malloc fail during map creation (step 2)", sys);
		list_map_temp = list_map_temp->next;
		i++;
	}
	sys->cub.map[i] = NULL;
	ft_lstclear(&sys->parse.list_map, free);
	ft_control_errors(sys);
}

int		main(int argc, char **argv)
{
	t_system	sys;
	int			fd;

	if (argc == 1 || argc > 3)
	{
		ft_printf("Error\nWrong number arguments\n");
		exit(0);
	}
	ft_memset(&sys, 0, sizeof(t_system));
	ft_init_system(&sys);
	if (!sys.mlx_vars.mlx)
		ft_exception("Mlx failed start", &sys);
	if (!ft_istypefile(argv[1], ".cub"))
		ft_exception("Not .cub file selected", &sys);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exception("Insert a valid .cub file", &sys);
	ft_parse_cub(fd, &sys);
	if (close(fd) == -1)
		ft_exception("Can't close cub file", &sys);
	if (argc == 3)
		ft_start_save(argv[2], &sys);
	ft_start_game(&sys);
	return (0);
}
