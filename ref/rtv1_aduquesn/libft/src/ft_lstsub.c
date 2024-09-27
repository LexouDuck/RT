/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:09 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/18 18:06:00 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	**ft_lstsub(t_list **alst, t_u32 index, t_u32 length)
{
	return (alst || index || length) ? NULL : NULL;
}
/*
**	t_list	**result;
**	t_list	*dst_lst;
**	t_list	*src_lst;
**	t_u32	i;
**
**	if (!(result = (t_list **)malloc(sizeof(t_list *))))
**		return (NULL);
**	if (!(lst = ft_lstget(alst, index)))
**		return (NULL);
**	*result = NULL;
**	src_lst = *alst;
**	dst_lst = *alst;
**	i = 0;
**	while (i < length)
**	{
**		dst_lst = NULL;
**		if (src_lst->next == NULL)
**			return (result);
**		else
**			src_lst = src_lst->next;
**		++i;
**	}
**	return (result);
**}
*/
/*
**	if (alst == NULL)
**		return (NULL);
*/
