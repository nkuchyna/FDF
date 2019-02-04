/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_s_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:48:08 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/13 19:57:10 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_hex_dec(char c)
{
	int		nbr;

	nbr = 0;
	if (c >= '0' && c <= '9')
		nbr = c - '0';
	else if (c >= 'A' && c <= 'F')
		nbr = 10 + c - 'A';
	else if (c >= 'a' && c <= 'f')
		nbr = 10 + c - 'a';
	return (nbr);
}

static void	ft_color_variations(char *str, t_points *s_ar, int k, int len)
{
	if (len == 8)
	{
		s_ar[k].red = ft_hex_dec(str[2]) * 16 + ft_hex_dec(str[3]);
		s_ar[k].green = ft_hex_dec(str[4]) * 16 + ft_hex_dec(str[5]);
		s_ar[k].blue = ft_hex_dec(str[6]) * 16 + ft_hex_dec(str[7]);
	}
	else if (len == 5)
	{
		s_ar[k].red = ft_hex_dec(str[2]) * 16 + ft_hex_dec(str[2]);
		s_ar[k].green = ft_hex_dec(str[3]) * 16 + ft_hex_dec(str[3]);
		s_ar[k].blue = ft_hex_dec(str[4]) * 16 + ft_hex_dec(str[4]);
	}
	else if (len == 6)
	{
		s_ar[k].red = 0;
		s_ar[k].green = ft_hex_dec(str[2]) * 16 + ft_hex_dec(str[4]);
		s_ar[k].blue = ft_hex_dec(str[5]) * 16 + ft_hex_dec(str[6]);
	}
	else if (len == 4)
	{
		s_ar[k].red = 0;
		s_ar[k].green = 0;
		s_ar[k].blue = ft_hex_dec(str[2]) * 16 + ft_hex_dec(str[3]);
	}
}

static void	ft_divide_in_color_comp(char *str, t_points *s_ar, int k)
{
	int		len;

	if (str == NULL)
	{
		s_ar[k].red = 255;
		s_ar[k].green = 255;
		s_ar[k].blue = 255;
		return ;
	}
	len = ft_strlen(str);
	ft_color_variations(str, s_ar, k, len);
}

static void	ft_add_color(t_points *s_ar, int k, char *str)
{
	int		i;

	i = 0;
	if (s_ar[k].valid_color == 0)
		s_ar[k].color = "0xFFFFFF";
	else if (s_ar[k].valid_color < 0)
		s_ar[k].color = "0x000000";
	else if (s_ar[k].valid_color > 0)
	{
		while (str[i] != ',' && str[i] != '\0')
			i++;
		i++;
		s_ar[k].color = ft_strsub(str, i, ft_strlen(str) - i);
	}
	ft_divide_in_color_comp(s_ar[k].color, s_ar, k);
}

int			ft_fill_s_array(t_points *s_ar, char **nbrs, int *line_nbr, int *k)
{
	int		i;

	i = 0;
	if (nbrs == NULL)
		return (1);
	while (nbrs[i] != NULL)
	{
		s_ar[(*k)].x = i + 1;
		s_ar[(*k)].z = ft_atoi(nbrs[i]);
		s_ar[(*k)].y = *line_nbr + 1;
		ft_add_color(s_ar, (*k), nbrs[i]);
		s_ar[(*k)].xt = s_ar[(*k)].x;
		s_ar[(*k)].yt = s_ar[(*k)].y;
		(*k)++;
		i++;
	}
	(*line_nbr)++;
	ft_free_char_array(nbrs);
	return (0);
}
