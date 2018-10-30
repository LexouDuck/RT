/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/FT_Output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_io.h"

inline void	FT_OutputChar(char c)
{
	write(STDOUT, &c, 1);
}

inline void	FT_OutputString(const char *str)
{
	if (str)
		write(STDOUT, str, FT_StringLength(str));
}

inline void	FT_OutputLine(const char *str)
{
	if (str)
	{
		write(STDOUT, str, FT_StringLength(str));
		write(STDOUT, "\n", 1);
	}
}

inline void	FT_OutputStringArray(const char **strls)
{
	if (strls)
		FT_WriteStringArray(strls, STDOUT);
}

inline void	FT_OutputMemory(const char *str, t_u8 cols)
{
	if (str)
		FT_WriteMemory(str, cols, STDOUT);
}
