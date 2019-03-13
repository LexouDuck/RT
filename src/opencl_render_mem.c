/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_render_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 14:01:52 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft_memory.h"
#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"
//#include "rt_scene.h"

static inline t_u32	ft_min(t_u32 a, t_u32 b)
{
	return (a < b ? a : b);
}

int					render_init_work_step_and_ray_tensor_buf(void)
{
	static t_work_array		*wksteps = &rt.scene.work_steps;
	int						error;

	*wksteps = *((t_work_array *)rt.ocl.gpu.max_witems_per_dim);
	wksteps->x = ft_min(ft_min(32, wksteps->x), rt.scene.work_dims.x);
	wksteps->y = ft_min(ft_min(32, wksteps->y), rt.scene.work_dims.y);
	wksteps->z = ft_min(ft_min(128, wksteps->z), rt.scene.work_dims.z);
	rt.ocl.gpu_buf.ray_lum_tensor = clCreateBuffer(rt.ocl.context,
		CL_MEM_READ_WRITE, sizeof(cl_float3) * wksteps->x * wksteps->y *
		rt.scene.work_dims.z, NULL, &error);
	if (error < 0)
		return (opencl_handle_error(error,
		"render_init_work_step_and_ray_tensor_buf:"
		" create read/write buffer failed for ray tensor for "RT_CL_KERNEL_1));
	return (OK);
}

int					render_init_tensor_dims_buf(void)
{
	cl_uint4				tensor_dims;
	int						error;

	tensor_dims = (cl_uint4){{rt.scene.work_steps.x, rt.scene.work_steps.y,
							rt.scene.work_dims.z, rt.scene.work_dims.x}};
	rt.ocl.gpu_buf.tensor_dims = clCreateBuffer(rt.ocl.context, CL_MEM_READ_ONLY
		| CL_MEM_COPY_HOST_PTR, sizeof(cl_uint4), &tensor_dims, &error);
	if (error < 0)
		return (opencl_handle_error(error, "render_init_tensor_dims_buf:"
			" create read/write buffer failed for scene for "RT_CL_KERNEL_2));
	if ((error = clEnqueueWriteBuffer(rt.ocl.cmd_queue,
				rt.ocl.gpu_buf.tensor_dims, CL_TRUE, 0,
				sizeof(cl_uint3), &(tensor_dims), 0, NULL, NULL)) < 0)
		return (opencl_handle_error(error, "render_init_tensor_dims_buf:"
							" write to gpu failed for "RT_CL_KERNEL_2));
	return (OK);
}

int					render_read_and_release_gpu_buffers(void)
{
	int		error;

	error = clEnqueueReadBuffer(rt.ocl.cmd_queue, rt.ocl.gpu_buf.canvas_pixels,
		CL_TRUE, 0, sizeof(t_u32) * rt.canvas_pixel_amount,
		rt.canvas->pixels, 0, NULL, NULL);
	if (error < 0)
		return (opencl_handle_error(error, "render_read_gpu_buffer:"
			" couldn't read the buffer for "RT_CL_KERNEL_1));
	if (rt.ocl.gpu_buf.ray_lum_tensor &&
		(error = clReleaseMemObject(rt.ocl.gpu_buf.ray_lum_tensor)))
		return (opencl_handle_error(error, "render_release_gpu_mem:"
		" release of ray tensor buffer failed."));
	rt.ocl.gpu_buf.ray_lum_tensor = NULL;
	if (rt.ocl.gpu_buf.tensor_dims &&
		(error = clReleaseMemObject(rt.ocl.gpu_buf.tensor_dims)))
		return (opencl_handle_error(error, "render_release_gpu_mem:"
		" release of tensor_dims_arg buffer failed."));
	rt.ocl.gpu_buf.tensor_dims = NULL;
	return (OK);
}
