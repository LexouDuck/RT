/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_lst_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 22:39:57 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:17 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"

void	ft_putnbr_lst_fd(t_list *lst, int fd)
{
	while (lst)
	{
		ft_putnbr_lstelem_fd(lst, fd);
		ft_putchar_fd('\n', fd);
		lst = lst->next;
	}
}
