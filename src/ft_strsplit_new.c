/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 15:18:03 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/05/13 14:53:32 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		ft_count_words(const char *s)
{
	int		nb;

	nb = 0;
	while (*s != '\0')
	{
		while ((*s == ' ' || *s == '\t') && *s != '\0')
			s++;
		while (*s != ' ' && *s != '\t' && *s != '\0')
			s++;
		if (*s == ' ' || *s == '\t'
		|| (*s == '\0' && *(s - 1) != ' ' && *(s - 1) != '\t'))
			nb++;
	}
	return (nb);
}

static char		*ft_mall_word(const char *s)
{
	int			size;
	char		*word;
	int			i;

	size = 0;
	i = 0;
	while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
	{
		size++;
		i++;
	}
	word = ft_strnew(size + 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char		**ft_clean_array(char **ptr_words, int i)
{
	while (i >= 0)
		free(ptr_words[i--]);
	free(ptr_words);
	return (NULL);
}

static char		**ft_fill_array(char **ptr_words, const char *s)
{
	int			i;

	i = 0;
	while (*s != '\0')
	{
		while ((*s == ' ' || *s == '\t') && *s != '\0')
			s++;
		if (*s != ' ' && *s != '\t' && *s != '\0')
		{
			if (!(ptr_words[i] = ft_mall_word(s)))
				return (ft_clean_array(ptr_words, i));
			i++;
			while (*s != ' ' && *s != '\t' && *s != '\0')
				s++;
		}
	}
	ptr_words[i] = NULL;
	return (ptr_words);
}

char			**ft_strsplit_new(char const *s)
{
	char		**ptr_words;
	int			nb;

	if (!s)
		return (NULL);
	nb = ft_count_words(s);
	ptr_words = (char**)malloc(sizeof(char*) * (nb + 1));
	if (ptr_words == NULL)
		return (NULL);
	return (ft_fill_array(ptr_words, s));
}
