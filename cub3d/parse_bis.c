#include "cub3d.h"

void ft_parse_texture_N(t_system *sys)
{
	if (sys->cub.txt_N.img != NULL)
		ft_exception("Duplicated north texture", sys);
	sys->parse.line += 2;
	ft_skip_spaces(sys);
	sys->cub.txt_N.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, sys->parse.line, &sys->cub.txt_N.width, &sys->cub.txt_N.height);
}

void ft_parse_texture_S(t_system *sys)
{
	if (sys->cub.txt_S.img != NULL)
		ft_exception("Duplicated south texture", sys);
	sys->parse.line += 2;
	ft_skip_spaces(sys);
	sys->cub.txt_S.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, sys->parse.line, &sys->cub.txt_S.width, &sys->cub.txt_S.height);
}

void ft_parse_texture_W(t_system *sys)
{
	if (sys->cub.txt_W.img != NULL)
		ft_exception("Duplicated west texture", sys);
	sys->parse.line += 2;
	ft_skip_spaces(sys);
	sys->cub.txt_W.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, sys->parse.line, &sys->cub.txt_W.width, &sys->cub.txt_W.height);
}

void ft_parse_texture_E(t_system *sys)
{
	if (sys->cub.txt_E.img != NULL)
		ft_exception("Duplicated east texture", sys);
	sys->parse.line += 2;
	ft_skip_spaces(sys);
	sys->cub.txt_E.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, sys->parse.line, &sys->cub.txt_E.width, &sys->cub.txt_E.height);
}

void ft_parse_texture_spr(t_system *sys)
{
	if (sys->cub.txt_SPR.img != NULL)
		ft_exception("Duplicated sprite texture", sys);
	sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.txt_SPR.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, sys->parse.line, &sys->cub.txt_SPR.width, &sys->cub.txt_SPR.height);
}
