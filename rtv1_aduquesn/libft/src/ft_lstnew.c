/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:10 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:11 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *result;

	if (!(result = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		result->content = NULL;
		result->content_size = content_size;
	}
	else
	{
		result->content_size = content_size;
		result->content = malloc(content_size);
		ft_memcpy(result->content, content, content_size);
	}
	result->next = NULL;
	return (result);
}
