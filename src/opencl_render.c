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

static int		render_launch_kernel0_build_scene(void)
{
	int		error;

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

/*
** The formula for calculating global id is:
**		(gx , gy) = (wx * Sx + sx + Fx, wy * Sy + sy + Fy)
**
** w{x,y} = work-group id{0, 1}
** S{x,y} = work-group size{0, 1}
** s{x,y} = local id{0, 1}
** F{x,y} = global ID offset{0, 1}
*/

static int			render_piecewise_2d_kernel(cl_kernel krnl)
{
	int		err;
	int		work_dim_rank;
	size_t	work_dim_array[2];
	size_t	work_offsets[2];
	int 	step;

	step = 32;//TODO fix in function of mc_raysamp_size
	work_dim_rank = 2;
	work_dim_array[0] = rt.scene.work_dim[0];
	work_dim_array[1] = step;
	ft_memclr(work_offsets, sizeof(size_t) * 2);
	rt.ocl.render_progress = 0.;
	while (work_offsets[1] < (size_t)rt.scene.work_dim[1])
	{ 
		if ((err = clEnqueueNDRangeKernel(rt.ocl.cmd_queue, krnl, work_dim_rank,
						work_offsets, work_dim_array, NULL, 0, NULL, NULL)) < 0)
			return (opencl_handle_error(err, "render_piecewise_2d_kernel:"
								" enqueue kernel failed for "RT_CL_KERNEL_1));
		work_offsets[1] += step;
		rt.ocl.render_progress = (float)work_offsets[1] / rt.scene.work_dim[1];
	}
	return (OK);
}

static int			render_launch_kernel1_rendermain(void)
{
	int		error;
	int		kernel_arg_nbr;

	kernel_arg_nbr = -1;
	if (((error = clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr,
					sizeof(cl_mem), &(rt.ocl.gpu_buf.canvas_pixels))) < 0) ||
		((error = clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr,
					sizeof(cl_mem), &(rt.ocl.gpu_buf.scene))) < 0))
	{
		debug_output_value("error: kernel #",
							ft_s32_to_str(kernel_arg_nbr), TRUE);
		return (opencl_handle_error(error, "render_launch_kernel1_rendermain:"
							" set kernel arg failed for "RT_CL_KERNEL_1));
	}
	if (render_piecewise_2d_kernel(rt.ocl.kernels[1]))
		return (opencl_handle_error(error, "render_launch_kernel1_rendermain:"
						" chained enqueue kernel failed for "RT_CL_KERNEL_1));
	return (OK);
}

int			render_read_gpu_buffer(void)
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

int			render(void)
{
	int		error;

	rt.scene.random_seed_time = rt.sdl.current_frame;
	if (render_launch_kernel0_build_scene())
		return (ERROR);
	if ((error = clFinish(rt.ocl.cmd_queue)) < 0)
		return (opencl_handle_error(error, "render:"
							" clFinish failed for "RT_CL_KERNEL_0));
	if (render_launch_kernel1_rendermain())
		return (ERROR);
	if ((error = clFinish(rt.ocl.cmd_queue)) < 0)
		return (opencl_handle_error(error, "render:"
							" clFinish failed for "RT_CL_KERNEL_1));
	if (render_read_gpu_buffer())
		return (ERROR);
	return (OK);
}
