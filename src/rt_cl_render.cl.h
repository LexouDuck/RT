
typedef struct	s_point
{
	cl_int		x;
	cl_int		y;
}				t_point;

typedef struct	s_cl_image_buf
{
	cl_mem			buf;
	cl_int			height;
	cl_int			width;
	cl_int			size;
}				t_cl_image_buf;



/*
** PRIMITIVES
**
** All primitives are considered to be centered near the origin with default
** unit dimensions.
*/
typedef enum	e_objtype
{
	null_obj,			//0
	sphere//,				//1
//	plane,				//2
//	disk,
//	square,
//	triangle,			//5
//	infcylinder,
//	cylinder,
//	infcone,
//	cone,
//	cube,				//10
//	paraboloid,
//	saddle
}				t_objtype;

/*
** Categories for the optical properties of materials for each geometric
** primtive (ie, how they interact with or produce light). Normals play
** a major role here.
*/
typedef enum	e_material
{
	lightsrc,
	diffuse/*,
	mirror,
	glassy,
	glossy*/
	/*,
	skybox ?*/
}				t_material;

/*
** This struct is used to translate, rotate and scale our object into position
**	in the world space.
**
** So that normals be calculated easily, rays are converted into object space
**	first, then compared with the basic primitive. The object_to_world matrix
**	is the succession of: scaling, then rotating, then translating, applied
**  to the basic primitive.
**
** type			: an enum to sort each geometric primitive, see above
** pos			: position in world space
** scl			: (x, y, z) scaling factors as a vector (tmp diagonal matrix)
** rot			: model angles of rotation (in radians) around (resp.)
**					the x-, y-, and z-axes
** rgb			: a vector of float from 0. to 1. representing how much each
**					object reflects each primary color of light,
**					respectively (r, g, b); albedo for a diffuse surface;
**					light emitted for a lightsrc; albedo and filter for
**					glassy, glossy and mirror surfaces.
** unit_w_to_o	: takes a unit vector from world space (that shouldn't be
**					translated) to a non-unit vector in object space
** unit_o_to_w	: takes a non-unit vector from object space (that shouldn't be
**					translated) to corresponding unit vector in world space
** o_to_w		: takes a vector that should be translated from object space
**					to world space
** w_to_o		: takes a vector that should be translated from world space
**					to object space
** n_to_w		: takes a vector that should be considered a normal of our
**					object from object space to world space, in practice,
**					normal_to_world = transpose(inverse(o_to_w))
** intersect	: the intersection function, set when type is set
** get_hnn		: the function that returns the appropriate hitpos and normal
**					of the ray on the object; note that the appropriate t
**					parameter should already be set before this function is
**					called
*/
/*
** Respective intensity for light source's rgb is vec3_scale(intensity, rgb),
**	where rgb contains values between 0. and 1.
*/

typedef struct	s_object
{
	t_objtype		type;
	t_material		material;
	cl_float3		pos;
	cl_float3		scl;
	cl_float3		rot; 
	cl_float3		rgb;
	t_bbox			bbox;
//	cl_float3		specul;
//	t_float			refrac;//refraction index for snell-descartes
//	t_float			intensity;//intensity for lightsrc objects, 1. for other objects //or reflectivity ??
//	t_mat_4b4		o_to_w;
//	t_mat_4b4		w_to_o;
//	t_mat_3b3		linear_o_to_w;
//	t_mat_3b3		linear_w_to_o;
//	t_mat_3b3		n_to_w;
}				t_object;

typedef struct	s_scene
{
	t_camera	cam;
	t_object	objs[MAX_OBJ_NB];
	cl_int		objlst_len;
	cl_int		max_ray_depth;
}				t_scene;