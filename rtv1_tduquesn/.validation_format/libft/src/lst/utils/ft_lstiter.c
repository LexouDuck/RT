/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:50 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:12:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lst.h"

void		ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*l_iter;

	if (!lst || !f)
		return ;
	l_iter = lst;
	while (l_iter)
	{
		(*f)(l_iter);
		l_iter = l_iter->next;
	}
}
