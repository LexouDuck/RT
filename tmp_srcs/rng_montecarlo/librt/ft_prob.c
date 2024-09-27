/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 22:02:27 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/01 23:59:21 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stat.h"

t_prob_mass				ft_stat_new_pmf(t_u32 len)
{
	t_prob_mass	res;

	res.value = NULL;
	res.prob = NULL;
	res.len = 0;
	if (len == 0 ||
		!(res.value = malloc(len * sizeof(t_float))) ||
		!(res.prob = malloc(len * sizeof(t_float))))
		return (res);
	res.len = len;
	return (res);
}

void					ft_stat_free_pmf(t_prob_mass *drv)
{
	if (drv->value)
	{
		free(drv->value);
		drv->value = NULL;
	}
	if (drv->prob)
	{
		free(drv->prob);
		drv->prob = NULL;
	}
	drv->len = 0;
}

t_int_list				ft_stat_ilst_to_iset(t_int_list const ilst)
{
	t_int_list				res;
	t_int_list				set;
	t_u32					i;
	t_u32					j;

	set = ft_stat_new_ilst(ilst.len);
	set.len = 0;
	i = 0;
	while (i < ilst.len)
	{
		j = 0;
		while (j < set.len)
		{
			if (set.data[j] == ilst.data[i])
				break;
			++j;
		}
		if (j == set.len)
			set.data[(set.len)++] = ilst.data[i];
		++i;
	}
	res = ft_stat_new_ilst(set.len);
//	ft_memcpy(res.data, set.data, set.len * sizeof(t_int));
memcpy(res.data, set.data, set.len * sizeof(t_int));
	free(set.data);
	return (res);
}

t_u32				ft_stat_ilst_count(t_int_list ilst, t_int elem)
{
	t_u32		i;
	t_u32		res;

	i = 0;
	res = 0;
	while (i < ilst.len)
	{
		if (ilst.data[i] == elem)
			++res;
		++i;
	}
	return (res);
}

/*
** Returns the probability distribution of a list of integers.
*/
t_prob_mass		ft_stat_ilst_to_pmf(t_int_list const ilst)
{
	t_prob_mass			res;
	t_int_list			set;
	t_u32				i;
	t_float				inv_sample_size;

	if (ilst.data == NULL || ilst.len == 0)
		return (ft_stat_new_pmf(0));
	set = ft_stat_ilst_to_iset(ilst);
	res = ft_stat_new_pmf(set.len);
	i = 0;
	inv_sample_size = 1.0 / ilst.len;
	while (i < res.len)
	{
		res.value[i] = (t_float)set.data[i];
		res.prob[i] = (t_float)ft_stat_ilst_count(ilst, set.data[i]);
		res.prob[i] *= inv_sample_size;
		++i;
	}
	ft_stat_free_ilst(&set);
	return (res);
}
