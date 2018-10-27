/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:51 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:12:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lst.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_elem;

	if (!(new_elem = (t_list*)malloc(sizeof(t_list))))
		return (0);
	if (content)
	{
		if (!(new_elem->content = malloc(content_size)))
			return (NULL);
		new_elem->content_size = content_size;
		ft_memmove(new_elem->content, content, content_size);
	}
	else
	{
		new_elem->content_size = 0;
		new_elem->content = NULL;
	}
	new_elem->next = NULL;
	return (new_elem);
}
