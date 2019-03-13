/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:05:34 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"
#include "ui.h"

#ifdef __APPLE__
# include <mach-o/getsect.h>
# include <mach-o/ldsyms.h>
#else

void	*getsectiondata(void *ptr, char const *section,
						char const *segment, size_t *size)
{
	if (ptr && section && segment && size)
		return (NULL);
	return (NULL);
}

int _mh_execute_header;

#endif

int		ui_init_assets(void)
{
	size_t	size;

	size = 0;
	rt.ui.chr = getsectiondata(&_mh_execute_header,
		"__DATA", "__inc_ui_chr", &size);
	if (rt.ui.chr == NULL)
		return (debug_perror("Could not load UI assets: GetSectionData()"));
	if (size != CHR_SIZE)
	{
		debug_output_value(
			"Invalid binary size: ", ft_size_to_str(size), TRUE);
		return (ERROR);
	}
	return (OK);
}
