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

#include "../rt.h"

inline char		*config_get(int index)
{
	if (rt.config.names[index])
	{
		if (rt.config.values[index])
			return (rt.config.values[index]);
		else
			return (rt.config.defaults[index]);
	}
	return (NULL);
}

inline void		config_set(int index, char *value)
{
	if (rt.config.names[index])
	{
		if (rt.config.values[index])
		{
			free(rt.config.values[index]);
		}
		rt.config.values[index] = value;
	}
}
