/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_build_scene.cl                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float16			rt_cl_build_cam_matrix
(
				t_camera	camera
)
{
	float16		cam_mat44 = (float16)(0.f);
	float3		axis_x;
	float3		axis_y;
	float3		axis_z;
	float		sin_val;
	float		cos_val;

	sin_val = sincos(camera.tilt_angle, &cos_val);
	axis_y = (float3)(sin_val, cos_val, 0.f);
	axis_z = normalize(camera.world_pos - camera.anchor);
	axis_x = cross(axis_y, axis_z);
	axis_x = normalize(axis_x);
	axis_y = cross(axis_x, axis_z);

//TODO change here and/or in apply_matrix-s if row major is faster
	cam_mat44.s012 = axis_x;
	cam_mat44.s456 = axis_y;
	cam_mat44.s89A = axis_z;
	cam_mat44.sCDE = camera.world_pos;
	cam_mat44.sF = 1.f;
	return (cam_mat44);
}

/*
** http://www.cs.nthu.edu.tw/~jang/book/addenda/matinv/matinv/
**
**	A homogeneous matrix is one with the last row equal to (0,0,0,1),
**	used to "linearize" the translation operation.
**
**	The page above give a neat formula to simplify our inverse calculation
**	when we choose the block C to be the last row's (0,0,0), D to be (1), etc.
**	To note, since C is null and D is (1), the inverse of the B block in a
**	homogeneous matrix is thus -inv(A)*B, and of the A block is simplu inv(A),
**	while C and D do not change.
**
**	Note that this also implies keeping a "linear" version of our 4*4 matrices
**	is unnecessary, as the corresponding linear_x_to_y matrix is always simply
**	the top left 3*3 block.
*/

static void			rt_cl_build_object_matrices
(
					__global	t_object *	obj
)
{
	float3		pos = obj->pos;
	float3		scale = obj->scale;
	float3		rot = obj->rot;
	float16		rot_mat;
	float16		tmp_mat;

	rot_mat = rt_cl_build_rotation_mat33in44(rot.x, 0);
	tmp_mat = rt_cl_build_rotation_mat33in44(rot.y, 1);
	rot_mat = rt_cl_mat44_mul(tmp_mat, rot_mat);
	tmp_mat = rt_cl_build_rotation_mat33in44(rot.z, 2);
	rot_mat = rt_cl_mat44_mul(tmp_mat, rot_mat);
	tmp_mat = rt_cl_build_diagonal_mat33in44(scale);
	obj->o_to_w = rt_cl_mat44_mul(rot_mat, tmp_mat);
	obj->o_to_w.sCDE = pos;
	//the 3 lines for which there is a big comment above; could be made into a small 'invert homogeneous matrix' function
	tmp_mat = rt_cl_mat33in44_inv(obj->o_to_w);                                                                                                               
	obj->w_to_o = tmp_mat;
	obj->w_to_o.sCDE = rt_cl_apply_linear_matrix(tmp_mat, -pos); //note that this value is the corrected inverse translation considering scaling and rotation
	obj->n_to_w = rt_cl_mat44_transpose(tmp_mat);

	//boolean matrices to round approximate 0s to 0. //TODO make a MAT44ROUND0 function ?
	#if 0
	int16		bool_mat;

	bool_mat = fabs(obj->o_to_w) < (float16)(EPS);
	bool_mat = (int16)(1) - bool_mat;
	tmp_mat = convert_float16(bool_mat);
	obj->o_to_w = obj->o_to_w * tmp_mat;

	bool_mat = fabs(obj->w_to_o) < (float16)(EPS);
	bool_mat = (int16)(1) - bool_mat;
	tmp_mat = convert_float16(bool_mat);
	obj->w_to_o = obj->w_to_o * tmp_mat;

	bool_mat = fabs(obj->n_to_w) < (float16)(EPS);
	bool_mat = (int16)(1) - bool_mat;
	tmp_mat = convert_float16(bool_mat);
	obj->n_to_w = obj->n_to_w * tmp_mat;
	#endif
}

static void			rt_cl_get_vertices_for_bbox
(
					float3 *	vertices,
					t_bbox		aabb
)
{
	vertices[0] = (float3)(aabb.vi.x, aabb.vi.y, aabb.vi.z);
	vertices[1] = (float3)(aabb.vi.x, aabb.vi.y, aabb.vf.z);
	vertices[2] = (float3)(aabb.vi.x, aabb.vf.y, aabb.vi.z);
	vertices[3] = (float3)(aabb.vi.x, aabb.vf.y, aabb.vf.z);
	vertices[4] = (float3)(aabb.vf.x, aabb.vi.y, aabb.vi.z);
	vertices[5] = (float3)(aabb.vf.x, aabb.vi.y, aabb.vf.z);
	vertices[6] = (float3)(aabb.vf.x, aabb.vf.y, aabb.vi.z);
	vertices[7] = (float3)(aabb.vf.x, aabb.vf.y, aabb.vf.z);
}

static t_bbox			rt_cl_build_object_bbox
(
				__global	t_object *		obj
)
{
	float3		objspace_bbox_vertices[8];
	t_bbox		result;
	
	rt_cl_get_vertices_for_bbox(objspace_bbox_vertices, obj->bbox_os);

	#pragma unroll
	for (int i = 0; i < 8; ++i)
	{
		objspace_bbox_vertices[i] = rt_cl_apply_homogeneous_matrix(obj->o_to_w, objspace_bbox_vertices[i]);
	}
	result.vf = result.vi = objspace_bbox_vertices[0];
	#pragma unroll
	for (int i = 1; i < 8; ++i)
	{
		result.vi = fmin(result.vi, objspace_bbox_vertices[i]);
		result.vf = fmax(result.vf, objspace_bbox_vertices[i]);
	}

	return (result);
}

__kernel void	rt_cl_build_scene
(
					__global	t_scene	*	scene
)
{
				int const		obj_id = get_global_id(0);
	__global	t_object *		obj = &(scene->objects[obj_id]);

	scene->camera.c_to_w = rt_cl_build_cam_matrix(scene->camera);
	rt_cl_build_object_matrices(obj);
	obj->bbox_ws = rt_cl_build_object_bbox(obj);

//	debug_print_object(obj);
}
