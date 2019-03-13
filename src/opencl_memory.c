/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"

int			opencl_init_gpu_memory(void)
{
	int		error;

	g_rt.ocl.gpu_buf.scene = clCreateBuffer(g_rt.ocl.context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(t_scene), &g_rt.scene, &error);
	if (error < 0)
		return (opencl_handle_error(error, "opencl_init_gpu_memory:"
		" create read/write buffer failed for scene for "RT_CL_KERNEL_0));
	g_rt.ocl.gpu_buf.img_texture = clCreateBuffer(g_rt.ocl.context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_u32) * 100 * 100, g_rt.img_texture, &error);
	if (error < 0)
		return (opencl_handle_error(error, "opencl_init_gpu_memory:"
		" create write buffer failed for texture for "RT_CL_KERNEL_1));
	g_rt.ocl.gpu_buf.canvas_pixels = clCreateBuffer(g_rt.ocl.context,
		CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_u32) * g_rt.scene.work_dims.x * g_rt.scene.work_dims.y,
		g_rt.canvas->pixels, &error);
	if (error < 0)
		return (opencl_handle_error(error, "opencl_init_gpu_memory:"
		" create write buffer failed for canvas for "RT_CL_KERNEL_2));
	return (OK);
}

int			opencl_release_memory_buffers(void)
{
	cl_int	error;

	if (g_rt.ocl.gpu_buf.canvas_pixels &&
		(error = clReleaseMemObject(g_rt.ocl.gpu_buf.canvas_pixels)))
		return (opencl_handle_error(error, "opencl_release_memory_buffers:"
		" release of canvas buffer failed."));
	g_rt.ocl.gpu_buf.canvas_pixels = NULL;
	if (g_rt.ocl.gpu_buf.scene &&
		(error = clReleaseMemObject(g_rt.ocl.gpu_buf.scene)))
		return (opencl_handle_error(error, "opencl_release_memory_buffers:"
		" release of scene buffer failed."));
	g_rt.ocl.gpu_buf.scene = NULL;
	if (g_rt.ocl.gpu_buf.img_texture &&
		(error = clReleaseMemObject(g_rt.ocl.gpu_buf.img_texture)))
		return (opencl_handle_error(error, "opencl_release_memory_buffers:"
		" release of img texture buffer failed."));
	g_rt.ocl.gpu_buf.img_texture = NULL;
	return (OK);
}

int			opencl_refresh_gpu_memory_buffers(void)
{
	if (opencl_release_memory_buffers())
		return (debug_perror("opencl_refresh_gpu_memory_buffers:"
		" memory release failed."));
	if (opencl_init_gpu_memory())
		return (debug_perror("opencl_refresh_gpu_memory_buffers:"
		" memory re-init failed."));
	return (OK);
}

int			opencl_release_queue_context_program(void)
{
	cl_int	error;

	if ((error = clReleaseCommandQueue(g_rt.ocl.cmd_queue)))
		return (opencl_handle_error(error, "opencl_release_queue_context_"
		"program: queue release failed."));
	if ((error = clReleaseContext(g_rt.ocl.context)))
		return (opencl_handle_error(error, "opencl_release_queue_context_"
		"program: context release failed."));
	if ((error = clReleaseProgram(g_rt.ocl.program)))
		return (opencl_handle_error(error, "opencl_release_queue_context_"
		"program: program release failed."));
	return (OK);
}

int			opencl_freeall(void)
{
	cl_int	error;
	int		i;

	if ((error = clFinish(g_rt.ocl.cmd_queue)))
		return (opencl_handle_error(error, "opencl_freeall:"
		" finish failed before release."));
	i = -1;
	while (++i < RT_CL_KERNEL_AMOUNT)
	{
		if ((error = clReleaseKernel(g_rt.ocl.kernels[i])))
		{
			debug_output_value("error: kernel #", ft_s32_to_str(i), TRUE);
			return (opencl_handle_error(error, "opencl_freeall:"
			" kernel release failed."));
		}
	}
	if (opencl_release_memory_buffers())
		return (debug_perror("opencl_freeall: memory release failed."));
	if (opencl_release_queue_context_program())
		return (debug_perror("opencl_freeall: non-memory release failed."));
	return (OK);
}
