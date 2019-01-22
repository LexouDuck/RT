/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 02:52:55 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/22 01:28:34 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_bool			trace_ray_to_objs(t_control *ctrl, t_ray ray_ws,
									t_object **hit_obj, t_ray *res_ray_os)
{
	t_bool		has_inter;
	t_ray		ray_os;
	int			k;
	t_object	cur_obj;

	k = -1;
	has_inter = FALSE;
	while (++k < ctrl->objlst_len)
	{
		cur_obj = ctrl->objlst[k];
		ray_os = ray_x_to_y(cur_obj.w_to_o, cur_obj.linear_w_to_o, ray_ws);
		if (cur_obj.intersect(&ray_os))
		{
			if (ray_os.t < ray_ws.t)
			{
				has_inter = TRUE;
				ray_ws.t = ray_os.t;
				if (hit_obj)
					*hit_obj = &(ctrl->objlst[k]);
				if (res_ray_os)
					*res_ray_os = ray_os;
			}
		}
	}
	return (has_inter);
}

//TODO this function is basically a copy of the previous one: the code can probably be factored.
t_bool			trace_ray_to_spots(t_control *ctrl, t_ray ray_ws,
									t_object **hit_spot, t_ray *res_lgtray_os)
{
	t_bool		has_inter;
	t_ray		ray_os;
	int			k;
	t_object	cur_spot;

	k = -1;
	has_inter = FALSE;
	while (++k < ctrl->spotlst_len)
	{
		cur_spot = ctrl->spotlst[k];
		ray_os = ray_x_to_y(cur_spot.w_to_o, cur_spot.linear_w_to_o, ray_ws);
		if (cur_spot.intersect(&ray_os))
		{
			if (ray_os.t < ray_ws.t)
			{
				has_inter = TRUE;
				ray_ws.t = ray_os.t;
				if (hit_spot)
					*hit_spot = &(ctrl->spotlst[k]);
				if (res_lgtray_os)
					*res_lgtray_os = ray_os;
			}
		}
	}
	return (has_inter);
}

t_vcolor		trace_ray_to_scene(t_control *ctrl, t_shader shdr)
{
	t_bool		has_inter;
	t_vcolor	reslum;
	t_object 	*hit_obj;
	t_ray		ray_os;

	has_inter = trace_ray_to_objs(ctrl, shdr.out_ray_ws, &hit_obj, &ray_os);
	if (has_inter)
		shdr.out_ray_ws.t = ray_os.t;
	has_inter = (trace_ray_to_spots(ctrl, shdr.out_ray_ws, &hit_obj, &ray_os)
								|| has_inter);
	if (has_inter)
		reslum = resolve_intersection(ctrl, shdr, hit_obj, ray_os);
	else
		reslum.val = (t_rgb){0., 0., 0.};
	return (reslum);
}
