/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:09 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/15 02:08:09 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstget(t_list **alst, t_u32 index)
{
	t_list	*lst;
	t_u32	i;

	lst = *alst;
	i = 0;
	while (i < index)
	{
		if (lst->next == NULL)
			return (NULL);
		else
			lst = lst->next;
		++i;
	}
	return (lst);
}
/*
**	if (alst == NULL)
**		return (NULL);
*/
