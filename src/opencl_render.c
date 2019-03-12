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

static int			render_launch_kernel1_rendermain(void)
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
	if (opencl_enqueue_piecewise_3d_kernel(rt.ocl.kernels[1]))
		return (opencl_handle_error(error, "render_launch_kernel1_rendermain:"
						" chained enqueue kernel failed for "RT_CL_KERNEL_1));
	return (OK);
}

static int			render_launch_kernel2_averagerays(void)
{
	int			error;
	int			kernel_arg_nbr;
	cl_uint3	tensor_dims;

	tensor_dims = (cl_uint3){{rt.scene.work_dims.x,
								rt.scene.work_dims.y,
								rt.scene.work_dims.z}};



	cl_mem tensor_dims_arg = clCreateBuffer(rt.ocl.context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_uint3), &tensor_dims, &error);
	if (error < 0)
		return (opencl_handle_error(error, "render_launch_kernel2_averagerays:"
		" create read/write buffer failed for scene for "RT_CL_KERNEL_2));

	kernel_arg_nbr = -1;
	if (((error = clSetKernelArg(rt.ocl.kernels[2], ++kernel_arg_nbr,
					sizeof(cl_mem), &(rt.ocl.gpu_buf.canvas_pixels))) < 0) ||
		((error = clSetKernelArg(rt.ocl.kernels[2], ++kernel_arg_nbr,
					sizeof(cl_mem), &(rt.ocl.gpu_buf.ray_lum_tensor))) < 0) ||
		((error = clSetKernelArg(rt.ocl.kernels[2], ++kernel_arg_nbr,
									sizeof(cl_mem), &tensor_dims_arg)) < 0))
	{
		debug_output_value("error: kernel #",
							ft_s32_to_str(kernel_arg_nbr), TRUE);
		return (opencl_handle_error(error, "render_launch_kernel2_averagerays:"
							" set kernel arg failed for "RT_CL_KERNEL_2));
	}
	if (opencl_enqueue_piecewise_2d_kernel(rt.ocl.kernels[2]))
		return (debug_perror("render_launch_kernel2_averagerays:"
						" chained enqueue kernel failed for "RT_CL_KERNEL_2));

	if (tensor_dims_arg &&
		(error = clReleaseMemObject(tensor_dims_arg)))
		return (opencl_handle_error(error, "render_launch_kernel2_averagerays:"
		" release of tensor_dims_arg buffer failed."));

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

int					render(void)
{
	int		error;
	t_bool	is_finished;

	if (render_launch_kernel0_build_scene())
		return (ERROR);
	if ((error = clFinish(rt.ocl.cmd_queue)) < 0)
		return (opencl_handle_error(error, "render:"
							" clFinish failed for "RT_CL_KERNEL_0));
	is_finished = FALSE;
	while (!is_finished)
	{

		if (render_launch_kernel1_rendermain())
			return (ERROR);
		if ((error = clFinish(rt.ocl.cmd_queue)) < 0)
			return (opencl_handle_error(error, "render:"
								" clFinish failed for "RT_CL_KERNEL_1));
		if (render_launch_kernel2_averagerays())
			return (ERROR);
		if ((error = clFinish(rt.ocl.cmd_queue)) < 0)
			return (opencl_handle_error(error, "render:"
								" clFinish failed for "RT_CL_KERNEL_2));
		if (render_read_gpu_buffer())
			return (ERROR);
		is_finished = TRUE;
	}
	return (OK);
}
