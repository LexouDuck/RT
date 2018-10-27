/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 22:32:05 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/19 22:32:27 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_H
# define LIBFT_IO_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define HEXCOLS	6

/*
** ============ Readers ============
*/
/*
** TODO file_to_strls
*/

/*
** ============ Writers ============
*/

/*
** Writes the given char 'c' to the standard output.
*/
void					ft_putchar(char c);

/*
** Writes the given string 'str' to the standard output.
*/
void					ft_putstr(char const *str);

/*
** Writes the given string 'str' to the standard output, with a newline at the
** end.
*/
void					ft_putendl(char const *str);

/*
** Writes the string representation of the given number to the standard output.
*/
void					ft_putnbr(int number);

/*
** Writes a given nul-term list of strings to standard output.
*/
void					ft_putstrls(char const **strls);

/*
** Prints memory in 'str' in 6 columns of 4 distinct bytes to stdout.
*/
void					ft_putmem(char const *str);

/*
** Writes the given char 'c' to the given file descriptor 'fd'.
*/
void					ft_putchar_fd(char c, int fd);

/*
** Writes the given string 'str' to the given file descriptor 'fd'.
*/
void					ft_putstr_fd(char const *str, int fd);

/*
** Writes the given string 'str' to the given file descriptor 'fd',
** with a newline at the end.
*/
void					ft_putendl_fd(char const *str, int fd);

/*
** Writes the string representation of the given number to the given
** file descriptor 'fd'.
*/
void					ft_putnbr_fd(int number, int fd);

/*
** Writes a given nul-term list of strings to file descriptor.
*/
void					ft_putstrls_fd(char const **strls, int fd);

/*
** Prints memory in  (null-term) 'str' in HEXCOLS columns of 4 distinct bytes to
** 'fd'.
*/
void					ft_putmem_fd(char const *str, int fd);

/*
** Prints memory in  (null-term) 'str' in HEXCOLS columns of 4 distinct bytes to
** stdout.
*/
void					ft_putmem(char const *str);

#endif
