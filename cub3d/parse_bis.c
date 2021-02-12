/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:27:09 by d2435             #+#    #+#             */
/*   Updated: 2021/02/12 23:27:10 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_texture_n(t_system *sys)
{
	if (sys->parse.line[0] == 'N' && sys->parse.line[1] == 'O' &&
		ft_isspace(sys->parse.line[2]) && !sys->parse.find)
	{
		if (sys->cub.txt_N.img != NULL)
			ft_exception("Duplicated north texture", sys);
		sys->parse.line += 2;
		ft_skip_spaces(sys);
		sys->cub.txt_N.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
			sys->parse.line, &sys->cub.txt_N.width, &sys->cub.txt_N.height);
		sys->parse.find = 1;
	}
}

void	ft_parse_texture_s(t_system *sys)
{
	if (sys->parse.line[0] == 'S' && sys->parse.line[1] == 'O' &&
		ft_isspace(sys->parse.line[2]) && !sys->parse.find)
	{
		if (sys->cub.txt_S.img != NULL)
			ft_exception("Duplicated south texture", sys);
		sys->parse.line += 2;
		ft_skip_spaces(sys);
		sys->cub.txt_S.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
			sys->parse.line, &sys->cub.txt_S.width, &sys->cub.txt_S.height);
		sys->parse.find = 1;
	}
}

void	ft_parse_texture_w(t_system *sys)
{
	if (sys->parse.line[0] == 'W' && sys->parse.line[1] == 'E' &&
		ft_isspace(sys->parse.line[2]) && !sys->parse.find)
	{
		if (sys->cub.txt_W.img != NULL)
			ft_exception("Duplicated west texture", sys);
		sys->parse.line += 2;
		ft_skip_spaces(sys);
		sys->cub.txt_W.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
			sys->parse.line, &sys->cub.txt_W.width, &sys->cub.txt_W.height);
		sys->parse.find = 1;
	}
}

void	ft_parse_texture_e(t_system *sys)
{
	if (sys->parse.line[0] == 'E' && sys->parse.line[1] == 'A' &&
		ft_isspace(sys->parse.line[2]) && !sys->parse.find)
	{
		if (sys->cub.txt_E.img != NULL)
			ft_exception("Duplicated east texture", sys);
		sys->parse.line += 2;
		ft_skip_spaces(sys);
		sys->cub.txt_E.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
			sys->parse.line, &sys->cub.txt_E.width, &sys->cub.txt_E.height);
		sys->parse.find = 1;
	}
}

void	ft_parse_texture_spr(t_system *sys)
{
	if (sys->parse.line[0] == 'S' && ft_isspace(sys->parse.line[1]) &&
		!sys->parse.find)
	{
		if (sys->cub.txt_SPR.img != NULL)
			ft_exception("Duplicated sprite texture", sys);
		sys->parse.line++;
		ft_skip_spaces(sys);
		sys->cub.txt_SPR.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
			sys->parse.line, &sys->cub.txt_SPR.width, &sys->cub.txt_SPR.height);
		sys->parse.find = 1;
	}
}
