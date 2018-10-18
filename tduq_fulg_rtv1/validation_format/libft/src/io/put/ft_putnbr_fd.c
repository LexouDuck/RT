/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:55 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:16 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		digits[50];
	int		i;
	long	l_nb;

	i = 0;
	l_nb = (long)n;
	if (l_nb < 0)
	{
		ft_putchar_fd('-', fd);
		l_nb *= -1;
	}
	if (l_nb == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	while (l_nb != 0)
	{
		digits[i++] = l_nb % 10;
		l_nb = l_nb / 10;
	}
	while (--i >= 0)
		ft_putchar_fd(digits[i] + '0', fd);
}
