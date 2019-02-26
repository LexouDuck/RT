static float3		rt_cl_get_reflect
(
						float3		incdir,
						float3		normal
)
{
	return (incdir - (float3)(2.f * dot(incdir, normal)) * normal);
}

static float3		rt_cl_get_transmit
(
						t_ray		incident,
						float3		normal
)
{
	float		dot_i_n;
	bool		incid_inside_obj;
	float		refrac_ratio;
	float		fresnel;

	dot_i_n = dot(incident.dir, normal);
	incid_inside_obj = (ray.inter_type == INTER_INSIDE);
	refrac_ratio = incid_inside_obj ? shdr->hit_obj->refrac : 1. / shdr->hit_obj->refrac;
	fresnel = 1 - refrac_ratio * refrac_ratio * (1 - dot_i_n * dot_i_n);
	if (fresnel < 0.)
		return (FALSE);
	fresnel = -sqrt(fresnel);
//	Tn
	newdir = (float3)refrac_ratio * mad(dot_i_n, normal, incident.dir);
//	+ Tt
	newdir = mad(fresnel, normal, newdir);
//	Position correction for transmission
	newpos = mad(-EPS, normal, newpos);
	return (TRUE);
}