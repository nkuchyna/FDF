/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_img_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:07:54 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/31 15:28:52 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_build_grad_point(t_image *img, int i)
{
	t_points	*s_ar;
	int			k1;
	int			k2;
	int			iter;

	k1 = img->k1;
	k2 = img->k2;
	iter = img->grad_iter;
	s_ar = img->s_array;
	img->img_str[i] = s_ar[k1].blue_t +
		(s_ar[k2].blue_t - s_ar[k1].blue_t) * iter / img->len_grad;
	img->img_str[++i] = s_ar[k1].green_t +
		(s_ar[k2].green_t - s_ar[k1].green_t) * iter / img->len_grad;
	img->img_str[++i] = s_ar[k1].red_t +
		(s_ar[k2].red_t - s_ar[k1].red_t) * iter / img->len_grad;
	img->grad_iter++;
}

void		ft_build_point(int k, t_image *img, int x, int y)
{
	int			i;
	t_points	*s_ar;

	if (x > 0 && x < 1000 && y > 0 && y < 1000)
	{
		i = y * img->bpl - img->bpl + x * 4 - 4;
		if (img->change_color == 1)
			ft_build_grad_point(img, i);
		else
		{
			s_ar = img->s_array;
			img->img_str[i] = s_ar[k].blue;
			img->img_str[++i] = s_ar[k].green;
			img->img_str[++i] = s_ar[k].red;
		}
	}
}

static void	ft_fill_color(char *str, int i, t_image *img, int k)
{
	t_points	*s_ar;

	s_ar = img->s_array;
	if (img->change_color == 0)
	{
		str[i] = s_ar[k].blue;
		str[++i] = s_ar[k].green;
		str[++i] = s_ar[k].red;
	}
	else
	{
		str[i] = s_ar[k].blue_t;
		str[++i] = s_ar[k].green_t;
		str[++i] = s_ar[k].red_t;
	}
}

void		ft_fill_img_str(char *str, t_points *s_ar, int size, t_image *img)
{
	int		i;
	int		k;
	int		width;

	i = 0;
	k = 0;
	width = img->bpl / 4;
	while (k < size)
	{
		if (s_ar[k].yt >= 0 && s_ar[k].yt < 1000
		&& s_ar[k].xt >= 0 && s_ar[k].xt < 1000)
		{
			i = s_ar[k].yt * img->bpl + s_ar[k].xt * 4;
			ft_fill_color(str, i, img, k);
		}
		k++;
	}
	ft_build_lines(s_ar, img);
}
