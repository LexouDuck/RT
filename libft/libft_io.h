/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_H
# define LIBFT_IO_H

# include "libft.h"

# include "libft_string.h"

/*
** ============ Reading ============
*/
/*
**
** TODO file_to_strls
*/



/*
** ============ Writing ============
*/



/*
**	Writes the given character 'c' to the given file descriptor 'fd'.
*/
void	FT_WriteChar(char c, int fd);

/*
**	Writes the given string 'str' to the given file descriptor 'fd'.
*/
void	FT_WriteString(const char *str, int fd);

/*
**	Writes the given string 'str' to the given file descriptor 'fd',
**	with a newline at the end.
*/
void	FT_WriteLine(const char *str, int fd);

/*
**	Writes the given string array 'strls' to the given file descriptor 'fd'.
*/
void	FT_WriteStringArray(const char **strls, int fd);

/*
**	Writes hexadecimal memory in the null-terminated string 'str',
**	writing lines of 'cols' columns of 4-byte chunks to 'fd'.
*/
void	FT_WriteMemory(char const *str, t_u8 cols, int fd);



/*
**	Writes the given char 'c' to the standard output.
*/
void	FT_OutputChar(char c);

/*
**	Writes the given string 'str' to the standard output.
*/
void	FT_OutputString(const char *str);

/*
**	Writes the given string 'str' to the standard output,
**	with a newline at the end.
*/
void	FT_OutputLine(const char *str);

/*
**	Writes the given string array 'strls' to the standard output.
*/
void	FT_OutputStringArray(const char **strls);

/*
**	Outputs hexadecimal memory in the null-terminated string 'str',
**	writing lines of 'cols' columns of 4-byte chunks.
*/
void	FT_OutputMemory(const char *str, t_u8 cols);

#endif
