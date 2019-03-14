/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernels.c                                   :+:      :+:    :+:   */
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

	g_rt.ocl.kernels[0] =
	clCreateKernel(g_rt.ocl.program, RT_CL_KERNEL_0, &error);
	if (error < 0)
		return (debug_perror("opencl_init:"
		" could not init kernel "RT_CL_KERNEL_0));
	g_rt.ocl.kernels[1] =
	clCreateKernel(g_rt.ocl.program, RT_CL_KERNEL_1, &error);
	if (error < 0)
		return (debug_perror("opencl_init:"
		" could not init kernel "RT_CL_KERNEL_1));
	g_rt.ocl.kernels[2] =
	clCreateKernel(g_rt.ocl.program, RT_CL_KERNEL_2, &error);
	if (error < 0)
		return (debug_perror("opencl_init:"
		" could not init kernel "RT_CL_KERNEL_2));
	return (OK);
}

int					render_launch_kernel0_build_scene(void)
{
	int		error;

	g_rt.scene.random_seed_time = g_rt.sdl.current_frame;
	if ((error =
		clEnqueueWriteBuffer(g_rt.ocl.cmd_queue, g_rt.ocl.gpu_buf.scene,
		CL_TRUE, 0, sizeof(t_scene), &(g_rt.scene), 0, NULL, NULL)) < 0)
		return (opencl_handle_error(error, "render_launch_kernel0_build_scene:"
		" write to gpu failed for "RT_CL_KERNEL_0));
	if ((error = clSetKernelArg(g_rt.ocl.kernels[0], 0, sizeof(cl_mem),
			&(g_rt.ocl.gpu_buf.scene))) < 0)
		return (opencl_handle_error(error, "render_launch_kernel0_build_scene:"
		" set kernel arg failed for "RT_CL_KERNEL_0));
	if ((error =
		clEnqueueNDRangeKernel(g_rt.ocl.cmd_queue, g_rt.ocl.kernels[0], 1,
		NULL, &(g_rt.scene.object_amount), NULL, 0, NULL, NULL)) < 0)
		return (opencl_handle_error(error, "render_launch_kernel0_build_scene:"
		" enqueue kernel failed for "RT_CL_KERNEL_0));
	return (OK);
}

int					render_prepare_kernel1_rendermain(void)
{
	int		error;
	int		kernel_arg_nbr;

	kernel_arg_nbr = -1;
	if (((error = clSetKernelArg(g_rt.ocl.kernels[1], ++kernel_arg_nbr,
			sizeof(cl_mem), &(g_rt.ocl.gpu_buf.ray_lum_tensor))) < 0) ||
		((error = clSetKernelArg(g_rt.ocl.kernels[1], ++kernel_arg_nbr,
			sizeof(cl_mem), &(g_rt.ocl.gpu_buf.scene))) < 0) ||
		((error = clSetKernelArg(g_rt.ocl.kernels[1], ++kernel_arg_nbr,
			sizeof(cl_mem), &(g_rt.ocl.gpu_buf.img_texture))) < 0))
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
	if (((error = clSetKernelArg(g_rt.ocl.kernels[2], ++kernel_arg_nbr,
			sizeof(cl_mem), &(g_rt.ocl.gpu_buf.canvas_pixels))) < 0) ||
		((error = clSetKernelArg(g_rt.ocl.kernels[2], ++kernel_arg_nbr,
			sizeof(cl_mem), &(g_rt.ocl.gpu_buf.ray_lum_tensor))) < 0) ||
		((error = clSetKernelArg(g_rt.ocl.kernels[2], ++kernel_arg_nbr,
			sizeof(cl_mem), &(g_rt.ocl.gpu_buf.tensor_dims))) < 0))
	{
		debug_output_value("error: kernel #",
			ft_s32_to_str(kernel_arg_nbr), TRUE);
		return (opencl_handle_error(error, "render_launch_kernel2_averagerays:"
		" set kernel arg failed for "RT_CL_KERNEL_2));
	}
	return (OK);
}
