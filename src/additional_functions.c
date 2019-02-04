/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:42:17 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/14 18:37:42 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_fill_change_color_initial(t_points *s_ar, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		s_ar[i].red_t = 255;
		s_ar[i].green_t = 255;
		s_ar[i].blue_t = 0;
		i++;
	}
}

void		ft_clear_str(char *str, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		str[i] = '\0';
		i++;
	}
}

void		ft_free_char_array(char **array)
{
	int			k;

	k = 0;
	while (array[k])
	{
		free(array[k]);
		array[k] = NULL;
		k++;
	}
	free(array);
	array = NULL;
}

int			ft_exit_x(void)
{
	exit(1);
	return (0);
}

int			ft_abs(int nbr)
{
	(nbr < 0) ? (nbr *= -1) : (0);
	return (nbr);
}
