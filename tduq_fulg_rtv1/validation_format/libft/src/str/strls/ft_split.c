/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:57 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

static int	ft_in_charset(char c, const char *charset)
{
	int i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

static int	ft_str_word_nb(const char *str, const char *sep_chars)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_in_charset(str[i], sep_chars))
			i++;
		if (str[i] == '\0')
			return (count);
		count++;
		while (!ft_in_charset(str[i], sep_chars) && str[i])
			i++;
	}
	return (count);
}

static int	ft_sing_word_lett_count(const char *str, int ws, const char *seps)
{
	int i;

	i = 0;
	while (!ft_in_charset(str[ws + i], seps) && str[ws + i])
		i++;
	return (i);
}

char		**ft_split(const char *str, const char *sep_chars)
{
	int		i;
	int		j;
	int		wstart;
	int		len;
	char	**strls;

	if (!str || !sep_chars || !(strls = (char**)malloc(
					sizeof(char*) * (ft_str_word_nb(str, sep_chars) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_str_word_nb(str, sep_chars))
	{
		while (ft_in_charset(str[j], sep_chars))
			j++;
		wstart = j--;
		len = ft_sing_word_lett_count(str, wstart, sep_chars);
		if (!(strls[i] = (char*)malloc(len + 1)))
			return (NULL);
		while (++j < wstart + len)
			strls[i][j - wstart] = str[j];
		strls[i++][j - wstart] = '\0';
	}
	strls[i] = 0;
	return (strls);
}
