/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_ini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_char.h"
#include "libft_string.h"
#include "libft_convert.h"
#include "libft_io.h"
#include "../rt.h"
#include "debug.h"

static char	*ini_error(char expected, char *description, char instead)
{
	char	*result;
	size_t	length;
	size_t	i;

	length = FT_StringLength(description);
	if (!(result = FT_MemoryAlloc((64 + length) * sizeof(char))))
		return (NULL);
	i = 0;
	FT_StringCopy(result, "Expected \'");
	i += 10;
	result[i++] = expected;
	FT_StringCopy(result + i, "\' (");
	i += 3;
	FT_StringCopy(result + i, description);
	i += length;
	FT_StringCopy(result + i, "), but instead found: \'");
	i += 21;
	result[i++] = instead;
	return (result);
}

static void	ini_parse_whitespace(t_iniparser *p)
{
	char	*file;

	file = p->file;
	while (file[p->index] && FT_IsSpace(file[p->index]))
	{
		if (file[p->index] == '\n')
			++(p->line);
		else if (
			file[p->index] == '#' ||
			file[p->index] == ';')
		{
			while (file[p->index] && file[p->index] != '\n')
				++(p->index);
			++(p->line);
		}
		++(p->index);
	}
}

static char	*ini_apply_setting(t_iniparser *p)
{
	int index;
	int	i;

	if (*(p->name + p->name_length))
		*(p->name + p->name_length) = '\0';
	i = -1;
	index = -1;
	while (++i < CONFIG_AMOUNT)
		if (rt.config.names[i] && FT_StringEquals(p->name, rt.config.names[i]))
			index = i;
	if (index == -1)
	{
		debug_output_value("Error while reading INI file, at line ",
			FT_Size_To_String(p->line), TRUE);
		debug_output_value("Unable to resolve label name:", p->name, FALSE);
		return (NULL);
	}
	if (*(p->value + p->value_length))
		*(p->value + p->value_length) = '\0';
	if (!(rt.config.values[index] = FT_StringDuplicate(p->value)))
		return ("Could not create config value string");
	return (NULL);
}

static char	*ini_read_setting(t_iniparser *p)
{
	char	*file;

	file = p->file;
	p->name = (p->file + p->index);
	while (file[p->index] && !(FT_IsSpace(file[p->index]) ||
		file[p->index] == '=' ||
		file[p->index] == '#' ||
		file[p->index] == ';'))
		++(p->index);
	p->name_length = (file + p->index) - p->name;
	if (file[p->index] != '=')
		ini_parse_whitespace(p);
	if (file[p->index] != '=')
		return (ini_error('=', " symbol but instead found ", file[p->index]));
	++(p->index);
	ini_parse_whitespace(p);
	if (!file[p->index])
		return ("Unexpected end of file encountered before value.");
	p->value = (file + p->index);
	while (file[p->index] && !FT_IsSpace(file[p->index]))
		++(p->index);
	p->value_length = (file + p->index) - p->value;
	++(p->index);
	return (ini_apply_setting(p));
}

void		ini_read_file(int fd)
{
	t_iniparser	parser;
	char		*error;

	parser.file = NULL;
	if ((FT_Read_File(fd, &parser.file)))
	{
		debug_output_error("Couldn't read INI file.", FALSE);
		return ;
	}
	parser.index = 0;
	parser.line = 1;
	ini_parse_whitespace(&parser);
	while (parser.file[parser.index])
	{
		if ((error = ini_read_setting(&parser)))
		{
			debug_output_value("Error while reading INI file, at line ",
				FT_Size_To_String(parser.line), TRUE);
			debug_output_error(error, FALSE);
			free(error);
		}
		ini_parse_whitespace(&parser);
	}
	free(parser.file);
}
