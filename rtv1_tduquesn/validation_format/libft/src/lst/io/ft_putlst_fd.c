/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:55 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:16 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"

void	ft_putlst_fd(t_list *lst, int fd)
{
	while (lst)
	{
		ft_putlstelem_fd(lst, fd);
		ft_putchar_fd('\n', fd);
		lst = lst->next;
	}
}
