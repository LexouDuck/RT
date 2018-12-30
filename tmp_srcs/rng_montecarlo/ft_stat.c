/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 00:43:31 by fulguritu         #+#    #+#             */
/*   Updated: 2018/12/30 18:48:22 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//TODO remove
#include <stdio.h>



#include "ft_stat.h"


/*
** Maybe add an "if lst.len = 0" condition ?
*/
//TODO fix
t_stat_sample_i 	ft_stat_merge_samples_i(t_stat_sample_i const start,
										t_stat_sample_i const append)
{
	t_stat_sample_i		res;
	t_u32				i;
	t_u32				j;

	if (start.len > MAX_STAT_SAMPLE_SIZE - append.len)
	{
		write(2, "MAX_SAMPLE_SIZE exceeded: some values thrown\n", 45);
//printf("\t--> startlen: %u, appendlen: %u, sum : %u, MAX_SAMPLE_SIZE: %u\n", start.len, append.len, start.len + append.len, MAX_STAT_SAMPLE_SIZE);
		res.len = MAX_STAT_SAMPLE_SIZE; 
	}
	else
		res.len = start.len + append.len;
	i = 0;
	while (i < start.len)
	{
		res.data[i] = start.data[i];
		++i;
	}
	j = 0;
	while (i < res.len)
	{
		res.data[i] = append.data[j];
		++i;
		++j;
	}
	return (res);
}


//TODO FIX
t_stat_sample_f 	ft_stat_merge_samples_f(t_stat_sample_f const start,
										t_stat_sample_f const append)
{
	t_stat_sample_f		res;
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
		res.data[i] = start.data[i];
		++i;
	}
	j = 0;
	while (i < res.len)
	{
		res.data[i] = append.data[j];
		++i;
		++j;
	}
	return (res);
}
//TODO fix
t_stat_sample_i 	ft_stat_quicksort_i(t_stat_sample_i const i_lst)
{
	t_u64				pivot;
	t_u32				i;
	t_stat_sample_i		sub_lst;
	t_stat_sample_i		sup_lst;

printf("lstlen: %d\n", i_lst.len);
	if (i_lst.len <= 1)
		return (i_lst);
	sub_lst.len = 0;
	sup_lst.len = 0;
	pivot = i_lst.data[0];
	i = 1;
	while (i < i_lst.len)
	{
		if (i_lst.data[i] < pivot)
			sub_lst.data[(sub_lst.len)++] = i_lst.data[i];
		else
			sup_lst.data[(sup_lst.len)++] = i_lst.data[i];
		++i;
	}
//	if (sub_lst.len == 0 || sup_lst.len == 0)
//		return (sub_lst.len == 0 ? sup_lst : sub_lst);
	sub_lst = ft_stat_quicksort_i(sub_lst);
	sup_lst = ft_stat_quicksort_i(sup_lst);
	sub_lst.data[(sub_lst.len)++] = pivot;
	return (ft_stat_merge_samples_i(sub_lst, sup_lst));
}

//TODO fix
t_stat_sample_f 	ft_stat_quicksort_f(t_stat_sample_f const f_lst)
{
	t_u64				pivot;
	t_u32				i;
	t_stat_sample_f		sub_lst;
	t_stat_sample_f		sup_lst;


//printf("lstlen: %d\n", f_lst.len);
	if (f_lst.len <= 1)
		return (f_lst);
	sub_lst.len = 0;
	sup_lst.len = 0;
	pivot = f_lst.data[0];
	i = 1;
	while (i < f_lst.len)
	{
		if (f_lst.data[i] < pivot)
			sub_lst.data[(sub_lst.len)++] = f_lst.data[i];
		else
			sup_lst.data[(sup_lst.len)++] = f_lst.data[i];
		++i;
	}
	sub_lst = ft_stat_quicksort_f(sub_lst);
	sup_lst = ft_stat_quicksort_f(sup_lst);
	sub_lst.data[(sub_lst.len)++] = pivot;
	return (ft_stat_merge_samples_f(sub_lst, sup_lst));
}

inline t_float		ft_stat_median_i(t_stat_sample_i const i_lst)
{
	return (i_lst.len % 2 ?
			i_lst.data[i_lst.len / 2] :
			(i_lst.data[i_lst.len / 2] + i_lst.data[i_lst.len / 2 + 1]) / 2);
}

inline t_float		ft_stat_median_f(t_stat_sample_f const f_lst)
{
	return (f_lst.len % 2 ?
			f_lst.data[f_lst.len / 2] :
			(f_lst.data[f_lst.len / 2] + f_lst.data[f_lst.len / 2 + 1]) / 2);
}

t_float		ft_stat_average_i(t_stat_sample_i const i_lst)
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

t_float		ft_stat_average_f(t_stat_sample_f const f_lst)
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

t_float		ft_stat_variance_i(t_stat_sample_i const i_lst)
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

t_float		ft_stat_variance_f(t_stat_sample_f const f_lst)
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
