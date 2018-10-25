/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:12 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/15 02:08:12 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr(int number)
{
	char	digits[10];
	long	n;
	int		i;

	n = (long)number;
	if (n < 0)
	{
		n *= -1;
		write(STDOUT, "-", 1);
	}
	else if (n == 0)
	{
		write(STDOUT, "0", 1);
		return ;
	}
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10 + '0';
		n /= 10;
	}
	while (i--)
	{
		write(STDOUT, (digits + i), 1);
	}
}
