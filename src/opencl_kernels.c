/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 16:46:16 by fulguritu         #+#    #+#             */
/*   Updated: 2019/02/01 21:17:10 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"

int					opencl_init_kernels(void)
{
	int		error;

	rt.ocl.kernels[0] = clCreateKernel(rt.ocl.program, RT_CL_KERNEL_0, &error);
	if (error < 0)
		return (debug_perror("opencl_init:"
							" could not init kernel "RT_CL_KERNEL_0));
	rt.ocl.kernels[1] = clCreateKernel(rt.ocl.program, RT_CL_KERNEL_1, &error);
	if (error < 0)
		return (debug_perror("opencl_init:"
							" could not init kernel "RT_CL_KERNEL_1));
	rt.ocl.kernels[2] = clCreateKernel(rt.ocl.program, RT_CL_KERNEL_2, &error);
	if (error < 0)
		return (debug_perror("opencl_init:"
							" could not init kernel "RT_CL_KERNEL_2));
	return (OK);
}

int					render_launch_kernel0_build_scene(void)
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

int					render_prepare_kernel1_rendermain(void)
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
	return (OK);
}

int					render_prepare_kernel2_averagerays(void)
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
	return (OK);
}



/*
** The formula for calculating global id is:
**		(gx , gy) = (wx * Sx + sx + Fx, wy * Sy + sy + Fy)
**
** w{x,y} = work-group id{0, 1}
** S{x,y} = work-group size{0, 1}
** s{x,y} = local id{0, 1}
** F{x,y} = global ID offset{0, 1}
*/

#if 0
//TODO remove
#include <stdio.h>

int					opencl_enqueue_piecewise_2d_kernel(cl_kernel krnl)
{
	static const int	dim_rank = 2;
	int					err;
	t_work_array		work_dim_end;
	t_work_array		work_offsets;
	t_work_array		work_steps;

	work_steps = *((t_work_array *)rt.ocl.gpu.max_witems_per_dim);
	work_offsets.z = 0;
	work_offsets.y = 0;
	while (work_offsets.y < rt.scene.work_dims.y)
	{
		work_offsets.x = 0;
		while (work_offsets.x < rt.scene.work_dims.x)
		{
			work_dim_end = (t_work_array){
				ft_min(work_steps.x, rt.scene.work_dims.x - work_offsets.x),
				ft_min(work_steps.y, rt.scene.work_dims.y - work_offsets.y), 1};	
printf("offsets: %zu %zu %zu | dim_end %zu %zu %zu\n", work_offsets.x, work_offsets.y, work_offsets.z, work_dim_end.x, work_dim_end.y, work_dim_end.z);
			if ((err = clEnqueueNDRangeKernel(rt.ocl.cmd_queue, krnl, dim_rank,
											(size_t const *)&work_offsets,
											(size_t const *)&work_dim_end,
													NULL, 0, NULL, NULL)) < 0)
				return (opencl_handle_error(err, "render_piecewise_2d_kernel:"
								" enqueue kernel failed."));
			work_offsets.x += work_steps.x;
		}
		work_offsets.y += work_steps.y;
		rt.ocl.render_progress = (float)work_offsets.y / rt.scene.work_dims.y;
	}
	return (OK);
}
#endif

