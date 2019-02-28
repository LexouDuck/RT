/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 13:11:57 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DEBUG_H
# define __DEBUG_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

# include "SDL.h"
# include "libft.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	This define will make the program do debug output to terminal (and log.txt)
**	If commented or removed, the debug output will only appear in log.txt
*/
# define DEBUG

/*
**	The name of the file in which we'll output the debug text
*/
# define DEBUG_FILE	"log.txt"

/*
**	This function needs to be called when the program starts,
**	so as to clear the contents of DEBUG_FILE.
*/
int		debug_init();

/*
**	Outputs the given string to DEBUG_FILE, and to STDERR if DEBUG is defined.
*/
void	debug_output(char const *str);

/*
**	Outputs the given args to DEBUG_FILE, and to STDERR if DEBUG is defined.
**	First writes 'str', followed by 'value', and if the 'free_value' arg is
**	not 0, then free() is called on the string 'value'.
*/
void	debug_output_value(char const *str, char *value, t_bool free_value);

/*
**	Outputs the given args to DEBUG_FILE, and to STDERR if DEBUG is defined.
**	First writes 'str' followed by a '\n' newline char, and if 'sdl_error' is
**	not 0, then SDL_GetError() will be called and its return will be written.
*/
void	debug_output_error(char const *str, t_bool sdl_error);

/*
**	Prints str + '\n' to DEBUG_FILE, ifdef DEBUG, also prints to terminal.
*/
int		debug_perror(char const *str);

#endif
