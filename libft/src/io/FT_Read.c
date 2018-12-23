/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/ft_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_io.h"
#include "../../libft_string.h"

int		ft_readfile(int const fd, char **file)
{
	int		result;
	char	buffer[BUFF_SIZE + 1];
	char	*temp;

	if (!(*file = ft_strnew(1)))
		return (ERROR);
	buffer[BUFF_SIZE] = '\0';
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		temp = *file;
		if (result < BUFF_SIZE)
			buffer[result] = '\0';
		if (!(*file = ft_strjoin(temp, buffer)))
			return (ERROR);
		free(temp);
	}
	if (result < 0)
	{
		if (*file)
			free(*file);
		return (ERROR);
	}
	return (OK);
}

int		ft_readlines(int const fd, char ***strls)
{
/*
** TODO actually code this
*/
	return (fd || strls);
}
