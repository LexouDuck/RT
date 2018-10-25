/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static char	*read_error(char expected, char *description, char instead)
{
	char	*result;
	size_t	length;
	size_t	i;

	length = ft_strlen(description);
	if (!(result = malloc((64 + length) * sizeof(char))))
		return (NULL);
	i = 0;
	ft_strcpy(result, "Expected \'");
	i += 10;
	result[i++] = expected;
	ft_strcpy(result + i, "\' (");
	i += 3;
	ft_strcpy(result + i, description);
	i += length;
	ft_strcpy(result + i, "), but instead found: \'");
	i += 21;
	result[i++] = instead;
	return (result);
}

static char	*read_vector_arg_number(t_parser *parser, float *result, char sep)
{
	char	*file;
	char	*number;

	read_whitespace(parser);
	file = parser->file;
	number = file + parser->index;
	while (file[parser->index] &&
		(ft_isdigit(file[parser->index]) ||
			file[parser->index] == '+' ||
			file[parser->index] == '-' ||
			file[parser->index] == '.'))
		++(parser->index);
	if (!file[parser->index])
		return ("Unexpected end of file inside vector argument");
	read_whitespace(parser);
	if (file[parser->index] != sep)
		return (read_error(sep, "separator char", file[parser->index]));
	file[parser->index] = '\0';
	++(parser->index);
	*result = ft_atof(number);
	return (NULL);
}

char		*read_vector_arg(t_parser *parser, t_vector *result)
{
	char	*error;
	char	symbol;

	read_whitespace(parser);
	if (!parser->file[parser->index])
		return ("Expected vector argument, reached end of file");
	symbol = parser->file[parser->index];
	if (symbol == '(' || symbol == '{' || symbol == '[')
		++(parser->index);
	else
		return (read_error('(', "or '{' or '[' => vector argument", symbol));
	symbol += (symbol == '(') ? 1 : 2;
	if ((error = read_vector_arg_number(parser, &(result->x), ',')))
		return (error);
	if ((error = read_vector_arg_number(parser, &(result->y), ',')))
		return (error);
	if ((error = read_vector_arg_number(parser, &(result->z), symbol)))
		return (error);
	return (NULL);
}

char		*read_number_arg(t_parser *parser, float *result)
{
	char	c;
	char	*file;
	char	*number;

	read_whitespace(parser);
	file = parser->file;
	c = file[parser->index];
	if (c == '\0')
		return ("Expected number argument, reached end of file");
	else if (ft_isdigit(c))
	{
		number = file + parser->index;
		while (file[parser->index] &&
			(ft_isdigit(file[parser->index]) || file[parser->index] == '.'))
			++(parser->index);
		if (file[parser->index] == '\n')
			parser->line += 1;
		file[parser->index] = '\0';
		++(parser->index);
		*result = ft_atof(number);
		return (NULL);
	}
	return (read_error('0', "or any other digit, for a number argument", c));
}

char		*read_color_arg(t_parser *parser, t_u32 *result)
{
	char	c;
	char	*file;
	char	*color;

	read_whitespace(parser);
	file = parser->file;
	c = file[parser->index];
	if (c == '\0')
		return ("Expected color argument, reached end of file");
	else if (c == '#')
	{
		++(parser->index);
		color = file + parser->index;
		while ((c = file[parser->index]) && (ft_isdigit(c) ||
			('A' <= c && c <= 'F') || ('a' <= c && c <= 'f')))
			++(parser->index);
		if (file[parser->index] == '\n')
			parser->line += 1;
		file[parser->index] = '\0';
		++(parser->index);
		*result = ft_atoi_hex(color);
		return (NULL);
	}
	return (read_error('#', "starting char for color arg", c));
}
