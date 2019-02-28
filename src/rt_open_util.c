/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_open_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"
#include "libft_string.h"
#include "../rt.h"

void		rt_read_whitespace(t_rtparser *p)
{
	char	*file;

	file = p->file;
	while (file[p->index] &&
		(ft_isspace(file[p->index]) || file[p->index] == '/'))
	{
		if (file[p->index] == '\n')
			++(p->line);
		else if (file[p->index] == '/')
		{
			if (file[p->index + 1] == '/')
			{
				while (file[p->index] && file[p->index] != '\n')
					++(p->index);
				++(p->line);
			}
			else
				break ;
		}
		++(p->index);
	}
}

char		*rt_read_error(char expected, char *description, char instead)
{
	char	*result;
	size_t	length;
	size_t	i;

	length = ft_strlen(description);
	if (!(result = (char*)malloc((64 + length) * sizeof(char))))
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
