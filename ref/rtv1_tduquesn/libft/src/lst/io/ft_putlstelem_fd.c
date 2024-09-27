/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlstelem_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:55 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:15 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"

void	ft_putlstelem_fd(t_list *elem, int fd)
{
	if (elem && elem->content)
		write(fd, elem->content, elem->content_size);
}
