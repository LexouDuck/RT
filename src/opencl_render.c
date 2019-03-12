/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 14:01:52 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"
#include "rt_scene.h"

/*
** code to print program as is stored in memory
** char str[40000];
**
** err = clGetProgramInfo(rt.ocl.program, CL_PROGRAM_SOURCE, 40000, str, NULL);
** 		if (err < 0)
** 		return (debug_perror(" read source failed for "RT_CL_PROGRAM_SOURCE));
** 		printf("%s", str);
*/

static int			render_launch_kernel0_build_scene(void)
{
	int		error;

	rt.scene.random_seed_time = rt.sdl.current_frame;
	if ((error = clEnqueueWriteBuffer(rt.ocl.cmd_queue, rt.ocl.gpu_buf.scene,
			CL_TRUE, 0, sizeof(t_scene), &(rt.scene), 0, NULL, NULL)) < 0)
		return (opencl_handle_error(error, "render_launch_kernel0_build_scene:"
							" write to gpu failed for "RT_CL_KERNEL_0));
	if ((error = clSetKernelArg(rt.ocl.kernels[0], 0, sizeof(cl_mem),
							&(rt.ocl.gpu_buf.scene))) < 0)
		return (opencl_handle_error(error, "render_launch_kernel0_build_scene:"
							" set kernel arg failed for "RT_CL_KERNEL_0));
	if ((error = clEnqueueNDRangeKernel(rt.ocl.cmd_queue, rt.ocl.kernels[0], 1,
				NULL, &(rt.scene.object_amount), NULL, 0, NULL, NULL)) < 0)
		return (opencl_handle_error(error, "render_launch_kernel0_build_scene:"
							" enqueue kernel failed for "RT_CL_KERNEL_0));
	return (OK);
}

static int			render_prepare_kernel1_rendermain(void)
{
	int		error;
	int		kernel_arg_nbr;

	kernel_arg_nbr = -1;
	if (((error = clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr,
					sizeof(cl_mem), &(rt.ocl.gpu_buf.ray_lum_tensor))) < 0) ||
		((error = clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr,
							sizeof(cl_mem), &(rt.ocl.gpu_buf.scene))) < 0) ||
		((error = clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr,
						sizeof(cl_mem), &(rt.ocl.gpu_buf.img_texture))) < 0))
	{
		debug_output_value("error: kernel #",
							ft_s32_to_str(kernel_arg_nbr), TRUE);
		return (opencl_handle_error(error, "render_launch_kernel1_rendermain:"
							" set kernel arg failed for "RT_CL_KERNEL_1));
	}
//	if (opencl_enqueue_piecewise_3d_kernel(rt.ocl.kernels[1]))
//		return (opencl_handle_error(error, "render_launch_kernel1_rendermain:"
//						" chained enqueue kernel failed for "RT_CL_KERNEL_1));
	return (OK);
}

static int			render_prepare_kernel2_averagerays(void)
{
	int				error;
	int				kernel_arg_nbr;

	kernel_arg_nbr = -1;
	if (((error = clSetKernelArg(rt.ocl.kernels[2], ++kernel_arg_nbr,
					sizeof(cl_mem), &(rt.ocl.gpu_buf.canvas_pixels))) < 0) ||
		((error = clSetKernelArg(rt.ocl.kernels[2], ++kernel_arg_nbr,
					sizeof(cl_mem), &(rt.ocl.gpu_buf.ray_lum_tensor))) < 0) ||
		((error = clSetKernelArg(rt.ocl.kernels[2], ++kernel_arg_nbr,
					sizeof(cl_mem), &(rt.ocl.gpu_buf.tensor_dims))) < 0))
	{
		debug_output_value("error: kernel #",
							ft_s32_to_str(kernel_arg_nbr), TRUE);
		return (opencl_handle_error(error, "render_launch_kernel2_averagerays:"
							" set kernel arg failed for "RT_CL_KERNEL_2));
	}
//	if (opencl_enqueue_piecewise_2d_kernel(rt.ocl.kernels[2]))
//		return (debug_perror("render_launch_kernel2_averagerays:"
//						" chained enqueue kernel failed for "RT_CL_KERNEL_2));


	return (OK);
}

static int			render_read_gpu_buffer(void)
{
	int		error;

	error = clEnqueueReadBuffer(rt.ocl.cmd_queue, rt.ocl.gpu_buf.canvas_pixels,
		CL_TRUE, 0, sizeof(t_u32) * rt.canvas_pixel_amount,
		rt.canvas->pixels, 0, NULL, NULL);
	if (error < 0)
		return (opencl_handle_error(error, "render_read_gpu_buffer:"
			" couldn't read the buffer for "RT_CL_KERNEL_1));
	return (OK);
}

//TODO move to better pastures
inline t_u32		ft_min(t_u32 a, t_u32 b)
{
	return (a < b ? a : b);
}

//TODO remove
#include <stdio.h>

