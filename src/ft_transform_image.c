/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 20:49:54 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/31 15:58:08 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_centre_img(t_points *s_ar, t_image *img, int x, int y)
{
	int			dx;
	int			dy;
	int			i;
	int			xo;
	int			yo;

	i = 0;
	if (s_ar == NULL || img->len <= 0)
		return ;
	xo = (s_ar[img->width - 1].x + s_ar[0].x) / 2;
	yo = (s_ar[(img->width - 1) * img->heigth].y + s_ar[0].y) / 2;
	dx = x - xo;
	dy = y - yo;
	while (i < img->len)
	{
		s_ar[i].xt += dx;
		s_ar[i].yt += dy;
		i++;
	}
}

void		ft_scale_img(t_points *s_ar, t_image *img, t_window *win)
{
	int		i;
	int		k;

	i = 0;
	k = 1;
	if (img->width > img->heigth && img->width != 0)
		k = win->size * img->kt / 10 / img->width;
	else
	{
		if (img->heigth != 0)
			k = win->size * img->kt / 10 / img->heigth;
	}
	if (k == 0)
		return ;
	while (i < img->len)
	{
		s_ar[i].x = s_ar[i].x / img->k * k;
		s_ar[i].y = s_ar[i].y / img->k * k;
		s_ar[i].z = s_ar[i].z / img->k * k;
		i++;
	}
	img->k = k;
}

void		ft_shift_transf_coordinates(t_points *s_ar, t_image *img)
{
	int		i;

	i = 0;
	if (img->dxt == 0 && img->dyt == 0)
		return ;
	while (i < img->len)
	{
		s_ar[i].xt += img->dxt;
		s_ar[i].yt += img->dyt;
		i++;
	}
}

static void	ft_spatial_to_flat(t_image *img, int i, int xo, int yo)
{
	int			y;
	int			z;
	int			x1;
	int			z1;
	t_points	*s_ar;

	s_ar = img->s_array;
	y = yo + (s_ar[i].y - yo) * cos(img->a) + (s_ar[i].z - 1) * sin(img->a);
	z = 1 + (s_ar[i].z - 1) * cos(img->a) - (s_ar[i].y - yo) * sin(img->a);
	x1 = xo + (s_ar[i].x - xo) * cos(img->q) + (z - 1) * sin(img->q);
	s_ar[i].xt = xo + (x1 - xo) * cos(img->w) + (y - yo) * sin(img->w);
	s_ar[i].yt = yo - (x1 - xo) * sin(img->w) + (y - yo) * cos(img->w);
}

void		ft_img_projection(t_points *s_ar, t_image *img)
{
	int		xo;
	int		yo;
	int		zo;
	int		i;

	i = 0;
	xo = (s_ar[img->width - 1].x + s_ar[0].x) / 2;
	yo = (s_ar[(img->width - 1) * img->heigth].y + s_ar[0].y) / 2;
	zo = 1;
	while (i < img->len)
	{
		ft_spatial_to_flat(img, i, xo, yo);
		i++;
	}
}
