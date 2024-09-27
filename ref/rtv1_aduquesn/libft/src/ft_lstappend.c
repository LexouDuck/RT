/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:09 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 02:51:34 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstappend(t_list **alst, t_list *elem)
{
	t_list *lst;

	if (*alst == NULL)
	{
		*alst = elem;
		return ;
	}
	lst = *alst;
	while (lst->next)
	{
		lst = lst->next;
	}
	lst->next = elem;
}
/*
**	if (alst == NULL || elem == NULL)
**		return ;
*/
