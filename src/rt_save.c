/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "debug.h"
#include "libft_convert.h"

/*
** this function write a function to the savefile
*/

static void		print_float3_to_str(int fd, cl_float3 *vector, char *label)
{
	char *tmp;

	if ((tmp = cl_float3_to_str(vector, 5)))
	{
		FT_Write_String(fd, label);
		FT_Write_Line(fd, tmp);
		free(tmp);
	}
	return ;
}

/*
** this function write revery data of the map and call above function.
*/

static void		print_get_str(int fd, t_object *object)
{
	char *tmp;

	if ((tmp = rt_get_str_primitive(object->type)))
		FT_Write_Line(fd, tmp);
	if (ft_strlen(object->name))
	{
		FT_Write_Char(fd, '"');
		FT_Write_String(fd, object->name);
		FT_Write_Line(fd, "\"");
	}
	if ((tmp = rt_get_str_material(object->material)))
	{
		FT_Write_String(fd, "material:");
		FT_Write_Line(fd, tmp);
	}
	if ((tmp = rt_get_str_pattern(object->pattern)))
	{
		FT_Write_String(fd, "pattern:");
		FT_Write_Line(fd, tmp);
	}
	if ((tmp = rt_get_str_projection(object->uvw_projection)))
	{
		FT_Write_String(fd, "projection:");
		FT_Write_Line(fd, tmp);
	}
	if ((tmp = rt_get_str_bump(object->bump_type)))
	{
		FT_Write_String(fd, "bump:");
		FT_Write_Line(fd, tmp);
	}
}

/*
** this function print Back ground color on the savefile
*/

static void		print_bg_color(int fd)
{
	char *tmp;

	if ((tmp = FT_U32_To_HexString(rt.scene.bg_color)))
	{
		FT_Write_String(fd, "BG #");
		FT_Write_Line(fd, tmp);
		FT_Write_Char(fd, '\n');
		free(tmp);
	}
	return ;
}

/*
** this function write a map and save in a new file or in the same file.
*/

void			rt_save(int fd)
{
	size_t		i;
	t_object	*object;

	print_bg_color(fd);
	i = 0;
	while (i < rt.scene.object_amount)
	{
		object = &rt.scene.objects[i];
		if (object)
		{
			print_get_str(fd, object);
			print_float3_to_str(fd, &object->rgb_a, "color:");
			print_float3_to_str(fd, &object->rgb_b, "color2:");
			print_float3_to_str(fd, &object->pos, "pos:");
			print_float3_to_str(fd, &object->rot, "rot:");
			print_float3_to_str(fd, &object->scale, "scale:");
			print_float3_to_str(fd, &object->bbox_os.vi, "bbox_vi:");
			print_float3_to_str(fd, &object->bbox_os.vf, "bbox_vf:");
			print_float3_to_str(fd, &object->uvw_scale, "uvw_scale:");
			print_float3_to_str(fd, &object->uvw_offset, "uvw_offset:");
			//TODO Add refrace rough and opacity ?
			FT_Write_Char(fd, '\n');
		}
		i++;
	}
	FT_Write_Char(fd, '\n');
	return ;
}

void			ui_menu_file_save(void)
{
	debug_output("File->Save\n");
	if (rt.filepath)
	{
		rt_file_save(rt.filepath);
	}
	else
	{
		rt.ui.current_prompt.textbox = texttype_text;
		rt.ui.current_prompt.text = ft_strdup("./");
		rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_SAVE;
		rt.ui.current_prompt.description = "Type in the destination filepath.";
		rt.ui.current_prompt.rect = PROMPT;
	}
	return ;
}
