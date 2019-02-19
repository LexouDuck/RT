/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_menu_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"

int			ui_menu_file_open(char *filepath)
{
	t_rtparser	parser;
	char		*error;

	if (rt_open_file(filepath, &parser))
		return (ERROR);
	ft_memclr(rt.scene.objects, OBJECT_MAX_AMOUNT * sizeof(t_object));
	rt.scene.object_amount = 0;
	if ((error = rt_read_file(&parser)))
	{
		debug_output_value("Error: while reading rt file -> at line ",
			ft_s32_to_str(parser.line), TRUE);
		debug_output_error(error, FALSE);
		return (ERROR);
	}
	debug_output_value("Successfully opened file: ", filepath, FALSE);
	rt_output_readfile();
	return (OK);
}

int			ui_menu_file_import(char *filepath)
{
	t_rtparser	parser;
	char		*error;

	if (rt_open_file(filepath, &parser))
		return (ERROR);
	if ((error = rt_read_file(&parser)))
	{
		debug_output_value("Error: while reading rt file -> at line ",
			ft_s32_to_str(parser.line), TRUE);
		debug_output_error(error, FALSE);
		return (ERROR);
	}
	debug_output_value("Successfully imported file: ", filepath, FALSE);
	rt_output_readfile();
	return (OK);
}
