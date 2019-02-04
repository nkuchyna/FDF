/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_color_adv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:04:19 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/15 12:56:13 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_find_diff_extr_heigth(t_points *s_ar, int size)
{
	int		i;
	int		z_max;
	int		z_min;

	i = 0;
	z_max = 0;
	z_min = 0;
	while (i + 1 < size)
	{
		if (s_ar[i].z >= 0)
		{
			if (s_ar[i + 1].z > z_max)
				z_max = s_ar[i + 1].z;
			if (s_ar[i + 1].z < z_min && s_ar[i + 1].z > 0)
				z_min = s_ar[i + 1].z;
		}
		i++;
	}
	return (z_max - z_min);
}

void	ft_find_heigth_diff_step(t_points *s_ar, int size, t_image *img)
{
	int		i;
	int		dz;
	int		colors;

	i = 0;
	colors = 1;
	dz = ft_find_diff_extr_heigth(s_ar, size);
	if (dz == 0 || dz == 1)
	{
		img->step_z = dz;
		img->colors = dz;
		return ;
	}
	while (dz / colors-- != 0)
	{
		if (colors > 5)
			break ;
		colors += 2;
	}
	img->step_z = dz / colors;
	img->colors = colors;
}

int		ft_find_color_step(int colors)
{
	int		step_c;

	if (colors == 1)
		step_c = 255;
	else if (colors == 0)
		step_c = 0;
	else
		step_c = 255 / colors * 2;
	return (step_c);
}

void	ft_set_change_color(t_points *s_ar, int i, int step_c, t_image *img)
{
	int		step_z;
	int		z;

	step_z = img->step_z;
	z = s_ar[i].z;
	if (s_ar[i].z > 0 && s_ar[i].z <= step_z * 6)
	{
		if (z <= step_z)
			s_ar[i].red_t = step_c;
		else if (img->colors > 1 && z > step_z && z <= step_z * 2)
			s_ar[i].red_t = step_c * 2;
		else if (img->colors > 2 && z > step_z * 2 && z <= step_z * 3)
			s_ar[i].red_t = step_c * 3;
		else if (img->colors > 3 && z > step_z * 3 && z <= step_z * 4)
			s_ar[i].green_t = step_c * 3;
		else if (img->colors > 4 && z > step_z * 4 && z <= step_z * 5)
			s_ar[i].green_t = step_c * 2;
		else if (img->colors > 5 && z > step_z * 5 && z <= step_z * 6)
			s_ar[i].green_t = step_c;
	}
}

void	ft_change_color_adv(t_points *s_ar, int size, t_image *img)
{
	int		step_c;
	int		i;

	i = -1;
	ft_find_heigth_diff_step(s_ar, size, img);
	step_c = ft_find_color_step(img->colors);
	while (++i < size)
	{
		ft_set_change_color(s_ar, i, step_c, img);
		if (s_ar[i].z == 0)
			s_ar[i].red_t = 0;
		else if (s_ar[i].z < 0)
		{
			s_ar[i].red_t = 0;
			s_ar[i].green_t = 0;
			s_ar[i].blue_t = 255;
		}
		else if (s_ar[i].z > img->step_z * 5)
			s_ar[i].green_t = 0;
	}
}
