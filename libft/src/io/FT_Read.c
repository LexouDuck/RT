/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FT_Read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_io.h"
#include "../../libft_string.h"

char			*read_file(int const fd)
{
	int		result;
	char	buffer[BUFF_SIZE + 1];
	char	*file;
	char	*temp;

	file = ft_strnew(1);
	buffer[BUFF_SIZE] = '\0';
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		temp = file;
		if (result < BUFF_SIZE)
			buffer[result] = '\0';
		if (!(file = ft_strjoin(temp, buffer)))
			return (NULL);
		free(temp);
	}
	if (result < 0)
	{
		if (file)
			free(file);
		return (NULL);
	}
	return (file);
}
