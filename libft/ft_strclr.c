/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:42:49 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/04/02 16:41:30 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *s)
{
	int		i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
		s[i++] = '\0';
}