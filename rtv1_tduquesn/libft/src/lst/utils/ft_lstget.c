/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 16:30:26 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:12:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lst.h"

t_list	*ft_lstget(t_list *lst, t_u32 n)
{
	t_u32		i;
	t_list		*result;

	if (!lst)
		return (NULL);
	result = lst;
	i = 0;
	while (i < n)
	{
		result = result->next;
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}
