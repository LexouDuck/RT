/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integral.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 05:14:16 by fulguritu         #+#    #+#             */
/*   Updated: 2018/12/23 05:44:51 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_integral.h"

t_float		mc_integrate(t_scalar_func3 const sf, t_coord_box const domain)
{
	t_vec_3d	rand_input;
	t_float		result;
	t_u32		i;

	result = 0.;
	i = 0;
	while (i < SAMPLE_NB)
	{
		rand_input[0] = ft_frand_a_to_b(domain.start[0], domain.end[0]);
		rand_input[1] = ft_frand_a_to_b(domain.start[1], domain.end[1]);
		rand_input[2] = ft_frand_a_to_b(domain.start[2], domain.end[2]);
		result += sf(rand_input);
		++i;
	}
	result /= (t_float)SAMPLE_NB;
	result *= (domain.end[0] - domain.start[0]) *
				(domain.end[1] - domain.start[1]) *
				(domain.end[2] - domain.start[2]);
	return (result);
}
