/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:38:54 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/31 15:54:56 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_count_elements(char *str)
{
	int			nb;
	int			i;

	nb = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
			i++;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
			i++;
		if (str[i] == ' ' || str[i] == '\t'
		|| (str[i] == '\0' && str[i - 1] != ' ' && str[i - 1] != '\t'))
			nb++;
	}
	return (nb);
}

static int	ft_check_lgth(int numbers_qty, char *line)
{
	int			current_numbers_qty;

	current_numbers_qty = ft_count_elements(line);
	if (current_numbers_qty != numbers_qty)
		return (1);
	return (0);
}

static int	ft_check_map(int fd, int *nbrs_qty, int *lines_qty)
{
	char		*line;

	line = NULL;
	if (get_next_line(fd, &line) == -1 || (line != NULL && !(ft_strlen(line))))
		return (1);
	if (line == NULL)
	{
		ft_putstr("No data found.\n");
		return (1);
	}
	*nbrs_qty = ft_count_elements(line);
	free(line);
	while (get_next_line(fd, &line) == 1)
	{
		(*lines_qty)++;
		if (ft_check_lgth(*nbrs_qty, line) == 1)
		{
			ft_putstr("Found wrong line length. Exiting.\n");
			return (1);
		}
		free(line);
		line = NULL;
	}
	return (0);
}

static void	ft_make_line_conect(t_points *s_ar, int size, int width, int heigth)
{
	int		k;

	k = 0;
	while (k < size)
	{
		if (s_ar[k].x != width && s_ar[k].y != heigth)
			s_ar[k].line_conect = 'B';
		else if (s_ar[k].x != width && s_ar[k].y == heigth)
			s_ar[k].line_conect = 'H';
		else if (s_ar[k].x == width && s_ar[k].y != heigth)
			s_ar[k].line_conect = 'V';
		else
			s_ar[k].line_conect = 'N';
		k++;
	}
}

t_points	*ft_map_processing(char *argv, t_image *img)
{
	int			fd;
	t_points	*s_array;
	int			lines_qty;
	int			nbrs_qty;

	lines_qty = 1;
	nbrs_qty = 0;
	if ((fd = open(argv, O_RDWR)) < 0)
	{
		ft_putstr(strerror(errno));
		ft_putstr("\nusage: fdf [file]\n");
		return (NULL);
	}
	if (ft_check_map(fd, &nbrs_qty, &lines_qty) == 1)
		return (NULL);
	close(fd);
	img->len = nbrs_qty * lines_qty;
	if (!(s_array = ft_check_content_and_create_s_array(img->len, argv)))
		return (NULL);
	ft_make_line_conect(s_array, img->len, nbrs_qty, lines_qty);
	img->s_array = s_array;
	img->width = nbrs_qty;
	img->heigth = lines_qty;
	return (s_array);
}
