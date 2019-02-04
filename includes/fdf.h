/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 20:04:08 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/14 21:55:31 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include "libft.h"
# include "mlx.h"
# include <math.h>

typedef struct		s_points
{
	int			x;
	int			y;
	int			z;
	int			xt;
	int			yt;
	char		line_conect;
	int			valid_color;
	int			invalid_nbr;
	char		*color;
	int			red;
	int			green;
	int			blue;
	int			red_t;
	int			green_t;
	int			blue_t;
}					t_points;

typedef struct		s_image
{
	t_points	*s_array;
	void		*img_ptr;
	char		*img_str;
	int			width;
	int			heigth;
	int			len;
	int			k;
	int			kt;
	float		a;
	float		q;
	float		w;
	int			dxt;
	int			dyt;
	int			dx;
	int			dy;
	int			lenx;
	int			leny;
	int			bpp;
	int			bpl;
	int			end;
	int			change_color;
	int			color_was_changed;
	int			step_z;
	int			colors;
	int			k1;
	int			k2;
	int			len_grad;
	int			grad_iter;
}					t_image;

typedef struct		s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			size;
	t_image		*img;
}					t_window;

void				ft_free_char_array(char **array);
void				ft_clear_str(char *str, int len);
int					ft_exit_x(void);
int					ft_abs(int nbr);
t_points			*ft_map_processing(char *argv, t_image *img_info);
t_points			*ft_check_content_and_create_s_array(int size, char *argv);
char				**ft_strsplit_new(char const *s);
int					ft_fill_s_array(t_points *s_ar, char **numbers,
									int *line_nbr, int *k);
void				ft_print_struct_array(t_points *s_array, int size);
void				ft_fill_img_str(char *str, t_points *s_ar,
									int size, t_image *img);
int					ft_key_action(int key, t_window *wndw);
void				ft_centre_img(t_points *s_ar, t_image *inf, int x, int y);
void				ft_scale_img(t_points *s_ar, t_image *inf, t_window *win);
void				ft_img_projection(t_points *s_ar, t_image *img);
void				ft_build_lines(t_points *s_ar, t_image *img);
void				ft_shift_transf_coordinates(t_points *s_ar, t_image *img);
void				ft_change_color_adv(t_points *s_ar, int size, t_image *img);
void				ft_fill_change_color_initial(t_points *s_ar, int size);
void				ft_build_grad_point(t_image *img, int i);
void				ft_build_point(int k, t_image *img, int x, int y);

#endif
