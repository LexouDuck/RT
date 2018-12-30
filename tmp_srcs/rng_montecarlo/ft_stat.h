/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 00:04:39 by fulguritu         #+#    #+#             */
/*   Updated: 2018/12/30 19:03:22 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STAT_H
# define FT_STAT_H


# include "rng_mc_test.h"
# include <unistd.h>


/*
** Please keep the sample size a power of 2. Here, 2^14.
*/
# define MAX_STAT_SAMPLE_SIZE	0b1000000000000
# define PROB_APPROX			0.000001

typedef struct	s_stat_sample_i
{
	t_u64		data[MAX_STAT_SAMPLE_SIZE];
	t_u32		len;
}				t_stat_sample_i;

typedef struct	s_stat_sample_f
{
	t_float		data[MAX_STAT_SAMPLE_SIZE];
	t_u32		len;
}				t_stat_sample_f;

typedef struct	s_prob_sample_i
{
	t_stat_sample_i		value[MAX_STAT_SAMPLE_SIZE];
	t_stat_sample_f		prob[MAX_STAT_SAMPLE_SIZE];
	t_u32				len;
}				t_prob_sample_i;

typedef struct	s_prob_sample_f
{
	t_stat_sample_f		value[MAX_STAT_SAMPLE_SIZE];
	t_stat_sample_f		prob[MAX_STAT_SAMPLE_SIZE];
	t_u32				len;
}				t_prob_sample_f;


t_stat_sample_i		ft_stat_merge_samples_i(t_stat_sample_i const start,
							t_stat_sample_i const append);
t_stat_sample_f		ft_stat_merge_samples_f(t_stat_sample_f const start,
							t_stat_sample_f const append);


t_stat_sample_i 	ft_stat_quicksort_i(t_stat_sample_i const i_lst);
t_stat_sample_f 	ft_stat_quicksort_f(t_stat_sample_f const f_lst);

/*
** List is supposed to be already in order for this to return the right result.
*/
t_float				ft_stat_median_i(t_stat_sample_i const i_lst);
t_float				ft_stat_median_f(t_stat_sample_f const f_lst);

t_float				ft_stat_average_i(t_stat_sample_i const i_lst);
t_float				ft_stat_average_f(t_stat_sample_f const f_lst);

t_float				ft_stat_variance_i(t_stat_sample_i const i_lst);
t_float				ft_stat_variance_f(t_stat_sample_f const f_lst);

t_float				ft_stat_stddev_i(t_stat_sample_i const i_lst);
t_float				ft_stat_stddev_f(t_stat_sample_f const f_lst);

/*
void				ft_stat_decile_i(t_stat_sample_i const i_lst);
void				ft_stat_decile_f(t_stat_sample_f const f_lst);
*/

t_bool				ft_prob_is_valid_i(t_prob_sample_i const i_problst);
t_bool				ft_prob_is_valid_f(t_prob_sample_f const f_problst);

#endif
