/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_fixed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:09 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 06:02:29 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_array_fixed_get_count(t_list *lst)
{
	int		result;
	size_t	size;

	result = 0;
	size = lst->content_size;
	while (lst)
	{
		++result;
		lst = lst->next;
		if (lst->content_size != size)
			return (-1);
	}
	return (result);
}

void	*ft_array_fixed(t_list **alst, void *terminator)
{
	void	*result;
	int		count;
	size_t	size;
	t_list	*lst;
	int		i;

	lst = *alst;
	count = ft_array_fixed_get_count(lst);
	if (count == -1)
		return (NULL);
	size = lst->content_size;
	if (!(result = (void *)malloc((count + 1) * size)))
		return (NULL);
	i = 0;
	while (i < count)
	{
		ft_memcpy(result + i, lst->content, size);
		lst = lst->next;
		++i;
	}
	ft_memcpy(result + i, terminator, size);
	return (result);
}
/*
**	if (alst == NULL || *alst == NULL)
**		return (NULL);
*/
