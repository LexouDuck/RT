static float3		rt_cl_get_reflect
(
						float3		incdir,
						float3		normal
)
{
	return (incdir - (float3)(2.f * dot(incdir, normal)) * normal);
}

/*
** Formula for transparency transmitted ray T:
**
** T = 	Tn + Tt
**	 = 	[n1/n2 * (I - dot(I, N) * N)]
**		+
**		[N   *   -sqrt(1 - (n1/n2)^2 * (1 - quadnorm(I, N)))]
**
** with n1 the refractive index for the incidence medium, n2 for refrac_ind of
**		the transmission medium, N the hitpos normal, I the hitpos incidence
**		vector.
*/
static float3		rt_cl_get_transmit_or_reflect
(
						uint2 *			random_seeds,
						float3			incdir,
						bool			is_inter_inside,
						float3			normal,
						float			refrac
)
{
	float3		newdir;
	float		dot_i_n;
	float		refrac_ratio;
	float		schlick;
	float		n1 = is_inter_inside ? refrac : 1.;
	float		n2 = is_inter_inside ? 1. : refrac;
	float		schlick_r0;
	float		fresnel;

	schlick_r0 = (n1 - n2) / (n1 + n2);
	schlick_r0 = schlick_r0 * schlick_r0;
	dot_i_n = dot(incdir, normal);
	schlick = schlick_r0 + (1. - schlick_r0) * pown((float)(1. - dot_i_n), 5);
	if (rt_cl_frand_0_to_1(random_seeds) < schlick)
	{
		refrac_ratio = is_inter_inside ? refrac : 1. / refrac;
		fresnel = 1 - refrac_ratio * refrac_ratio * (1 - dot_i_n * dot_i_n);
		if (fresnel < 0.)
//			return ((float3)(0., 0., 0.));
			return (rt_cl_get_reflect(incdir, normal));
		fresnel = -sqrt(fresnel); //this is -cos(theta_transmited), the angle made after transmission)
	//	Tn
		newdir = (float3)refrac_ratio * mad(dot_i_n, normal, incdir);
	//	+ Tt
		newdir = mad(fresnel, normal, newdir);
		newdir = normalize(newdir);
	}
	else
	{
		newdir = rt_cl_get_reflect(incdir, normal);
		//coslobe phong according to roughness?
	}
	return (newdir);
}
