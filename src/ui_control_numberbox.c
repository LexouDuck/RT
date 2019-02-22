/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_control_numberbox.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"
#include "libft_convert.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"

void	ui_mouse_control_numberbox()
{

}

void	ui_render_control_numberbox(int x, int y, cl_float value)
{
	static SDL_Rect	rect = { 0, 0, 9, 3 };
	char			*str;

	rect.x = x;
	rect.y = y;
	ui_render_rect(rect, FALSE);
	if ((str = ft_f32_to_str(value, 3)))
	{
		if (ft_strlen(str) > 6)
			str[6] = '\0';
		ui_render_text(str, rect.x + 1, rect.y + 1, FALSE);
		free(str);
	}
	ui_render_text("\x10", rect.x + rect.w - 2, rect.y + 0, TRUE);
	ui_render_text("\x11", rect.x + rect.w - 2, rect.y + 2, TRUE);
}
