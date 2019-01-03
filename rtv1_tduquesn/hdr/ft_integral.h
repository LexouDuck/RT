/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integral.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 04:59:20 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/03 03:47:17 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INTEGRAL_H
# define FT_INTEGRAL_H

# include "../libft/hdr/libft_algebra.h"
# include "ft_random.h"

# define SAMPLE_NB		1024

typedef		t_float	(*t_scalar_func3)(t_vec_3d const v);


/*
** Note that this is a coordinate box in the input space R^3. The volume
** computed by the integral is thus technically a 4-hypervolume (since you
** add a dimension because of the output space of dimension 1).
** The box is assumed to be orthogonal (brick shaped), which is why only
** two vectors are necessary to define it.
*/
typedef struct		s_coord_box
{
	t_vec_3d	start;
	t_vec_3d	end;
}					t_coord_box;

//t_float	lin_integrate(sf, domain);
t_float		mc_integrate(t_scalar_func3 const sf, t_coord_box const domain);

#endif
