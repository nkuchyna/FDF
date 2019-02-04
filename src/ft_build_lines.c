/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 15:05:24 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/14 18:32:44 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_build_line_iter_x(t_points *s_ar, int i1, int i2, t_image *img)
{
	int		len;
	int		d;
	int		x;
	int		y;

	x = s_ar[i1].xt;
	y = s_ar[i1].yt;
	len = img->lenx;
	d = -img->lenx;
	while (len > 0)
	{
		if (s_ar[i1].z > s_ar[i2].z || img->change_color == 1)
			ft_build_point(i1, img, x, y);
		else
			ft_build_point(i2, img, x, y);
		x += img->dx;
		d += 2 * img->leny;
		if (d > 0)
		{
			d -= 2 * img->lenx;
			y += img->dy;
		}
		len--;
	}
}

void		ft_build_line_iter_y(t_points *s_ar, int i1, int i2, t_image *img)
{
	int		len;
	int		d;
	int		x;
	int		y;

	x = s_ar[i1].xt;
	y = s_ar[i1].yt;
	len = img->leny;
	d = -img->leny;
	while (len > 0)
	{
		if (s_ar[i1].z > s_ar[i2].z || img->change_color == 1)
			ft_build_point(i1, img, x, y);
		else
			ft_build_point(i2, img, x, y);
		y += img->dy;
		d += 2 * img->lenx;
		if (d > 0)
		{
			d -= 2 * img->leny;
			x += img->dx;
		}
		len--;
	}
}

void		ft_fill_img_by_lines(t_points *s_ar, int i1, int i2, t_image *img)
{
	int		len;
	int		x;
	int		y;

	img->dx = (s_ar[i2].xt - s_ar[i1].xt >= 0 ? 1 : -1);
	img->dy = (s_ar[i2].yt - s_ar[i1].yt >= 0 ? 1 : -1);
	img->lenx = ft_abs(s_ar[i2].xt - s_ar[i1].xt);
	img->leny = ft_abs(s_ar[i2].yt - s_ar[i1].yt);
	img->k1 = i1;
	img->k2 = i2;
	img->len_grad = sqrt(pow((s_ar[i2].xt - s_ar[i1].xt), 2)
					+ pow((s_ar[i2].yt - s_ar[i1].yt), 2));
	img->grad_iter = 1;
	if (img->lenx > img->leny)
		len = img->lenx;
	else
		len = img->leny;
	x = s_ar[i1].xt;
	y = s_ar[i1].yt;
	if (img->leny <= img->lenx)
		ft_build_line_iter_x(s_ar, i1, i2, img);
	else
		ft_build_line_iter_y(s_ar, i1, i2, img);
}

void		ft_build_lines(t_points *s_ar, t_image *img)
{
	int		i;

	i = 0;
	while (i < img->len)
	{
		if (s_ar[i].line_conect == 'H')
			ft_fill_img_by_lines(s_ar, i, i + 1, img);
		else if (s_ar[i].line_conect == 'V')
			ft_fill_img_by_lines(s_ar, i, i + img->width, img);
		else if (s_ar[i].line_conect == 'B')
		{
			ft_fill_img_by_lines(s_ar, i, i + 1, img);
			ft_fill_img_by_lines(s_ar, i, i + img->width, img);
		}
		i++;
	}
}
