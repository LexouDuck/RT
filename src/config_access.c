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
	if (g_rt.config.names[index])
	{
		if (g_rt.config.values[index])
			return (g_rt.config.values[index]);
		else
			return (g_rt.config.defaults[index]);
	}
	return (NULL);
}

inline void		config_set(int index, char *value)
{
	if (g_rt.config.names[index])
	{
		if (g_rt.config.values[index])
		{
			free(g_rt.config.values[index]);
		}
		g_rt.config.values[index] = value;
	}
}
