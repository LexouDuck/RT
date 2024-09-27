/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 00:43:31 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/01 23:47:05 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//TODO remove
#include <stdio.h>



#include "ft_stat.h"
/*
** An extra t_int is always allocated to leve room for the pivot in QckSrt
*/
t_int_list 	ft_stat_merge_ilst(t_int_list *start,
								t_int_list *append)
{
	t_int_list			res;
	t_u32				i;
	t_u32				j;

	if (start->len == 0 && append->len == 0)
		return (ft_stat_new_ilst(0));
	else if (!start->data || start->len == 0)
		return (*append);
	else if (!append->data || append->len == 0)
		return (*start);
	res = ft_stat_new_ilst(start->len + append->len + 1);
	--res.len;
	if (!(res.data))
		return (res);
	i = 0;
	while (i < start->len)
	{
		res.data[i] = start->data[i];
		++i;
	}
	j = 0;
	while (i < res.len)
		res.data[i++] = append->data[j++];
	ft_stat_free_ilst(start);
	ft_stat_free_ilst(append);
	return (res);
}

/*
//TODO FIX
t_float_list 	ft_stat_merge_flst(t_float_list const start,
										t_float_list const append)
{
	t_float_list		res;
	t_u32				i;
	t_u32				j;

	if (start.len > MAX_STAT_SAMPLE_SIZE - append.len)
	{
		write(2, "MAX_SAMPLE_SIZE exceeded: some values thrown\n", 45);
		res.len = MAX_STAT_SAMPLE_SIZE; 
	}
	else
		res.len = start.len + append.len;
	i = 0;
	while (i < start.len)
	{
		res->data[i] = start->data[i];
		++i;
	}
	j = 0;
	while (i < res.len)
	{
		res->data[i] = append->data[j];
		++i;
		++j;
	}
	return (res);
}
*/

t_int_list 	ft_stat_quicksort_i(t_int_list const i_lst)
{
	t_int				pivot;
	t_u32				i;
	t_int_list			sub_lst;
	t_int_list			sup_lst;

	if (i_lst.len <= 1)
		return (i_lst);
	sub_lst = ft_stat_new_ilst(i_lst.len);
	sup_lst = ft_stat_new_ilst(i_lst.len);
	if (!sub_lst.data || !sup_lst.data)
		return (ft_stat_new_ilst(0));
	sub_lst.len = 0;
	sup_lst.len = 0;
	pivot = i_lst.data[0];
	i = 0;
	while (++i < i_lst.len)
		if (i_lst.data[i] < pivot)
			sub_lst.data[(sub_lst.len)++] = i_lst.data[i];
		else
			sup_lst.data[(sup_lst.len)++] = i_lst.data[i];
	sub_lst = ft_stat_quicksort_i(sub_lst);
	sup_lst = ft_stat_quicksort_i(sup_lst);
	sub_lst.data[(sub_lst.len)++] = pivot;
	return (ft_stat_merge_ilst(&sub_lst, &sup_lst));
}
/*
//TODO fix
t_float_list 	ft_stat_quicksort_f(t_float_list const f_lst)
{
	t_float				pivot;
	t_u32				i;
	t_float_list		sub_lst;
	t_float_list		sup_lst;


//printf("lstlen: %d\n", f_lst.len);
	if (f_lst.len <= 1)
		return (f_lst);
	sub_lst.len = 0;
	sup_lst.len = 0;
	pivot = f_lst->data[0];
	i = 1;
	while (i < f_lst.len)
	{
		if (f_lst->data[i] < pivot)
			sub_lst->data[(sub_lst.len)++] = f_lst->data[i];
		else
			sup_lst->data[(sup_lst.len)++] = f_lst->data[i];
		++i;
	}
	sub_lst = ft_stat_quicksort_f(sub_lst);
	sup_lst = ft_stat_quicksort_f(sup_lst);
	sub_lst->data[(sub_lst.len)++] = pivot;
	return (ft_stat_merge_samples_f(sub_lst, sup_lst));
}
*/

inline t_float		ft_stat_median_i(t_int_list const i_lst)
{
	return (i_lst.len % 2 ?
			i_lst.data[i_lst.len / 2] :
			(i_lst.data[i_lst.len / 2] + i_lst.data[i_lst.len / 2 + 1]) / 2);
}

inline t_float		ft_stat_median_f(t_float_list const f_lst)
{
	return (f_lst.len % 2 ?
			f_lst.data[f_lst.len / 2] :
			(f_lst.data[f_lst.len / 2] + f_lst.data[f_lst.len / 2 + 1]) / 2);
}

t_float		ft_stat_average_i(t_int_list const i_lst)
{
	t_float		sum;
	t_u32		i;

	sum = 0;
	i = 0;
	while (i < i_lst.len)
	{
		sum += i_lst.data[i];
		++i;
	}
	return (sum / i);

}

t_float		ft_stat_average_f(t_float_list const f_lst)
{
	t_float		sum;
	t_u32		i;

	sum = 0.;
	i = 0;
	while (i < f_lst.len)
	{
		sum += f_lst.data[i];
		++i;
	}
	return (sum / i);
}

/*
** Using V(X) = E(X^2) - E(X)^2 rather than E( [X - E(X)]^2 ) which has more
**	operations (n subtractions).
*/

t_float		ft_stat_variance_i(t_int_list const i_lst)
{
	t_float		sum;
	t_u32		i;
	t_float		average;
	t_float		tmp;

	average = ft_stat_average_i(i_lst);
	sum = 0;
	i = 0;
	while (i < i_lst.len)
	{
		tmp = i_lst.data[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));

}

t_float		ft_stat_variance_f(t_float_list const f_lst)
{
	t_float		sum;
	t_u32		i;
	t_float		average;
	t_float		tmp;

	average = ft_stat_average_f(f_lst);
	sum = 0;
	i = 0;
	while (i < f_lst.len)
	{
		tmp = f_lst.data[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));

}

/*
t_bool				ft_prob_is_valid_i(t_prob_sample_i const i_problst)
{
	t_float		prob_sum;
	t_float		tmp;
	t_u32		i;

	prob_sum = 0.;
	i = 0;
	while (i < i_problst.len)
	{
		tmp = i_problst.prob[i];
		if (tmp < 0. || 1. < tmp)
		{
			ft_printf_fd(2, "Proba %f at index %d is out of [0, 1]\n", tmp, i);
			return (FALSE);
		}
		prob_sum += tmp;
		++i;
	}
	if (ft_fabs(prob_sum - 1.) > PROB_APPROX)
	{
		ft_printf_fd(2, "Proba sum %s is too far from 1.\n", prob_sum);
		return (FALSE);
	}
	return (TRUE);
}

t_bool				ft_prob_is_valid_f(t_prob_sample_f const f_problst);
{

}
*/
