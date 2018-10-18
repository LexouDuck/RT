/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 21:32:01 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:22 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

/*
** ft_memalloc wipes memory with ft_bzero.
*/

char	*ft_strcnew(size_t size, char const c)
{
	char	*str;

	if (!(str = (char*)malloc(size + 1)))
		return (NULL);
	str[size] = '\0';
	ft_memset(str, c, size);
	return (str);
}
