/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/07 02:45:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_char.h"

inline int		ft_tolower(int c)
{
	return (('A' <= c && c <= 'Z') ?
		(c - 'A' + 'a') : c);
}

inline int		ft_toupper(int c)
{
	return (('a' <= c && c <= 'z') ?
		(c - 'a' + 'A') : c);
}
