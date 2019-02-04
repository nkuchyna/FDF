/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 21:21:47 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/16 15:32:57 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_paral_move(t_image *img, int key)
{
	if (key == 123)
		img->dxt -= 50;
	else if (key == 124)
		img->dxt += 50;
	else if (key == 125)
		img->dyt += 50;
	else if (key == 126)
		img->dyt -= 50;
}

void		ft_rotation_move(t_image *img, int key)
{
	if (key == 13)
		img->a += 0.1;
	if (key == 1)
		img->a -= 0.1;
	if (key == 2)
		img->q += 0.1;
	if (key == 0)
		img->q -= 0.1;
	if (key == 6)
		img->w += 0.1;
	if (key == 50)
		img->w -= 0.1;
}

void		ft_scale_transform(t_image *img, int key)
{
	if (key == 69 && img->kt != 20)
		img->kt += 1;
	if (key == 78 && img->kt != 1)
		img->kt -= 1;
}

void		ft_transform(t_image *img, int key)
{
	t_points	*s_ar;

	s_ar = img->s_array;
	if (key == 123 || key == 124 || key == 125 || key <= 126)
		ft_paral_move(img, key);
	if (key == 13 || key == 0 || key == 1 || key == 2 || key == 6 || key == 50)
		ft_rotation_move(img, key);
	if (key == 69 || key == 78)
		ft_scale_transform(img, key);
	if (key == 8)
	{
		if (img->change_color == 0 && img->color_was_changed == 0)
		{
			img->change_color = 1;
			ft_fill_change_color_initial(s_ar, img->len);
			ft_change_color_adv(s_ar, img->len, img);
		}
		else if (img->change_color == 0 && img->color_was_changed == 1)
			img->change_color = 1;
		else if (img->change_color == 1)
			img->change_color = 0;
	}
}

int			ft_key_action(int key, t_window *win)
{
	t_image		*img;
	t_points	*s_ar;

	img = win->img;
	s_ar = img->s_array;
	if (key == 53)
	{
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		exit(1);
		return (0);
	}
	ft_transform(img, key);
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	ft_clear_str(img->img_str, img->bpl * win->size);
	ft_scale_img(s_ar, img, win);
	ft_img_projection(s_ar, img);
	ft_centre_img(s_ar, img, win->size / 2, win->size / 2);
	ft_shift_transf_coordinates(s_ar, img);
	ft_fill_img_str(img->img_str, s_ar, img->len, img);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->img_ptr, 0, 0);
	return (0);
}
