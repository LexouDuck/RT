/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
#define DEBUG_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "SDL.h"

#include "libft.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	This define will make the program do debug output to terminal (and log.txt)
**	If commented or removed, the debug output will only appear in log.txt
*/
#define DEBUG

#define DEBUG_FILE	"log.txt"

int		debug_init();
void	debug_output(char const* str);
void	debug_output_value(char const* str, char* value, t_bool free_value);
void	debug_output_error(char const* str, t_bool sdl_error);

#endif
