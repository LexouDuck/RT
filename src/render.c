/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 14:01:52 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft_memory.h"
#include "../rt.h"
#include "debug.h"
#include "rt_scene.h"

/*
** code to print program as is stored in memory
** char str[40000];
**
** err = clGetProgramInfo(rt.ocl.program, CL_PROGRAM_SOURCE, 40000, str, NULL);
** 		if (err < 0)
** 		return (debug_perror("Couldn't create read source "RT_CL_PROGRAM_SOURCE));
** 		printf("%s", str);
*/

static int		render_launch_kernel0_build_scene(void)
{
	int err;

	err = CL_SUCCESS;
	err = clEnqueueWriteBuffer(rt.ocl.cmd_queue, rt.ocl.gpu_buf.scene, CL_TRUE,
			0, sizeof(t_scene), &(rt.scene), 0, NULL, NULL);
	if (err < 0)
		return (debug_perror("Couldn't enqueue write to gpu for "RT_CL_KERNEL_0));
	err = clSetKernelArg(rt.ocl.kernels[0], 0, sizeof(cl_mem), &(rt.ocl.gpu_buf.scene));
	if (err < 0)
		return (debug_perror("Couldn't create a kernel argument for "RT_CL_KERNEL_0));
	err = clEnqueueNDRangeKernel(rt.ocl.cmd_queue, rt.ocl.kernels[0], 1, NULL,
				&(rt.scene.object_amount), NULL, 0, NULL, NULL);
	if (err < 0)
	{
		debug_perror(opencl_get_error_string(err));
		return (debug_perror("Couldn't enqueue the kernel for "RT_CL_KERNEL_0));
	}
	if ((err = clFinish(rt.ocl.cmd_queue)) < 0)
		return (debug_perror("Couldn't finish "RT_CL_KERNEL_0));
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
	int		work_dim_amount;
	size_t	work_dim_array[2];
	size_t	work_offsets_array[2];
//	size_t	work_buffer_end[2];

	work_dim_amount = 2;
	work_dim_array[0] = rt.scene.work_dim[0];
	work_dim_array[1] = 1;//(size_t)rt.canvas_h;
	work_offsets_array[0] = 0;
	work_offsets_array[1] = 0;
	rt.ocl.render_progress = 0.;
	while (work_offsets_array[1] < (size_t)rt.scene.work_dim[1])
	{ 
		if ((err = clEnqueueNDRangeKernel(rt.ocl.cmd_queue, krnl,
			work_dim_amount, work_offsets_array, work_dim_array, NULL, 0, NULL, NULL)) < 0)
		{
			debug_perror(opencl_get_error_string(err));
			return (debug_perror("Couldn't enqueue a kernel for "RT_CL_KERNEL_1));
		}
		++work_offsets_array[1];
		rt.ocl.render_progress = ((float)work_offsets_array[1]) / rt.scene.work_dim[1];
	}
	return (OK);
}

static int			render_launch_kernel1_rendermain(void)
{
	int		err;
	int		kernel_arg_nbr;

	err = 0;
	kernel_arg_nbr = -1;
	err = clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr, sizeof(cl_mem),
							&(rt.ocl.gpu_buf.canvas_pixels));
	err |= clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr, sizeof(cl_mem),
							&(rt.ocl.gpu_buf.scene));
//	err |= clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr, sizeof(cl_uint), NULL); TODO: check if adding this fixes work group seed problem
	if (err < 0)
	{
//		debug_perror(get_error_string(err));
		return (debug_perror("Couldn't create a kernel argument for "RT_CL_KERNEL_1));
	}
	render_piecewise_2d_kernel(rt.ocl.kernels[1]);
	if ((err = clFinish(rt.ocl.cmd_queue)) < 0)
	{
		debug_perror(opencl_get_error_string(err));
		return (debug_perror("Couldn't finish "RT_CL_KERNEL_1));
	}
	return (OK);
}

int			render_read_gpu_buffer(void)
{
	int err;

	err = 0;
	err = clEnqueueReadBuffer(rt.ocl.cmd_queue, rt.ocl.gpu_buf.canvas_pixels,
		CL_TRUE, 0, sizeof(t_u32) * rt.canvas_pixel_amount,
		rt.canvas->pixels, 0, NULL, NULL);
	if (err < 0)
	{
		debug_perror(opencl_get_error_string(err));
		return (debug_perror("render_read_gpu_buffer:"
			" couldn't read the buffer for "RT_CL_KERNEL_1));
	}
	return (OK);
}

int			render(void)
{
//	int		err;
//	rt.scene.render_mode = RENDERMODE_MCPT;
//	rt.scene.camera.model = CAMERA_MODEL_TMP;
//	rt.scene.camera.model = CAMERA_MODEL_FOCAL;
//	rt.scene.camera.model = CAMERA_MODEL_PINHOLE;
//	rt.scene.camera.model = CAMERA_MODEL_ORTHOGRAPHIC;
//rt.scene.render_mode = RENDERMODE_SOLIDCOLOR;
//rt.scene.objects[0].material = !lightsource;
//float intensity = 1. / 255.;
//rt.scene.objects[0].rgb = (cl_float3){255., 255., 255.};//((BG_COLOR & 0xFF0000) >> 16) * intensity, ((BG_COLOR & 0xFF00) >> 8) * intensity, (BG_COLOR & 0xFF) * intensity};
	rt.scene.random_seed_time = rt.sdl.current_frame;
	if (render_launch_kernel0_build_scene())
		return (ERROR);
	if (render_launch_kernel1_rendermain())
		return (ERROR);
	if (render_read_gpu_buffer())
		return (ERROR);
	return (OK);
}
