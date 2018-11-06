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

inline int		FT_IsLetter(int c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z'));
}

inline int		FT_IsUppercase(int c)
{
	return ('a' <= c && c <= 'z');
}

inline int		FT_IsLowercase(int c)
{
	return ('A' <= c && c <= 'Z');
}

inline int		FT_IsAlphanumeric(int c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9'));
}

inline int		FT_IsSpace(int c)
{
	return ((c == ' ') ||
			(c == 127) ||
			('\t' <= c && c <= '\r'));
}

inline int		FT_IsDigit(int c)
{
	return ('0' <= c && c <= '9');
}

inline int		FT_IsHexDigit(int c)
{
	return (('0' <= c && c <= '9') ||
			('A' <= c && c <= 'F') ||
			('a' <= c && c <= 'f'));
}

inline int		FT_IsPunctuation(int c)
{
	return (('!' <= c && c <= '/') ||
			(':' <= c && c <= '@') ||
			('[' <= c && c <= '`') ||
			('{' <= c && c <= '~'));
}

inline int		FT_IsPrintable(int c)
{
	return (0x20 <= c && c <= 0x7E);
}

inline int		FT_IsASCII(int c)
{
	return (0x00 <= c && c <= 0x7F);
}
