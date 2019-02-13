float16			rt_cl_mat44_transpose(float16 mat44)
{
	return (mat44.s048C159D26AE37BF);
}


float3			rt_cl_apply_linear_matrix(float16 mat44, float3 vec3)
{
	float3		res;

	res.x = dot(mat44.s048, vec3);
	res.y = dot(mat44.s159, vec3);
	res.z = dot(mat44.s26A, vec3);
	return (res);
}


float3			rt_cl_apply_homogeneous_matrix(float16 mat44, float3 vec3)
{
	float4		tmp;
	float3		res;

	tmp.xyz = vec3;
	tmp.w = 1.;
	res.x = dot(mat44.s048C, tmp);
	res.y = dot(mat44.s159D, tmp);
	res.z = dot(mat44.s26AE, tmp);
	return (res);
}

float16			rt_cl_build_diagonal_mat33in44(float3 diag)
{
	float16		result = (float16)(0.);

	result.s05AF = (float4)(diag.x, diag.y, diag.z, 1.);
	return (result);
}

float16			rt_cl_build_rotation_mat33in44(float theta, int axis)
{
	float16		result;
	float		c_th;
	float		s_th;

	result = rt_cl_build_diagonal_mat33in44((float3)(1., 1., 1.));
	axis = axis % 3;
	s_th = sincos(theta, &c_th);
	if (axis == 0)
		result.s5A69 = (float4)(c_th, c_th, s_th, -s_th);
	else if (axis == 1)
		result.sA082 = (float4)(c_th, c_th, s_th, -s_th);
	else
		result.s0514 = (float4)(c_th, c_th, s_th, -s_th);
	return (result);
}

float16			rt_cl_mat44_mul(float16 const mat_A, float16 const mat_B)
{
	float16		mat_C;

	mat_C.s0 = dot(mat_A.s048C, mat_B.s0123);
	mat_C.s1 = dot(mat_A.s159D, mat_B.s0123);
	mat_C.s2 = dot(mat_A.s26AE, mat_B.s0123);
	mat_C.s3 = dot(mat_A.s37BF, mat_B.s0123);
	mat_C.s4 = dot(mat_A.s048C, mat_B.s4567);
	mat_C.s5 = dot(mat_A.s159D, mat_B.s4567);
	mat_C.s6 = dot(mat_A.s26AE, mat_B.s4567);
	mat_C.s7 = dot(mat_A.s37BF, mat_B.s4567);
	mat_C.s8 = dot(mat_A.s048C, mat_B.s89AB);
	mat_C.s9 = dot(mat_A.s159D, mat_B.s89AB);
	mat_C.sA = dot(mat_A.s26AE, mat_B.s89AB);
	mat_C.sB = dot(mat_A.s37BF, mat_B.s89AB);
	mat_C.sC = dot(mat_A.s048C, mat_B.sCDEF);
	mat_C.sD = dot(mat_A.s159D, mat_B.sCDEF);
	mat_C.sE = dot(mat_A.s26AE, mat_B.sCDEF);
	mat_C.sF = dot(mat_A.s37BF, mat_B.sCDEF);
	return (mat_C);
}


float			rt_cl_mat33in44_det(float16 const mat33)
{
	return (mat33.s0 * mat33.s5 * mat33.sA
			+ mat33.s1 * mat33.s6 * mat33.s8
			+ mat33.s2 * mat33.s4 * mat33.s9
			- mat33.s2 * mat33.s5 * mat33.s8
			- mat33.s1 * mat33.s4 * mat33.sA
			- mat33.s0 * mat33.s6 * mat33.s9);
}


/*
** M^-1 = 1/det * adj(m) and adj(m) = comat(m^transpose)
*/

float16			rt_cl_mat33in44_inv(float16 const mat33)
{
	float		det;
	float16		result;

	if ((det = rt_cl_mat33in44_det(mat33)) == 0.)
		return ((float16)(0. / 0.));
	result.s0 = mat33.s5 * mat33.sA - mat33.s6 * mat33.s9;
	result.s4 = mat33.s6 * mat33.s8 - mat33.s4 * mat33.sA;
	result.s8 = mat33.s4 * mat33.s9 - mat33.s5 * mat33.s8;
	result.s1 = mat33.s2 * mat33.s9 - mat33.s1 * mat33.sA;
	result.s5 = mat33.s0 * mat33.sA - mat33.s2 * mat33.s8;
	result.s9 = mat33.s1 * mat33.s8 - mat33.s0 * mat33.s9;
	result.s2 = mat33.s1 * mat33.s6 - mat33.s2 * mat33.s5;
	result.s6 = mat33.s2 * mat33.s4 - mat33.s0 * mat33.s6;
	result.sA = mat33.s0 * mat33.s5 - mat33.s1 * mat33.s4;
	result.sF = 1.;
	result.s37B = (float3)(0., 0., 0.);
	result.sCDE = (float3)(0., 0., 0.);
	result = (float16)(1. / det) * (result); //TODO use native_recip ?
	return (result);
}






float16			rt_cl_build_cam_matrix
(
				t_camera	camera
)
{
	float16		cam_mat44 = (float16)(0.);
	float3		axis_x;
	float3		axis_y;
	float3		axis_z;
	float		sin_val;
	float		cos_val;

	sin_val = sincos(camera.tilt, &cos_val);
	axis_y = (float3)(sin_val, cos_val, 0.);
	axis_z = normalize(camera.anchor - camera.world_pos);
	axis_x = cross(axis_y, axis_z);
	axis_x = normalize(axis_x);
	axis_y = cross(axis_x, axis_z);

//TODO change here and/or in apply_matrix-s if row major is faster
	cam_mat44.s012 = axis_x;
	cam_mat44.s345 = axis_y;
	cam_mat44.s89A = axis_z;
	cam_mat44.sCDE = camera.world_pos;
	cam_mat44.sF = 1.;
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

void			rt_cl_build_object_matrices
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
	tmp_mat = rt_cl_mat33in44_inv(rot_mat);
	obj->w_to_o = tmp_mat;
	obj->w_to_o.sCDE = rt_cl_apply_linear_matrix(tmp_mat, -pos); //note that this value is the corrected inverse translation considering scaling and rotation
	obj->n_to_w = rt_cl_mat44_transpose(tmp_mat);
}





void			rt_cl_get_vertices_for_bbox
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

t_bbox			rt_cl_build_object_bbox
(
							t_primitive		type,
							float16			o_to_w,
							float			render_dist
)
{
	t_bbox		objspace_bbox;
	float3		objspace_bbox_vertices[8];
	t_bbox		result;

	if (type == sphere || type == cube)
	{
		objspace_bbox = (t_bbox){(float3)(-0.5, -0.5, -0.5),
									(float3)(0.5, 0.5, 0.5)};
	}
	else
	{
		return ((t_bbox){(float3)(-render_dist, -render_dist, -render_dist),
							(float3)(render_dist, render_dist, render_dist)});
	}
	rt_cl_get_vertices_for_bbox(objspace_bbox_vertices, objspace_bbox);

	#pragma unroll
	for (int i = 0; i < 8; ++i)
	{
		objspace_bbox_vertices[i] = rt_cl_apply_homogeneous_matrix(o_to_w, objspace_bbox_vertices[i]);
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
	obj->bbox = rt_cl_build_object_bbox(obj->type, obj->o_to_w, scene->render_dist);
	//TODO sort objects by type and material
}