/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 02:52:55 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/11 01:15:00 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_bool			trace_ray_to_objs(t_control *ctrl, t_ray ray,
									t_object *hit_obj, t_ray *res_objray)
{
	t_bool		has_inter;
	t_ray		objray;
	int			k;
	t_object	cur_obj;

	k = -1;
	has_inter = FALSE;
	while (++k < ctrl->objlst_len)
	{
		cur_obj = ctrl->objlst[k];
		objray = ray_x_to_y(cur_obj.w_to_o, cur_obj.linear_w_to_o, ray);
		if (cur_obj.intersect(&objray))
		{
			if (objray.t < ray.t)
			{
				has_inter = TRUE;
				ray.t = objray.t;
				if (hit_obj)
					*hit_obj = ctrl->objlst[k];
				if (res_objray)
					*res_objray = objray;
			}
		}
	}
	return (has_inter);
}

//TODO this function is basically a copy of the previous one: the code can probably be factored.
t_bool			trace_ray_to_spots(t_control *ctrl, t_ray ray,
									t_object *hit_spot, t_ray *res_lgtray)
{
	t_bool		has_inter;
	t_ray		objray;
	int			k;
	t_object	cur_spot;

	k = -1;
	has_inter = FALSE;
	while (++k < ctrl->spotlst_len)
	{
		cur_spot = ctrl->spotlst[k];
		objray = ray_x_to_y(cur_spot.w_to_o, cur_spot.linear_w_to_o, ray);
		if (cur_spot.intersect(&objray))
		{
			if (objray.t < ray.t)
			{
				has_inter = TRUE;
				ray.t = objray.t;
				if (hit_spot)
					*hit_spot = ctrl->spotlst[k];
				if (res_lgtray)
					*res_lgtray = objray;
			}
		}
	}
	return (has_inter);
}

t_vcolor		trace_ray_to_scene(t_control *ctrl, t_shader shdr)
{
	t_bool		has_inter;
	t_vcolor	reslum;
	t_object 	hit_obj;
	t_ray		objray;

	has_inter = trace_ray_to_objs(ctrl, shdr.out_ray_ws, &hit_obj, &objray);
	if (has_inter)
		shdr.out_ray_ws.t = objray.t;
	has_inter = (trace_ray_to_spots(ctrl, shdr.out_ray_ws, &hit_obj, &objray)
								|| has_inter);
	if (has_inter)
	{
		shdr.out_ray_ws.t = objray.t;
		reslum = resolve_intersection(ctrl, shdr, &hit_obj, objray);
	}
	else
		reslum.val = (t_rgb){0., 0., 0.};
	return (reslum);
}
