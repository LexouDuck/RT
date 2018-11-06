/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FT_Is.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../libft_char.h"

inline int		FT_IsAlpha(int c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z'));
}

inline int		FT_IsDigit(int c)
{
	return ('0' <= c && c <= '9');
}

inline int		FT_IsAlphanumeric(int c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9'));
}

inline int		FT_IsASCII(int c)
{
	return (0x00 <= c && c <= 0x7F);
}

inline int		FT_IsPrint(int c)
{
	return (0x20 <= c && c <= 0x7E);
}

inline int		FT_IsSpace(int c)
{
	return (c == ' ' || c == 127 || (9 <= c && c <= 13));
}
