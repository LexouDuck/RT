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

#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"

/*
** code to print program as is stored in memory
** char str[40000];
**
** err = clGetProgramInfo(g_rt.ocl.program,
** CL_PROGRAM_SOURCE, 40000, str, NULL);
** 		if (err < 0)
** 		return (debug_perror(" read source failed for "RT_CL_PROGRAM_SOURCE));
** 		printf("%s", str);
*/

/*
** The formula for calculating global id is:
**		(gx , gy) = (wx * Sx + sx + Fx, wy * Sy + sy + Fy)
**
** w{x,y} = work-group id{0, 1}
** S{x,y} = work-group size{0, 1}
** s{x,y} = local id{0, 1}
** F{x,y} = global ID offset{0, 1}
*/

int					render_enqueue_pairwise_kernels_inner(
												t_work_array work_offsets)
{
	int					err;
	t_work_array		work_dim_end;

	work_offsets.z = 0;
	while (work_offsets.z < g_rt.scene.work_dims.z)
	{
		work_dim_end = g_rt.scene.work_steps;
		if ((err = clEnqueueNDRangeKernel(g_rt.ocl.cmd_queue,
				g_rt.ocl.kernels[1], 3, (size_t const *)&work_offsets,
				(size_t const *)&work_dim_end, NULL, 0, NULL, NULL)) < 0)
			return (opencl_handle_error(err, "render_pairwise_kernels:"
			" enqueue kernel failed for "RT_CL_KERNEL_1));
		work_offsets.z += g_rt.scene.work_steps.z;
	}
	if ((err = clFinish(g_rt.ocl.cmd_queue)) < 0)
		return (opencl_handle_error(err, "render_pairwise_kernels:"
		" clFinish failed for "RT_CL_KERNEL_1));
	if ((err = clEnqueueNDRangeKernel(g_rt.ocl.cmd_queue,
			g_rt.ocl.kernels[2], 2, (size_t const *)&work_offsets,
			(size_t const *)&work_dim_end, NULL, 0, NULL, NULL)) < 0)
		return (opencl_handle_error(err, "render_pairwise_kernels:"
		" enqueue kernel failed for "RT_CL_KERNEL_2));
	return (OK);
}

int					render_enqueue_pairwise_kernels(void)
{
	t_work_array		work_offsets;

	work_offsets.y = 0;
	while (work_offsets.y < g_rt.scene.work_dims.y)
	{
		work_offsets.x = 0;
		while (work_offsets.x < g_rt.scene.work_dims.x)
		{
			if (render_enqueue_pairwise_kernels_inner(work_offsets))
				return (debug_perror("render_enqueue_pairwise_kernels:"
				" render failed."));
			work_offsets.x += g_rt.scene.work_steps.x;
		}
		work_offsets.y += g_rt.scene.work_steps.y;
		g_rt.ocl.render_progress =
			(float)work_offsets.y / g_rt.scene.work_dims.y;
		debug_output_value("Progress: ",
					ft_f32_to_str(g_rt.ocl.render_progress * 100.f, 3), TRUE);
	}
	return (OK);
}

int					render(void)
{
	int		error;

	if (render_launch_kernel0_build_scene())
		return (debug_perror("render: failure in launch_kernel0"));
	if ((error = clFinish(g_rt.ocl.cmd_queue)) < 0)
		return (opencl_handle_error(error, "render:"
		" clFinish failed for "RT_CL_KERNEL_0));
	if (render_init_work_step_and_ray_tensor_buf())
		return (debug_perror("render: failure in init_ray_tensor_buf"));
	if (render_init_tensor_dims_buf())
		return (debug_perror("render: failure in init_tensor_dims_buf"));
	if (render_prepare_kernel1_rendermain())
		return (debug_perror("render: failure in args for "RT_CL_KERNEL_1));
	if (render_prepare_kernel2_averagerays())
		return (debug_perror("render: failure in args for "RT_CL_KERNEL_2));
	if (render_enqueue_pairwise_kernels())
		return (debug_perror("render: failure in core render kernel queue."));
	if ((error = clFinish(g_rt.ocl.cmd_queue)) < 0)
		return (opencl_handle_error(error, "render:"
		" clFinish failed for render kernel queue."));
	if (render_read_and_release_gpu_buffers())
		return (debug_perror("render: failure to read or release gpu buffers"));
	return (OK);
}
