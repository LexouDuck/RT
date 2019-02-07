/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "debug.h"

#include "libft_memory.h"

int		render_init()
{
	int err = 0;
//assign group size and work dim etc //fat data buffers
//kernels //setting args is done later ? //clCreateKernelsInProgram

	rt.ocl.kernels[0] = clCreateKernel(rt.ocl.program, RT_CL_KERNEL_0, &err);
	if (err < 0)
		return (debug_perror("Couldn't create a kernel for "RT_CL_KERNEL_0));

//TODO CREATESCENE

//	rt.ocl.scene_hostbuf = clCreateBuffer(context, CL_MEM_READ_ONLY |
//			CL_MEM_COPY_HOST_PTR, sizeof(t_scene), &scene, &err); //TODO Once pointer based BVH are implemented, edit here so that scene is the right format, or add args to kernel

	size_t	work_dim[2] = {rt.sdl.window_w, rt.sdl.window_h};
	rt.ocl.result_gpu_buf = clCreateBuffer(rt.ocl.context, CL_MEM_READ_WRITE |
			CL_MEM_COPY_HOST_PTR, sizeof(uint) * rt.sdl.pixel_amount, rt.canvas->pixels, &err);
	/* Create kernel arguments */


//	err = clSetKernelArg(rt.ocl.kernels[0], 0, rt.sdl.pixel_amount * sizeof(cl_uint), NULL);//empty declaration for local memory.
	err = clSetKernelArg(rt.ocl.kernels[0], 0, sizeof(cl_mem), &(rt.ocl.result_gpu_buf));
//	err |= clSetKernelArg(rt.ocl.kernels[0], 1, sizeof(cl_mem), &(rt.ocl.scene_gpu_buf));
	if (err < 0)
		return (debug_perror("Couldn't create a kernel argument"));



	/* Enqueue kernel */
	err = clEnqueueNDRangeKernel(rt.ocl.cmd_queue, rt.ocl.kernels[0], 2, NULL /*dim_offsets*/, work_dim, 
			NULL /*&local_size*/, 0, NULL, NULL); 
	if (err < 0)
		return (debug_perror("Couldn't enqueue the kernel"));
	/* Read the kernel's output */
	err = clEnqueueReadBuffer(rt.ocl.cmd_queue, rt.ocl.result_gpu_buf, CL_TRUE, 0, 
			sizeof(uint) * rt.sdl.pixel_amount, rt.canvas->pixels, 0, NULL, NULL);
	if(err < 0)
		return (debug_perror("Couldn't read the buffer"));




	clReleaseKernel(rt.ocl.kernels[0]);
	clReleaseMemObject(rt.ocl.result_gpu_buf);
//	clReleaseMemObject(rt.ocl.scene_gpu_buf);
}

void	render()
{
	// fill the canvas->pixels buffer here
	if (render_init())
	{
		debug_output_error("Rendering failed: ", TRUE);
		return ;
	}
}