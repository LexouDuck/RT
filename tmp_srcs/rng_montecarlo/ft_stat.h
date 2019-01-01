/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 00:04:39 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/01 23:05:39 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STAT_H
# define FT_STAT_H


# include "rng_mc_test.h"
# include <unistd.h>
# include <stdlib.h>


/*
** Please keep the sample size a power of 2. Here, 2^14.
*/
//# define MAX_STAT_SAMPLE_SIZE	0b1000000000000
# define PROB_APPROX			0.000001


typedef struct	s_int_list
{
	t_int		*data;
	t_u32		len;
}				t_int_list;

typedef struct	s_float_list
{
	t_float		*data;
	t_u32		len;
}				t_float_list;

/*
** Use only to signify a list with no repeating values.
*/
/*
typedef t_int_list		t_int_set;
typedef t_float_list	t_float_set;
*/
/*
** Use only to signify a list that has been ordered.
*/
/*
typedef t_int_list		t_int_sortedlst;
typedef t_float_list	t_float_sortedlst;
*/

/*
** Remember:
**
** A random variable X is a function from an input set O to an output set V,
** where:
**		- The universe O of possible events is the input set of X.
**		- The universe O is endowed with a sigma-algebra A (think "power set or
**			appropriate continuous extension of the power set"). Events are the
**			members of A, or equivalently, events are the subsets of O.
**		- P is a measure over A with values in [0, 1] such that the event for
**			the whole of O is given measure 1 (=all possibilites). Generally P
**			is found/constructed by taking some obvious	measure M on O (like
**			Lebesgue or counting) and normalizing by defining for every event
**			'a' the following: P(a) = M(a) / M(O).
**		- The triplet (O, A, P) is called a probability space. It's in a sense
**			our "full" input space with all necessary structure.
**		- probability for a given output Y is the measure of the preimage of
**			Y by f. Ie, the measure of the set X in O, or element a in A,
**			such that f(X) = Y.
**			Eg, the probability of getting an even number on a uniform 6-sided
**			dice (event "e") is 1/2 because M(e) = #({2,4,6}) = 3 and
**			M(O) = #({1,2,3,4,5,6}) = 6 and P(e)= M(e) / M(O) = 3/6 = 1/2.
**		- "values" of X are the values in the output space V.
**		- the output set V is generally R, sometimes R^n, rarely N without
**			extending it to R naturally (ie, medians, average, etc. of integers
**			end up in the real numbers anyways).
**		- a probability distribution f is a function from V to [0,1] that
**			assigns its probability to each event, represented not as an element**			of A, but as the (set of) value(s) of that event in V.
**		- if the input set is discrete, f is a "probability mass function".
**		- if the input set is continuous, f is a "probability density function".
**
** To summarize, there are 3 major spaces: (O, A, P), V and [0,1], and they are ** linked thus:
**		- X: (O, A, P) -> V
**		- P: (O, A, P) -> [0, 1]
**		- f: V -> [0, 1]
**
** In the following implementation, discrete universes are kept finite and
** indexed, each atomic event is given by an index of the list.
** "value[i]" corresponds to X(i); "prob[i]" corresponds to f(X(i)).
*/

/*
** A struct for the probability mass function describing a discrete random var.
*/
typedef struct	s_prob_mass
{
	t_float				*value;
	t_float				*prob;
	t_u32				len;
}				t_prob_mass;

/*
typedef struct	s_prob_dens
{
	t_float		(*distrib)(); //? cumul distib ?
}				t_prob_dens;
*/

t_int_list			ft_stat_merge_ilst(t_int_list *start,
							t_int_list *append);
t_float_list		ft_stat_merge_flst(t_float_list *start,
							t_float_list *append);


t_int_list 			ft_stat_quicksort_i(t_int_list const i_lst);
t_float_list 		ft_stat_quicksort_f(t_float_list const f_lst);

/*
** List is supposed to be already in order for this to return the right result.
*/
t_float				ft_stat_median_i(t_int_list const i_lst);
t_float				ft_stat_median_f(t_float_list const f_lst);

t_float				ft_stat_average_i(t_int_list const i_lst);
t_float				ft_stat_average_f(t_float_list const f_lst);

t_float				ft_stat_variance_i(t_int_list const i_lst);
t_float				ft_stat_variance_f(t_float_list const f_lst);

t_float				ft_stat_stddev_i(t_int_list const i_lst);
t_float				ft_stat_stddev_f(t_float_list const f_lst);

t_int_list			ft_stat_new_ilst(t_u32 len);
t_float_list		ft_stat_new_flst(t_u32 len);
void				ft_stat_free_ilst(t_int_list *ilst);
void				ft_stat_free_flst(t_float_list *flst);

/*
void				ft_stat_decile_i(t_int_list const i_lst);
void				ft_stat_decile_f(t_float_list const f_lst);


t_bool				ft_prob_is_valid_i(t_prob_sample_i const i_problst);
t_bool				ft_prob_is_valid_f(t_prob_sample_f const f_problst);
*/

t_prob_mass			ft_stat_new_pmf(t_u32 len);
void				ft_stat_free_pmf(t_prob_mass *drv);
t_int_list			ft_stat_ilst_to_iset(t_int_list const ilst);
t_u32				ft_stat_ilst_count(t_int_list ilst, t_int elem);
t_prob_mass			ft_stat_ilst_to_pmf(t_int_list const ilst);

#endif
