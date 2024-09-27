/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 02:25:16 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/09 15:13:34 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_algebra.h"
#include "ft_printf.h"

void		print_mat33(char const *title, t_mat_3b3 const mat)
{
	ft_printf("%s:\n"
		"\tx: (%.5f, %.5f, %.5f)\n"
		"\ty: (%.5f, %.5f, %.5f)\n"
		"\tz: (%.5f, %.5f, %.5f)\n",
		title,
		mat[0], mat[1], mat[2],
		mat[3], mat[4], mat[5],
		mat[6], mat[7], mat[8]);
}

void		print_mat44(char const *title, t_mat_4b4 const mat)
{
	ft_printf("%s:\n"
		"\tx: (%.5f, %.5f, %.5f, %.5f)\n"
		"\ty: (%.5f, %.5f, %.5f, %.5f)\n"
		"\tz: (%.5f, %.5f, %.5f, %.5f)\n"
		"\tt: (%.5f, %.5f, %.5f, %.5f)\n\n",
		title,
		mat[0], mat[1], mat[2], mat[3],
		mat[4], mat[5], mat[6], mat[7],
		mat[8], mat[9], mat[10], mat[11],
		mat[12], mat[13], mat[14], mat[15]);
}

void		print_vec4(char const *title, t_vec_4d const v)
{
	ft_printf("%s: (%.5f, %.5f, %.5f, %.5f)\n",
		title, v[0], v[1], v[2], v[3]);
}
