/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_content_and_create_s_array.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 20:46:58 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/14 20:57:02 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		ft_check_nbr(char *str)
{
	long int		nbr;
	int				i;
	int				len;

	i = 0;
	len = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != ',' && str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		len++;
		i++;
	}
	if (len > 10 || (str[i - len] == '0' && len != 1))
		return (1);
	nbr = ft_atoi(str);
	if (!(nbr >= -2147483648 && nbr <= 2147483647))
		return (1);
	return (0);
}

static int		ft_check_color(char *str, int i)
{
	int		len;

	if ((len = ft_strlen(str) - i) != 8 && len != 5 && len != 6 && len != 4)
		return (1);
	if (!(str[i] == '0' && str[i + 1] == 'x'))
		return (1);
	i += 2;
	while (str[i] != '\0')
	{
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f')
			|| (str[i] >= 'A' && str[i] <= 'F'))
			i++;
		else
			return (1);
	}
	return (0);
}

static int		ft_check_numbers_and_color(char *str, t_points *s_array, int k)
{
	int			i;

	i = 0;
	if (ft_check_nbr(str) == 1)
		return (1);
	while (str[i] != ',' && str[i] != '\0')
		i++;
	if (str[i] == ',')
	{
		if (ft_check_color(str, i + 1) != 1)
			s_array[k].valid_color = i + 1;
		else
			s_array[k].valid_color = -1;
	}
	if (str[i] == '\0')
		s_array[k].valid_color = 0;
	return (0);
}

static char		**ft_check_content(char *str, t_points *s_ar, int k)
{
	int			i;
	char		**numbers;

	i = 0;
	if (!(numbers = ft_strsplit_new(str)))
		return (NULL);
	while (numbers[i])
	{
		if (ft_check_numbers_and_color(numbers[i], s_ar, k) == 1)
		{
			s_ar[k].invalid_nbr = 1;
			s_ar[k].valid_color = -1;
		}
		else
			s_ar[k].invalid_nbr = 0;
		i++;
		k++;
	}
	return (numbers);
}

t_points		*ft_check_content_and_create_s_array(int size, char *argv)
{
	int			fd;
	t_points	*s_ar;
	char		*line;
	int			k;
	int			line_nbr;

	line = NULL;
	k = 0;
	line_nbr = 0;
	fd = open(argv, O_RDWR);
	if (!(s_ar = (t_points*)malloc(sizeof(t_points) * size)))
		return (NULL);
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_fill_s_array(s_ar, ft_check_content(line, s_ar, k),
							&line_nbr, &k) == 1)
			return (NULL);
		free(line);
		line = NULL;
	}
	if (get_next_line(fd, &line) == -1)
		return (NULL);
	close(fd);
	return (s_ar);
}
