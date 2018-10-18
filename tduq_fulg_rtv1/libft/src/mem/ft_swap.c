/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:03 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:49 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

static void		ft_swap_t_u8(t_u8 *a, t_u8 *b)
{
	t_u8 c;

	c = *a;
	*a = *b;
	*b = c;
}

static void		ft_swap_u16(t_u16 *a, t_u16 *b)
{
	t_u16 c;

	c = *a;
	*a = *b;
	*b = c;
}

static void		ft_swap_t_u32(t_u32 *a, t_u32 *b)
{
	t_u32 c;

	c = *a;
	*a = *b;
	*b = c;
}

static void		ft_swap_u64(t_u64 *a, t_u64 *b)
{
	t_u64 c;

	c = *a;
	*a = *b;
	*b = c;
}

int				ft_swap(void *a, void *b, size_t sizeof_ab)
{
	if (!a || !b)
		return (ERROR);
	if (sizeof_ab == 1)
		ft_swap_t_u8(a, b);
	else if (sizeof_ab == 2)
		ft_swap_u16(a, b);
	else if (sizeof_ab == 4)
		ft_swap_t_u32(a, b);
	else if (sizeof_ab == 8)
		ft_swap_u64(a, b);
	else
		return (ERROR);
	return (OK);
}
