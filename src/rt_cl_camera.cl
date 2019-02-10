float16			rt_cl_mat44_transpose(float16 mat)
{
	return (mat.s048C159D26AE37BF);
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

float16			rt_cl_init_cam
(
				float3		world_pos,
				float3		anchor,
				float		tilt
)
{
	float16		cam_mat44 = {0};
	float3		axis_x;
	float3		axis_y;
	float3		axis_z;
	float		sin_val;
	float		cos_val;

	sin_val = sincos(tilt, &cos_val);
	axis_y = (float3)(sin_val, cos_val, 0.);
	axis_z = normalize(anchor - world_pos);
	axis_x = cross(axis_y, axis_z);
	axis_x = normalize(axis_x);
	axis_y = cross(axis_x, axis_z);

//TODO change here and/or in apply_matrix-s if row major is faster
	cam_mat44.s012 = axis_x;
	cam_mat44.s345 = axis_y;
	cam_mat44.s89A = axis_z;
	cam_mat44.sCDE = world_pos;
	cam_mat44.sF = 1.;
	return (cam_mat44);
}
