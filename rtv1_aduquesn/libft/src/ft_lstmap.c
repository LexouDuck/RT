/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:10 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 02:54:46 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	delete(void *content, size_t content_size)
{
	if (content && content_size > 0)
	{
		free(content);
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *))
{
	t_list	*result;
	t_list	*current;

	result = NULL;
	while (lst)
	{
		current = f(lst);
		if (current == NULL)
		{
			ft_lstdel(&result, &delete);
			return (NULL);
		}
		ft_lstappend(&result, current);
		lst = lst->next;
	}
	return (result);
}
/*
**	if (lst == NULL || f == NULL)
**		return (NULL);
*/
