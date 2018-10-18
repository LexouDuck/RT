/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlsjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 12:50:11 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

static void	ft_strnb_charnb_in_strls(const char **strls, int *w_nb, int *c_nb)
{
	int str_at;

	str_at = 0;
	while (strls[str_at])
	{
		*(c_nb) += ft_strlen(strls[str_at]);
		str_at++;
	}
	*w_nb = str_at;
}

static void	ft_build_str(char *dest, char const **strls, char const *sep)
{
	int i;
	int words;
	int chars;
	int sep_i;

	i = 0;
	sep_i = 0;
	words = -1;
	while (strls[++words])
	{
		chars = 0;
		while (strls[words][chars])
			dest[i++] = strls[words][chars++];
		sep_i = 0;
		while (sep[sep_i] && strls[words + 1])
			dest[i++] = sep[sep_i++];
	}
	dest[i] = '\0';
}

char		*ft_strlsjoin(char const **strls, char const *sep)
{
	char	*str;
	int		strls_str_nb;
	int		strls_char_nb;
	int		total_sep_char_nb;
	int		total_char_nb;

	if (!strls || !sep)
		return (NULL);
	strls_str_nb = 0;
	strls_char_nb = 0;
	ft_strnb_charnb_in_strls(strls, &strls_str_nb, &strls_char_nb);
	total_sep_char_nb = (strls_str_nb - 1) * ft_strlen(sep);
	total_char_nb = total_sep_char_nb + strls_char_nb;
	if (!(str = ft_strnew(total_char_nb + 1)))
		return (NULL);
	ft_build_str(str, strls, sep);
	return (str);
}
