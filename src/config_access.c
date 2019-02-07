/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

inline char*	config_get(int index)
{
	if (config.names[index])
	{
		if (config.values[index])
			return (config.values[index]);
		else
			return (config.defaults[index]);
	}
	return (NULL);
}

inline void		config_set(int index, char* value)
{
	if (config.names[index])
	{
		if (config.values[index])
		{
			free(config.values[index]);
		}
		config.values[index] = value;
	}
}
