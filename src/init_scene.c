/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		init_scene(void)
{
	rt.scene.camera.world_pos = DEFAULT_CAM_POS;
	rt.scene.camera.anchor = DEFAULT_CAM_ANCHOR;
	rt.scene.camera.tilt = DEFAULT_CAM_TILT;
	rt.scene.camera.hrz_fov = DEFAULT_CAM_FOV;
	rt.scene.camera.aperture = DEFAULT_CAM_APERTURE;
//	rt.scene.camera.c_to_w = (cl_float16){0., 0., 0., 0., 0., 0., 0., 0.,
//										0., 0., 0., 0., 0., 0., 0., 0.};
	rt.scene.camera.mode = CAMERA_NONE;


	rt.scene.bg_color = BG_COLOR;
	rt.scene.bg_rgb = (cl_float3){(BG_COLOR & 0xFF0000) >> 16, (BG_COLOR & 0xFF00) >> 8, BG_COLOR & 0xFF};
	rt.scene.object_amount = 0;
	rt.scene.render_dist = DEFAULT_RENDER_DIST;
	rt.scene.bbox.vi = (cl_float3){-DEFAULT_RENDER_DIST, -DEFAULT_RENDER_DIST, -DEFAULT_RENDER_DIST};
	rt.scene.bbox.vf = (cl_float3){DEFAULT_RENDER_DIST, DEFAULT_RENDER_DIST, DEFAULT_RENDER_DIST};
	rt.scene.max_ray_depth = DEFAULT_MAX_RAY_DEPTH;
	rt.scene.mc_raysamp_size = DEFAULT_RAYSAMP_SIZE;
}