/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl.debug.cl                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void			debug_print_scene
(
				__constant		t_scene *		scene
)
{
#if CAN_USE_PRINTF
	printf("\n\nScene:\n"
		"\tbg_color = %#x\n"
		"\tbg_rgb = %f %f %f\n"
		"\tobject_amount = %u\n"
		"\trender_dist = %10f\n"
		"\tbbox = %10f %10f %10f | %10f %10f %10f\n"
		"\tmax_ray_depth = %u\n"
		"\tmc_raysamp_size = %u\n"
		,
		scene->bg_color,	
		scene->bg_rgb.x, scene->bg_rgb.y, scene->bg_rgb.z,
		scene->object_amount,
		scene->render_dist,
		scene->bbox_ws.vi.x, scene->bbox_ws.vi.y, scene->bbox_ws.vi.z,
		scene->bbox_ws.vf.x, scene->bbox_ws.vf.y, scene->bbox_ws.vf.z,
		scene->max_ray_depth,
		scene->mc_raysamp_size);
#endif
}

/*
** Use only the lines you need, memory is limited and you might get weird results otherwise
*/
static void			debug_print_object
(
				__global		t_object *		obj
)
{
#if CAN_USE_PRINTF
//	float16		ow;
//	float16		wo;
	float16		nw;


//	ow = rt_cl_mat44_transpose(obj->o_to_w);
//	wo = rt_cl_mat44_transpose(obj->w_to_o);
	nw = rt_cl_mat44_transpose(obj->n_to_w);
	printf("\n\nObject\n"
	//	"\tpos %f %f %f | scale %f %f %f | rot %f %f %f \n"
		"\tcolor %#08x | rgb %f %f %f\n"
		"\ttype %d | material %d | bbox %f %f %f | %f %f %f\n"
	//	"\tobj->o_to_w: \n%10f %10f %10f %10f\n%10f %10f %10f %10f\n%10f %10f %10f %10f\n%10f %10f %10f %10f\n"
	//	"\tobj->w_to_o: \n%10f %10f %10f %10f\n%10f %10f %10f %10f\n%10f %10f %10f %10f\n%10f %10f %10f %10f\n"
		"\tobj->n_to_w: \n%10f %10f %10f %10f\n%10f %10f %10f %10f\n%10f %10f %10f %10f\n%10f %10f %10f %10f\n"
		,
	//	obj->pos.x, obj->pos.y, obj->pos.z, obj->scale.x, obj->scale.y, obj->scale.z, obj->rot.x, obj->rot.y, obj->rot.z,
		obj->color_a, obj->rgb_a.x, obj->rgb_a.y, obj->rgb_a.z,
		obj->type, obj->material, obj->bbox_ws.vi.x, obj->bbox_ws.vi.y, obj->bbox_ws.vi.z, obj->bbox_ws.vf.x, obj->bbox_ws.vf.y, obj->bbox_ws.vf.z,
	//	ow.s0, ow.s1, ow.s2, ow.s3, ow.s4, ow.s5, ow.s6, ow.s7, ow.s8, ow.s9, ow.sA, ow.sB, ow.sC, ow.sD, ow.sE, ow.sF//,
	//	wo.s0, wo.s1, wo.s2, wo.s3, wo.s4, wo.s5, wo.s6, wo.s7, wo.s8, wo.s9, wo.sA, wo.sB, wo.sC, wo.sD, wo.sE, wo.sF//,
		nw.s0, nw.s1, nw.s2, nw.s3, nw.s4, nw.s5, nw.s6, nw.s7, nw.s8, nw.s9, nw.sA, nw.sB, nw.sC, nw.sD, nw.sE, nw.sF
	);
#endif
}

static void			debug_print_camera
(
				__constant		t_camera *		camera
)
{
#if CAN_USE_PRINTF
	float16		c;

	c = rt_cl_mat44_transpose(camera->c_to_w);
	printf("\n\nCamera\n"
		"\tworld_pos %f %f %f | anchor %f %f %f\n"
		"\ttilt %f | hrz_fov %f | aperture %f"
		"\tc_to_w: \n%10f %10f %10f %10f\n%10f %10f %10f %10f\n%10f %10f %10f %10f\n%10f %10f %10f %10f\n"
		,
		camera->world_pos.x, camera->world_pos.y, camera->world_pos.z, camera->anchor.x, camera->anchor.y, camera->anchor.z,
		camera->tilt_angle, camera->hrz_fov, camera->aperture,
		c.s0, c.s1, c.s2, c.s3, c.s4, c.s5, c.s6, c.s7, c.s8, c.s9, c.sA, c.sB, c.sC, c.sD, c.sE, c.sF);
#endif
}
