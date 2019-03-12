/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft_color.h"
#include "libft_memory.h"

#include "../rt.h"

void		init_scene(void)
{
	rt.scene.bg_color = DEFAULT_BG_COLOR;
	rt.scene.bg_rgb = (cl_float3){{
		(DEFAULT_BG_COLOR & 0xFF0000) >> 16,
		(DEFAULT_BG_COLOR & 0x00FF00) >> 8,
		(DEFAULT_BG_COLOR & 0x0000FF) }};
	rt.scene.object_amount = 0;
	rt.scene.render_dist = DEFAULT_RENDER_DIST;
	rt.scene.bbox_ws.vi = (cl_float3){{
		-DEFAULT_RENDER_DIST,
		-DEFAULT_RENDER_DIST,
		-DEFAULT_RENDER_DIST }};
	rt.scene.bbox_ws.vf = (cl_float3){{
		DEFAULT_RENDER_DIST,
		DEFAULT_RENDER_DIST,
		DEFAULT_RENDER_DIST }};
	rt.scene.max_ray_depth = DEFAULT_MAX_RAY_DEPTH;
	rt.scene.mc_raysamp_size = DEFAULT_RAYSAMP_SIZE;
	rt.scene.work_dim[0] = rt.canvas_w;
	rt.scene.work_dim[1] = rt.canvas_h;
	rt.scene.render_mode = DEFAULT_RENDER_MODE;
}

void		update_scene(void)
{
	rt.scene.bg_color = ft_color_argb32_set(0.,
		rt.scene.bg_rgb.x * 255.,
		rt.scene.bg_rgb.y * 255.,
		rt.scene.bg_rgb.z * 255.);
}

static void	rt_object_init_bbox(t_object *object)
{
	float	render_dist;

	render_dist = rt.scene.render_dist;
	//TODO merge hyperboloid and infcone with else ?
	if (object->type == sphere || object->type == cube || object->type == cylinder)
		object->bbox_os = (t_bbox){
			(cl_float3){{-1.f - EPS, -1.f - EPS, -1.f - EPS}},
			(cl_float3){{1.f + EPS, 1.f + EPS, 1.f + EPS}}};
	else if (object->type == plane)
		object->bbox_os = (t_bbox){
			(cl_float3){{-render_dist, -EPS, -render_dist}},
			(cl_float3){{render_dist, EPS, render_dist}}};
	else if (object->type == rectangle || object->type == disk)
		object->bbox_os = (t_bbox){
			(cl_float3){{-1.f - EPS, -EPS, -1.f - EPS}},
			(cl_float3){{1.f + EPS, EPS, 1.f + EPS}}};
	else if (object->type == triangle)
		object->bbox_os = (t_bbox){
			(cl_float3){{-0.5f - EPS, -EPS, -EPS}},
			(cl_float3){{0.5f + EPS, EPS, 1.f + EPS}}};
	else if (object->type == infcylinder)
		object->bbox_os = (t_bbox){
			(cl_float3){{-1.f - EPS, -render_dist, -1.f - EPS}},
			(cl_float3){{1.f + EPS, render_dist, 1.f + EPS}}};
	else if (object->type == paraboloid)
		object->bbox_os = (t_bbox){
			(cl_float3){{-sqrt(render_dist), 0.f - EPS, -sqrt(render_dist)}},
			(cl_float3){{sqrt(render_dist), render_dist, sqrt(render_dist)}}};
	else if (object->type == hyperboloid)
		object->bbox_os = (t_bbox){
			(cl_float3){{-render_dist, -render_dist, -render_dist}},
			(cl_float3){{render_dist, render_dist, render_dist}}};
	else if (object->type == cone)
		object->bbox_os = (t_bbox){
			(cl_float3){{-1.f - EPS, 0.f - EPS, -1.f - EPS}},
			(cl_float3){{1.f + EPS, 1.f + EPS, 1.f + EPS}}};
	else if (object->type == infcone)
		object->bbox_os = (t_bbox){
			(cl_float3){{-render_dist, -render_dist, -render_dist}},
			(cl_float3){{render_dist, render_dist, render_dist}}};
	else
		object->bbox_os = (t_bbox){
			(cl_float3){{-render_dist, -render_dist, -render_dist}},
			(cl_float3){{render_dist, render_dist, render_dist}}};
}

void		init_object(t_object *object)
{
	object->material = diffuse;
	object->pattern = solid;
	object->uvw_projection = spherical;
	object->bump_type = flat;
	ft_memclr(&object->name, OBJECT_NAME_MAXLENGTH);
	object->color_a = 0xFFFFFF;
	object->color_b = 0x000000;
	object->rgb_a = (cl_float3){{ 1., 1., 1. }};
	object->rgb_b = (cl_float3){{ 0., 0., 0. }};
	object->pos = (cl_float3){{ 0., 0., 0. }};
	object->rot = (cl_float3){{ 0., 0., 0. }};
	object->scale = (cl_float3){{ 1., 1., 1. }};
	object->uvw_scale = (cl_float3){{ 1., 1., 1. }};
	object->uvw_offset = (cl_float3){{ 0., 0., 0. }};
	object->refrac = DEFAULT_OBJECT_REFRAC;
	object->roughness = DEFAULT_OBJECT_ROUGHNESS;
	object->opacity = DEFAULT_OBJECT_OPACITY;
	rt_object_init_bbox(object);
}

void		update_object(t_object *object)
{
	object->color_a = ft_color_argb32_set(0.,
		object->rgb_a.x * 255.,
		object->rgb_a.y * 255.,
		object->rgb_a.z * 255.);
	object->color_b = ft_color_argb32_set(0.,
		object->rgb_b.x * 255.,
		object->rgb_b.y * 255.,
		object->rgb_b.z * 255.);
}
