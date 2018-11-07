/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2018/11/07 01:56:36 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_H
# define LIBFT_IO_H

# include "libft.h"
# include "libft_string.h"

/* ************************************************************************** */
/*                                  Macros                                    */
/* ************************************************************************** */

/*
**	Define the 3 standard (std) streams of data - these numbers are special
**	file descriptors used to read from and write to the terminal commandline.
*/
# define STDIN	0
# define STDOUT	1
# define STDERR	2

/*
**	Define the return values for the reading functions.
*/
# define OK		0
# define ERROR	1

/*
**	Define the return values for FT_GetNextLine().
*/
# define GNL_ERROR -1
# define GNL_LINE	1
# define GNL_END	0

/*
**	This is the arbitrary buffer size to be used by the reading functions.
**	Raising this amount will lower the amount of function calls made to
**	the 'read' function from unistd.h, resulting in possible speed improvments,
**	depending on the amount of files to read, and their filesizes.
**	It is also recommended to have this number be a power of 2, as it can be
**	occasionally faster to manage arrays of such sizes on certain machines.
*/
# define BUFF_SIZE 2048



/* ************************************************************************** */
/*                              Reading Functions                             */
/* ************************************************************************** */

/*	@	stdio.h > fread()
**	Reads the contents of the file descriptor 'fd', and puts it into 'buffer'.
**	Returns 0 if the stream was read successfully, 1 if there was an error.
*/
int		FT_ReadFile(int const fd, char * buffer);

/*	@	stdio.h > fgets()
**	Reads the contents of the file descriptor 'fd' line per line.
**	This means that it will allocate and fill a buffer until reading '\n',
**	at which point this buffer is returned via the 'line' char pointer arg.
**	Returns:
**		-1 if there's an error
**		1 if a line of characters was successfully read
**		0 if the end of the file was reached
*/
int		FT_GetNextLine(int const fd, char ** line);

/*	TODO actually code this
**	Reads the contents of the file descriptor 'fd', and puts that into
**	an array of strings, one char pointer for each line.
**	The '\n' characters are replaced by '\0' string terminators.
**	Returns 0 if the stream was read successfully, 1 if there was an error.
*/
int		FT_ReadAllLines(int const fd, char ** strls);



/* ************************************************************************** */
/*                              Writing Functions                             */
/* ************************************************************************** */

/*	@	stdio.h > putc() & fputc()
**	Writes the given character 'c' to the given file descriptor 'fd'.
*/
void	FT_WriteChar(char c, int fd);

/*	@	stdio.h > fputs()
**	Writes the given string 'str' to the given file descriptor 'fd'.
*/
void	FT_WriteString(char const * str, int fd);

/*
**	Writes the given string 'str' to the given file descriptor 'fd',
**	with a newline '\n' character at the end.
*/
void	FT_WriteLine(char const * str, int fd);

/*
**	Writes the given string array 'strls' to the given file descriptor 'fd'.
*/
void	FT_WriteStringArray(char const ** strls, int fd);

/*
**	Writes hexadecimal memory in the null-terminated string 'str',
**	writing lines of 'cols' columns of 4-byte chunks to 'fd'.
*/
void	FT_WriteMemory(char const * str, t_u8 cols, int fd);



/* ************************************************************************** */
/*                             Commandline Output                             */
/* ************************************************************************** */

/*	@	stdio.h > putchar()
**	Writes the given char 'c' to the standard output.
*/
void	FT_OutputChar(char c);

/*
**	Writes the given string 'str' to the standard output.
*/
void	FT_OutputString(char const * str);

/*	@	stdio.h > puts()
**	Writes the given string 'str' to the standard output,
**	with a newline '\n' character at the end.
*/
void	FT_OutputLine(char const * str);

/*
**	Writes the given string array 'strls' to the standard output.
*/
void	FT_OutputStringArray(char const ** strls);

/*
**	Outputs hexadecimal memory in the null-terminated string 'str',
**	writing lines of 'cols' columns of 4-byte chunks.
*/
void	FT_OutputMemory(char const * str, t_u8 cols);

#endif
