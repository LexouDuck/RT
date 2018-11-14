/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/ft_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_io.h"

inline void	ft_output_char(char c)
{
	write(STDOUT, &c, 1);
}

inline void	ft_output_str(const char *str)
{
	if (str)
		write(STDOUT, str, ft_strlen(str));
}

inline void	ft_output_line(const char *str)
{
	if (str)
	{
		write(STDOUT, str, ft_strlen(str));
		write(STDOUT, "\n", 1);
	}
}

inline void	ft_output_strls(const char **strls)
{
	if (strls)
		ft_write_strls(strls, STDOUT);
}

inline void	ft_output_memory(const char *str, t_u8 cols)
{
	if (str)
		ft_write_memory(str, cols, STDOUT);
}
