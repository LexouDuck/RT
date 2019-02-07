#if 0
__kernel void render_kernel(__global float3* output, int width, int height)
{
 const int work_item_id = get_global_id(0); /* the unique global id of the work item for the current pixel */
 int x = work_item_id % width; /* x-coordinate of the pixel */
 int y = work_item_id / width; /* y-coordinate of the pixel */
 float fx = (float)x / (float)width; /* convert int to float in range [0-1] */
 float fy = (float)y / (float)height; /* convert int to float in range [0-1] */
 output[work_item_id] = (float3)(fx, fy, 0); /* simple interpolated colour gradient based on pixel coordinates */
}
#endif

//#include "rt_cl_render.cl.h"

__kernel void rt_cl_render(
				__global		uint *		result_imgbuf)//,
	//			__constant		t_scene		scene)
{
	const int			x_id = get_global_id(0); /* x-coordinate of the current pixel */
	const int			y_id = get_global_id(1); /* y-coordinate of the current pixel */
//	const int			sample_id = get_global_id(2); /* id of the current ray thread amongst the MC simulation for the current pixel*/
	const int			work_item_id = y_id * get_work_dim(0) + x_id;

	float fx = (float)x / (float)get_work_dim(0); /* convert int to float in range [0-1] */
	float fy = (float)y / (float)get_worl_dim(1); /* convert int to float in range [0-1] */
	uint3 color3 = (uint3)(255 * fx, 255 * fy, 0); 
	result_imgbuf[work_item_id] = (color3.x << 16) & (color3.y << 8) & (color3.z); /* simple interpolated colour gradient based on pixel coordinates */
}