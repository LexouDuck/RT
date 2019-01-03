/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat_nblst_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 18:41:11 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/01 21:10:37 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stat.h"

t_int_list		ft_stat_new_ilst(t_u32 len)
{
	t_int_list		res;

	res.data = NULL;
	res.len = 0;
	if (len == 0 || !(res.data = malloc(sizeof(t_int) * len)))
		return (res);
	res.len = len;
	return (res);
}

t_float_list	ft_stat_new_flst(t_u32 len)
{
	t_float_list	res;

	res.data = NULL;
	res.len = 0;
	if (len == 0 || !(res.data = malloc(sizeof(t_int) * len)))
		return (res);
	res.len = len;
	return (res);
}

void			ft_stat_free_ilst(t_int_list *ilst)
{
	if (ilst->data)
	{
		free(ilst->data);
		ilst->data = NULL;
	}
	ilst->len = 0;
}

void			ft_stat_free_flst(t_float_list *flst)
{
	if (flst->data)
	{
		free(flst->data);
		flst->data = NULL;
	}
	flst->len = 0;
}
