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
	printf("\n\nScene:\n"
	"\tbg_color = %#x\n"
	"\tbg_rgb = %g %g %g\n"
	"\tobject_amount = %u\n"
	"\trender_dist = %10g\n"
	"\tbbox = %10g %10g %10g | %10g %10g %10g\n"
	"\tmax_ray_depth = %u\n"
	"\tmc_raysamp_size = %u\n",
	scene->bg_color,	
	scene->bg_rgb.x, scene->bg_rgb.y, scene->bg_rgb.z,
	scene->object_amount,
	scene->render_dist,
	scene->bbox_ws.vi.x, scene->bbox_ws.vi.y, scene->bbox_ws.vi.z, scene->bbox_ws.vf.x, scene->bbox_ws.vf.y, scene->bbox_ws.vf.z,
	scene->max_ray_depth,
	scene->mc_raysamp_size);
}

/*
** Use only the lines you need, memory is limited and you might get weird results otherwise
*/
static void			debug_print_object
(
				__global		t_object *		obj
)
{
//	float16		ow;
//	float16		wo;
	float16		nw;


//	ow = rt_cl_mat44_transpose(obj->o_to_w);
//	wo = rt_cl_mat44_transpose(obj->w_to_o);
	nw = rt_cl_mat44_transpose(obj->n_to_w);
	printf("\n\nObject\n"
	//		"\tpos %g %g %g | scale %g %g %g | rot %g %g %g \n"
			"\tcolor %#08x | rgb %g %g %g\n"
			"\ttype %d | material %d | bbox %g %g %g    %g %g %g\n"
	//		"\tobj->o_to_w: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n"
	//		"\tobj->w_to_o: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n"
			"\tobj->n_to_w: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n"
			,
	//obj->pos.x, obj->pos.y, obj->pos.z, obj->scale.x, obj->scale.y, obj->scale.z, obj->rot.x, obj->rot.y, obj->rot.z,
	obj->color_a, obj->rgb_a.x, obj->rgb_a.y, obj->rgb_a.z,
	obj->type, obj->material, obj->bbox_ws.vi.x, obj->bbox_ws.vi.y, obj->bbox_ws.vi.z, obj->bbox_ws.vf.x, obj->bbox_ws.vf.y, obj->bbox_ws.vf.z,
//	ow.s0, ow.s1, ow.s2, ow.s3, ow.s4, ow.s5, ow.s6, ow.s7, ow.s8, ow.s9, ow.sA, ow.sB, ow.sC, ow.sD, ow.sE, ow.sF//,
//	wo.s0, wo.s1, wo.s2, wo.s3, wo.s4, wo.s5, wo.s6, wo.s7, wo.s8, wo.s9, wo.sA, wo.sB, wo.sC, wo.sD, wo.sE, wo.sF//,
	nw.s0, nw.s1, nw.s2, nw.s3, nw.s4, nw.s5, nw.s6, nw.s7, nw.s8, nw.s9, nw.sA, nw.sB, nw.sC, nw.sD, nw.sE, nw.sF
	);
}

static void			debug_print_camera
(
				__constant		t_camera *		camera
)
{
	float16		c;

	c = rt_cl_mat44_transpose(camera->c_to_w);
	printf("\n\nCamera\n"
			"\tworld_pos %g %g %g | anchor %g %g %g\n"
			"\ttilt %g | hrz_fov %g | aperture %g"
			"\tc_to_w: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n",
		camera->world_pos.x, camera->world_pos.y, camera->world_pos.z, camera->anchor.x, camera->anchor.y, camera->anchor.z,
		camera->tilt_angle, camera->hrz_fov, camera->aperture,
		c.s0, c.s1, c.s2, c.s3, c.s4, c.s5, c.s6, c.s7, c.s8, c.s9, c.sA, c.sB, c.sC, c.sD, c.sE, c.sF);
}
