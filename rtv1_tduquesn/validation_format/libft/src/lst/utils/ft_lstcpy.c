/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 22:03:30 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:12:45 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lst.h"

static t_list	*ft_lstelemcpy(t_list *elem)
{
	if (!elem)
		return (NULL);
	return (ft_lstnew(elem->content, elem->content_size));
}

t_list			*ft_lstcpy(t_list *lst)
{
	if (!lst)
		return (NULL);
	return (ft_lstmap(lst, &ft_lstelemcpy));
}
