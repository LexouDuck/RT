/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:09 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 05:27:03 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	**ft_array(t_list **alst)
{
	void	**result;
	int		count;
	int		i;
	t_list	*lst;

	lst = *alst;
	count = ft_lstsize(lst);
	if (!(result = (void **)malloc((count + 1) * sizeof(void *))))
		return (NULL);
	i = 0;
	while (i < count)
	{
		result[i] = (void *)malloc(lst->content_size);
		ft_memcpy(result[i], lst->content, lst->content_size);
		lst = lst->next;
		++i;
	}
	result[i] = NULL;
	return (result);
}
/*
**	if (alst == NULL)
**		return (NULL);
*/
