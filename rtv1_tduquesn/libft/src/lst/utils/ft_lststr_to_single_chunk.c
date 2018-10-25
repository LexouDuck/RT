/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststr_to_single_chunk.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 02:33:57 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:12:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lst.h"
#include "libft_str.h"

t_list		*ft_lststrfold(t_list *lst)
{
	char	*res_str;
	size_t	tot_size;

	if (!lst || !(res_str = ft_strnew(0)))
		return (NULL);
	tot_size = 0;
	ft_lstmemfold(lst, &tot_size);
	ft_lstfold(lst, &res_str, ft_pcat);
	return (ft_lstnew_no_copy(res_str, tot_size));
}
