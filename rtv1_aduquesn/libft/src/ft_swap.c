/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:08 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/15 02:08:08 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_swap_8b(t_u8 *ptr1, t_u8 *ptr2)
{
	t_u8 tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static void	ft_swap_16b(t_u16 *ptr1, t_u16 *ptr2)
{
	t_u16 tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static void	ft_swap_32b(t_u32 *ptr1, t_u32 *ptr2)
{
	t_u32 tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static void	ft_swap_64b(t_u64 *ptr1, t_u64 *ptr2)
{
	t_u64 tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

int			ft_swap(void *ptr1, void *ptr2, size_t size)
{
	if (ptr1 && ptr2)
	{
		if (size <= 1)
			ft_swap_8b((t_u8 *)ptr1, (t_u8 *)ptr2);
		else if (size <= 2)
			ft_swap_16b((t_u16 *)ptr1, (t_u16 *)ptr2);
		else if (size <= 4)
			ft_swap_32b((t_u32 *)ptr1, (t_u32 *)ptr2);
		else if (size <= 8)
			ft_swap_64b((t_u64 *)ptr1, (t_u64 *)ptr2);
		else
			return (ERROR);
		return (OK);
	}
	return (ERROR);
}
