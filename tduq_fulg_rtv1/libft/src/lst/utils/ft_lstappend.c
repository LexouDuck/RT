/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:50 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:12:45 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lst.h"

void	ft_lstappend(t_list **alst, t_list *new_elem)
{
	t_list	*cur_elem;

	if (!alst || !new_elem)
		return ;
	if (!(*alst))
	{
		*alst = new_elem;
		return ;
	}
	cur_elem = *alst;
	while (cur_elem->next)
		cur_elem = cur_elem->next;
	cur_elem->next = new_elem;
}
