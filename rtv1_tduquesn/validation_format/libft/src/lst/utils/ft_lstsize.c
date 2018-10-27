/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:51 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:12:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lst.h"

t_u32			ft_lstsize(t_list *lst)
{
	t_u32		i;
	t_list		*cur_elem;

	if (!lst)
		return (0);
	cur_elem = lst;
	i = 0;
	while (cur_elem)
	{
		cur_elem = cur_elem->next;
		i++;
	}
	return (i);
}
