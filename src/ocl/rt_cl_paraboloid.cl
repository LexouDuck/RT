static float3		cl_float3_eucl_nrmlz
(
					float3 		vector
)
{
	float		inv_norm;

	inv_norm = 1. / sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	vector.x = vector.x * inv_norm;
	vector.y = vector.y * inv_norm;
	vector.z = vector.z * inv_norm;
	return (vector);

}

/*
** The paraboloid primitive is the set of points made by the rotation of the
**	curve x^2 = y around the y-axis.
**
** Any point on this primitive verifies x^2 + z^2 == y; thus one must find
**	r = o + td
**	(o+td)_x^2 + (o+td)_z^2 - (o+td)_y			== 0		<=>
**
**	(ox + t dx)^2 + (oz + t dz)^2 - (oy + t dy)	== 0		<=>
**
**	(ox^2 + oz^2 - oy)						+				<=>
**	(2 * (oxdx + ozdz) - dy)	* t			+
**	(dx^2 + dz^2)				* t^2			== 0
*/
static t_intersection		rt_cl_paraboloid_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3		quadpoly;
	float2		roots;

	quadpoly.x = rt_cl_float3_ynull_dot(ray.dir, ray.dir);
	quadpoly.y = 2 * rt_cl_float3_ynull_dot(ray.dir, ray.pos) - ray.dir.y;
	quadpoly.z = rt_cl_float3_ynull_dot(ray.pos, ray.pos) - ray.pos.y;
	if (!(rt_cl_get_realroots_quadpoly(&roots, quadpoly)))
		return (INTER_NONE);
	if (roots.x <= 0. && roots.y <= 0.)
		return (INTER_NONE);
	else if (roots.x <= 0.)
	{
		*res = roots.y;
		return (INTER_INSIDE);
	}
	else if (roots.y <= 0.)
	{
		*res = roots.x;
		return (INTER_INSIDE);
	}
	else
	{
		*res = fmin(roots.x, roots.y);
		return (INTER_OUTSIDE);
	}
}

/*
** To find the normal of a parabola, consider the fact that a parabola is a
** manifold and can thus be described as though its calculus form.
**
** Our scalar function for our hypersurface is f(x, y, z) = x^2 - y + z^2
** Its jacobian matrix is thus the 1×3 matrix [ 2x, -1, 2z ]
*/
static float3			rt_cl_paraboloid_get_normal
(
						float3 hitpos
)
{
	float3		normal;

	normal = (float3)(2 * hitpos.x, -1., 2 * hitpos.z);
	normal = cl_float3_eucl_nrmlz(normal);
	return(normal);

//	return((float3)(2 * hitpos.x, -1., 2 * hitpos.z));
}

#if 0
/*
** The paraboloid primitive is the set of points made by the rotation of the
**	curve x^2 = y around the y-axis.
**
** Any point on this primitive verifies x^2 - z^2 == y; thus one must find
**	r = o + td
**	(o+td)_x^2 - (o+td)_z^2 - (o+td)_y			== 0		<=>
**
**	(ox + t dx)^2 - (oz + t dz)^2 - (oy + t dy)	== 0		<=>
**
**	(ox^2 - oz^2 - oy)						+				<=>
**	(2 * (oxdx - ozdz) - dy)	* t			+
**	(dx^2 - dz^2)				* t^2			== 0
**
t_bool						intersect_ray_saddle(t_ray *objray)
{
	t_vec_3d	quadpoly;
	t_float		root1;
	t_float		root2;

	quadpoly[0] = objray->dir[0] * objray->dir[0]
					- objray->dir[2] * objray->dir[2];
	quadpoly[1] = 2 * (objray->dir[0] * objray->pos[0]
					- objray->dir[2] * objray->pos[2]) - objray->dir[1];
	quadpoly[2] = objray->pos[0] * objray->pos[0]
					- objray->pos[2] * objray->pos[2] - objray->pos[1];
	if (!(get_realroots_quadpoly(&root1, &root2, quadpoly)))
		return (FALSE);
	if (root1 <= 0. && root2 <= 0.)
		return (FALSE);
	if (root1 <= 0.)
		root1 = root2;
	else if (root2 <= 0.)
		root2 = root1;
	if (root1 > objray->t && root2 > objray->t)
		return (FALSE);
	objray->t = ft_fmin(root1, root2);
	return (TRUE);
}
*/

/*
** To find the normal of a parabola, consider the fact that a parabola is a
** manifold and can thus be described as though its calculus form.
**
** Our scalar function for our hypersurface is f(x, y, z) = x^2 - y - z^2
** Its jacobian matrix is thus the 1×3 matrix [ 2x, -1, -2z ]

void						get_hnn_saddle(t_vec_3d hitpos,
								t_vec_3d normal, t_ray const objray)
{
	get_ray_hitpos(hitpos, objray);
	vec3_set(normal, 2. * hitpos[0], -1., -2. * hitpos[2]);
	if (objray.pos[0] * objray.pos[0] - objray.pos[2] * objray.pos[2]
				<= objray.pos[1])
		vec3_scale(normal, -1., normal);
	vec3_eucl_nrmlz(normal, normal);
}
*/
#endif
