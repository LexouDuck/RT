/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrls_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:56 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:17 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"
#include "libft_str.h"

void	ft_putstrls_fd(const char **strls, int fd)
{
	int i;

	if (!strls)
		return ;
	i = 0;
	while (strls[i])
	{
		ft_putstr_fd(strls[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
}
