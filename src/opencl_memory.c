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

	error = CL_SUCCESS;
	rt.ocl.gpu_buf.scene = clCreateBuffer(rt.ocl.context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(t_scene), &rt.scene, &error);
	if (error < 0)
		return (opencl_handle_error(error, "opencl_init_gpu_memory:"
					" create read/write buffer failed for "RT_CL_KERNEL_0));
	rt.ocl.gpu_buf.canvas_pixels = clCreateBuffer(rt.ocl.context,
		CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_u32) * rt.scene.work_dim[0] * rt.scene.work_dim[1],
		rt.canvas->pixels, &error);
	if (error < 0)
		return (opencl_handle_error(error, "opencl_init_gpu_memory:"
					" create write buffer failed for "RT_CL_KERNEL_1));
	//TODO Check with Tristan
	rt.ocl.gpu_buf.img_texture = clCreateBuffer(rt.ocl.context,
		CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_u32) * 100 * 100, rt.img_texture, &error);
	if (error < 0)
		return (opencl_handle_error(error, "opencl_init_gpu_memory:"
					" create write buffer failed for "RT_CL_KERNEL_1));
	return (OK);
}

int			opencl_release_memory_buffers(void)
{
	cl_int	error;

	if (rt.ocl.gpu_buf.canvas_pixels &&
		(error = clReleaseMemObject(rt.ocl.gpu_buf.canvas_pixels)))
		return (opencl_handle_error(error, "opencl_release_memory_buffers:"
										" release of canvas buffer failed."));
	rt.ocl.gpu_buf.canvas_pixels = NULL;
	if (rt.ocl.gpu_buf.scene &&
		(error = clReleaseMemObject(rt.ocl.gpu_buf.scene)))
		return (opencl_handle_error(error, "opencl_release_memory_buffers:"
										" release of scene buffer failed."));
	rt.ocl.gpu_buf.scene = NULL;
	//TODO Check with Tristan
	if (rt.ocl.gpu_buf.img_texture &&
		(error = clReleaseMemObject(rt.ocl.gpu_buf.img_texture)))
		return (opencl_handle_error(error, "opencl_release_memory_buffers:"
										" release of img texture buffer failed."));
	rt.ocl.gpu_buf.img_texture = NULL;
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

	if ((error = clReleaseCommandQueue(rt.ocl.cmd_queue)))
		return (opencl_handle_error(error,
			"opencl_release_queue_context_program: queue release failed."));
	if ((error = clReleaseContext(rt.ocl.context)))
		return (opencl_handle_error(error,
			"opencl_release_queue_context_program: context release failed."));
	if ((error = clReleaseProgram(rt.ocl.program)))
		return (opencl_handle_error(error,
			"opencl_release_queue_context_program: program release failed."));
	return (OK);
}

int			opencl_freeall(void)
{
	cl_int	error;
	int		i;

	if ((error = clFinish(rt.ocl.cmd_queue)))
		return (opencl_handle_error(error,
				"opencl_freeall: finish failed before release."));
	i = -1;
	while (++i < RT_CL_KERNEL_AMOUNT)
	{
		if ((error = clReleaseKernel(rt.ocl.kernels[i])))
		{
			debug_output_value("error: kernel #", ft_s32_to_str(i), TRUE);
			return (opencl_handle_error(error,
					"opencl_freeall: kernel release failed."));
		}
	}
	if (opencl_release_memory_buffers())
		return (debug_perror("opencl_freeall: memory release failed."));
	if (opencl_release_queue_context_program())
		return (debug_perror("opencl_freeall: non-memory release failed."));
	return (OK);
}
