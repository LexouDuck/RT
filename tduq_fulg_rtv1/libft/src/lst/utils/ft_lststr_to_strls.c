/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststr_to_strls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 02:33:57 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:12:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lst.h"
#include "libft_str.h"

char	**ft_lststr_to_strls(t_list *lst)
{
	char	**result;
	t_u32	i;
	long	status;

	if (!lst || !(result = (char**)ft_ptrarrnew(ft_lstsize(lst) + 1)))
		return (NULL);
	i = 0;
	while (lst)
	{
		if (!(result[i] = ft_strnew(lst->content_size)))
		{
			ft_strlsdel(&result);
			return (NULL);
		}
		status = ft_strlcpy(result[i], lst->content, lst->content_size + 1);
		if (status != (long)lst->content_size)
			write(2, "Incoherent string size in lst conversion.\n", 42);
		lst = lst->next;
		++i;
	}
	result[i] = NULL;
	return (result);
}
