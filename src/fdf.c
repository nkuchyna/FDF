/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 12:56:18 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/31 16:06:50 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_window	*ft_create_wndw_info(void)
{
	void		*mlx_ptr;
	t_window	*new_window;

	if (!(mlx_ptr = mlx_init()))
		return (NULL);
	new_window = (t_window*)malloc(sizeof(t_window) * 1);
	new_window->mlx_ptr = mlx_ptr;
	new_window->win_ptr = NULL;
	new_window->size = 1000;
	return (new_window);
}

static t_image	*ft_create_img_info(void)
{
	t_image		*img;

	if (!(img = (t_image*)malloc(sizeof(t_image) * 1)))
		return (NULL);
	img->img_ptr = NULL;
	img->img_str = NULL;
	img->width = 0;
	img->heigth = 0;
	img->k = 1;
	img->kt = 7;
	img->a = 0;
	img->q = 0;
	img->w = 0;
	img->dxt = 0;
	img->dyt = 0;
	img->dx = 0;
	img->dy = 0;
	img->bpp = 0;
	img->bpl = 0;
	img->end = 0;
	img->change_color = 0;
	img->color_was_changed = 0;
	return (img);
}

static int		ft_create_window(t_window *wndw_info, int len, int heigth)
{
	void	*win_ptr;

	if (!(win_ptr = mlx_new_window(wndw_info->mlx_ptr, len, heigth, "-FdF-")))
		return (1);
	wndw_info->win_ptr = win_ptr;
	return (0);
}

static int		ft_create_img(t_image *img, t_window *win)
{
	int		k;
	void	*img_ptr;

	k = 1;
	img_ptr = mlx_new_image(win->mlx_ptr, win->size, win->size);
	img->img_ptr = img_ptr;
	img->img_str = mlx_get_data_addr(img_ptr, &img->bpp, &img->bpl, &img->end);
	win->img = img;
	return (0);
}

int				main(int argc, char **argv)
{
	t_window	*win;
	t_points	*s_array;
	t_image		*img;

	if (argc != 2)
	{
		ft_putstr("usage: fdf [file]\n");
		return (1);
	}
	win = ft_create_wndw_info();
	img = ft_create_img_info();
	if (!win || !img || !(s_array = ft_map_processing(argv[1], img)))
		return (1);
	if (ft_create_window(win, win->size, win->size) == 1
	|| ft_create_img(img, win) == 1)
		return (1);
	ft_scale_img(s_array, img, win);
	ft_img_projection(s_array, img);
	ft_centre_img(s_array, img, win->size / 2, win->size / 2);
	ft_fill_img_str(img->img_str, s_array, img->len, img);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->img_ptr, 0, 0);
	mlx_hook(win->win_ptr, 2, 5, ft_key_action, win);
	mlx_hook(win->win_ptr, 17, 1L << 17, ft_exit_x, win);
	mlx_loop(win->mlx_ptr);
	return (0);
}
