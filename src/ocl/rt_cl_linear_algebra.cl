/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_linear_algebra.cl                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline float		rt_cl_float3_ynull_dot
(
							float3 v1,
							float3 v2
)
{
	return (v1.x * v2.x + v1.z * v2.z);
}

static inline float		rt_cl_float3_yneg_dot
(
							float3 v1, 
							float3 v2
)
{
	return (v1.x * v2.x - v1.y * v2.y + v1.z * v2.z);
}

static bool				rt_cl_get_realroots_quadpoly
(
							float2 *	roots,
							float3		quadpoly
)
{
	float		delta;
	float		one_over_two_a;

	delta = quadpoly.y * quadpoly.y - 4.f * quadpoly.x * quadpoly.z;
	if (delta < 0.f)
	{
		roots->x = roots->y = 0.f / 0.f;
		return (false);
	}
	one_over_two_a = 0.5f / quadpoly.x;
	delta = sqrt(delta);
	roots->x = (-quadpoly.y + delta) * one_over_two_a;
	roots->y = (-quadpoly.y - delta) * one_over_two_a;
	return (true);
}


static float16			rt_cl_mat44_transpose(float16 mat44)
{
	return (mat44.s048C159D26AE37BF);
}


static float3			rt_cl_apply_linear_matrix(float16 mat44, float3 vec3)
{
	float3		res;

	res.x = dot(mat44.s048, vec3);
	res.y = dot(mat44.s159, vec3);
	res.z = dot(mat44.s26A, vec3);
	return (res);
}


static float3			rt_cl_apply_homogeneous_matrix(float16 mat44, float3 vec3)
{
	float4		tmp;
	float3		res;

	tmp.xyz = vec3;
	tmp.w = 1.f;
	res.x = dot(mat44.s048C, tmp);
	res.y = dot(mat44.s159D, tmp);
	res.z = dot(mat44.s26AE, tmp);
	return (res);
}


static float16			rt_cl_build_diagonal_mat33in44(float3 diag)
{
	float16		result = (float16)(0.f);

	result.s05AF = (float4)(diag.x, diag.y, diag.z, 1.f);
	return (result);
}


static float16			rt_cl_build_rotation_mat33in44(float theta, int axis)
{
	float16		result;
	float		c_th;
	float		s_th;

	result = rt_cl_build_diagonal_mat33in44((float3)(1.f, 1.f, 1.f));
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


static float16			rt_cl_mat44_mul(float16 const mat_A, float16 const mat_B)
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


static float			rt_cl_mat33in44_det(float16 const mat33in44)
{
	return (mat33in44.s0 * mat33in44.s5 * mat33in44.sA
			+ mat33in44.s1 * mat33in44.s6 * mat33in44.s8
			+ mat33in44.s2 * mat33in44.s4 * mat33in44.s9
			- mat33in44.s2 * mat33in44.s5 * mat33in44.s8
			- mat33in44.s1 * mat33in44.s4 * mat33in44.sA
			- mat33in44.s0 * mat33in44.s6 * mat33in44.s9);
}


/*
** M^-1 = 1/det * adj(m) and adj(m) = comat(m^transpose)
*/

static float16			rt_cl_mat33in44_inv(float16 const mat33)
{
	float		det;
	float16		result;

	if (fabs((det = rt_cl_mat33in44_det(mat33))) < EPS)
		return ((float16)(0.f / 0.f));
	result.s0 = mat33.s5 * mat33.sA - mat33.s6 * mat33.s9;
	result.s4 = mat33.s6 * mat33.s8 - mat33.s4 * mat33.sA;
	result.s8 = mat33.s4 * mat33.s9 - mat33.s5 * mat33.s8;
	result.s1 = mat33.s2 * mat33.s9 - mat33.s1 * mat33.sA;
	result.s5 = mat33.s0 * mat33.sA - mat33.s2 * mat33.s8;
	result.s9 = mat33.s1 * mat33.s8 - mat33.s0 * mat33.s9;
	result.s2 = mat33.s1 * mat33.s6 - mat33.s2 * mat33.s5;
	result.s6 = mat33.s2 * mat33.s4 - mat33.s0 * mat33.s6;
	result.sA = mat33.s0 * mat33.s5 - mat33.s1 * mat33.s4;
	result = (float16)(native_recip((float)det)) * (result);
	result.s37B = (float3)(0.f, 0.f, 0.f);
	result.sCDEF = (float4)(0.f, 0.f, 0.f, 1.f);                                                                                                                      
	return (result);
}