int					opencl_enqueue_pairwise_kernels(void)
{
//	static const int	dim_rank = 3;
	int					err;
	t_work_array		work_dim_end;
	t_work_array		work_offsets;


	work_offsets.y = 0;
	while (work_offsets.y < rt.scene.work_dims.y)
	{
		work_offsets.x = 0;
		while (work_offsets.x < rt.scene.work_dims.x)
		{


			work_offsets.z = 0;
			while (work_offsets.z < rt.scene.work_dims.z)
			{
				work_dim_end = (t_work_array){
					ft_min(rt.scene.work_steps.x, rt.scene.work_dims.x - work_offsets.x),
					ft_min(rt.scene.work_steps.y, rt.scene.work_dims.y - work_offsets.y),
					ft_min(rt.scene.work_steps.z, rt.scene.work_dims.z - work_offsets.z)};
				if ((err = clEnqueueNDRangeKernel(rt.ocl.cmd_queue,
							rt.ocl.kernels[1], 3, (size_t const *)&work_offsets,
							(size_t const *)&work_dim_end, NULL, 0, NULL, NULL)) < 0)
					return (opencl_handle_error(err, "render_pairwise_kernels:"
										" enqueue kernel failed for "RT_CL_KERNEL_1));
				work_offsets.z += rt.scene.work_steps.z;
			}

/*			if ((err = clFinish(rt.ocl.cmd_queue)) < 0)
				return (opencl_handle_error(err, "render_pairwise_kernels:"
									" clFinish failed for "RT_CL_KERNEL_1));
*/			if ((err = clEnqueueNDRangeKernel(rt.ocl.cmd_queue,
						rt.ocl.kernels[2], 2, (size_t const *)&work_offsets,
						(size_t const *)&work_dim_end, NULL, 0, NULL, NULL)) < 0)
				return (opencl_handle_error(err, "render_pairwise_kernels:"
										" enqueue kernel failed for "RT_CL_KERNEL_2));

			work_offsets.x += rt.scene.work_steps.x;
		}
		work_offsets.y += rt.scene.work_steps.y;
		rt.ocl.render_progress = (float)work_offsets.y / rt.scene.work_dims.y;
//printf("%f / 100.0%%\n", rt.ocl.render_progress * 100.f);
	}



	return (OK);
}


int					render(void)
{
	int		error;

/*	if (rt.scene.render_mode == RENDERMODE_MCPT)
	{
*/		rt.scene.work_steps = *((t_work_array *)rt.ocl.gpu.max_witems_per_dim);
		rt.scene.work_steps.x = ft_min(ft_min(32,
								rt.scene.work_steps.x), rt.scene.work_dims.x);
		rt.scene.work_steps.y = ft_min(ft_min(32,
								rt.scene.work_steps.y), rt.scene.work_dims.y);
		rt.scene.work_steps.z = ft_min(ft_min(128,
								rt.scene.work_steps.z), rt.scene.work_dims.z);
/*	}
	else
	{
		rt.scene.work_steps = rt.scene.work_dims;//should be canvas.w, canvas.h, 1
	}
*/
	if (render_launch_kernel0_build_scene())
		return (ERROR);
	if ((error = clFinish(rt.ocl.cmd_queue)) < 0)
		return (opencl_handle_error(error, "render:"
							" clFinish failed for "RT_CL_KERNEL_0));



	rt.ocl.gpu_buf.ray_lum_tensor = clCreateBuffer(rt.ocl.context,
		CL_MEM_READ_WRITE, sizeof(cl_float3) * rt.scene.work_steps.x *
		rt.scene.work_steps.y * rt.scene.work_dims.z, NULL, &error);
	if (error < 0)
		return (opencl_handle_error(error, "render:"
		" create read/write buffer failed for ray tensor for "RT_CL_KERNEL_1));




	if (render_prepare_kernel1_rendermain())
		return (ERROR);




	cl_uint4	tensor_dims;
	tensor_dims = (cl_uint4){{rt.scene.work_steps.x,
							rt.scene.work_steps.y,
							(rt.scene.render_mode == RENDERMODE_MCPT ? rt.scene.work_dims.z : 1),
							rt.scene.work_dims.x}};
	rt.ocl.gpu_buf.tensor_dims = clCreateBuffer(rt.ocl.context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_uint4), &tensor_dims, &error);
	if (error < 0)
		return (opencl_handle_error(error, "render_launch_kernel2_averagerays:"
			" create read/write buffer failed for scene for "RT_CL_KERNEL_2));
	if ((error = clEnqueueWriteBuffer(rt.ocl.cmd_queue,
				rt.ocl.gpu_buf.tensor_dims, CL_TRUE, 0,
				sizeof(cl_uint3), &(tensor_dims), 0, NULL, NULL)) < 0)
		return (opencl_handle_error(error, "render_launch_kernel2_averagerays:"
							" write to gpu failed for "RT_CL_KERNEL_2));




	if (render_prepare_kernel2_averagerays())
		return (ERROR);




	if (opencl_enqueue_pairwise_kernels())
		return (ERROR);
	if ((error = clFinish(rt.ocl.cmd_queue)) < 0)
		return (opencl_handle_error(error, "render:"
							" clFinish failed for render loop."));


	if (render_read_gpu_buffer())
		return (ERROR);




	if (rt.ocl.gpu_buf.ray_lum_tensor &&
		(error = clReleaseMemObject(rt.ocl.gpu_buf.ray_lum_tensor)))
		return (opencl_handle_error(error, "opencl_release_memory_buffers:"
		" release of ray tensor buffer failed."));
	rt.ocl.gpu_buf.ray_lum_tensor = NULL;

	if (rt.ocl.gpu_buf.tensor_dims &&
		(error = clReleaseMemObject(rt.ocl.gpu_buf.tensor_dims)))
		return (opencl_handle_error(error, "render_launch_kernel2_averagerays:"
		" release of tensor_dims_arg buffer failed."));
	rt.ocl.gpu_buf.tensor_dims = NULL;
	return (OK);
}
