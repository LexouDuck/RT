/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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

int		render_init(SDL_Surface *screen, t_rt_cl *ocl)
{
	int err = 0;
//assign group size and work dim etc //fat data buffers
//kernels //setting args is done later ? //clCreateKernelsInProgram

	ocl->kernels[0] = clCreateKernel(ocl->program, RT_CL_KERNEL_0, &err);
	if (err < 0)
		return (debug_perror("Couldn't create a kernel for "RT_CL_KERNEL_0));

//TODO CREATESCENE

//	ocl->scene_hostbuf = clCreateBuffer(context, CL_MEM_READ_ONLY |
//			CL_MEM_COPY_HOST_PTR, sizeof(t_scene), &scene, &err); //TODO Once pointer based BVH are implemented, edit here so that scene is the right format, or add args to kernel

	size_t	work_dim[2] = {WINDOW_W, WINDOW_H};
	int		pixel_nb = work_dim[0] * work_dim[1];
	ocl->result_gpu_buf = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE |
			CL_MEM_COPY_HOST_PTR, sizeof(uint) * pixel_nb, screen->pixels, &err);
	/* Create kernel arguments */


//	err = clSetKernelArg(ocl->kernels[0], 0, pixel_nb * sizeof(cl_uint), NULL);//empty declaration for local memory.
	err = clSetKernelArg(ocl->kernels[0], 0, sizeof(cl_mem), &(ocl->result_gpu_buf));
//	err |= clSetKernelArg(ocl->kernels[0], 1, sizeof(cl_mem), &(ocl->scene_gpu_buf));
	if (err < 0)
		return (debug_perror("Couldn't create a kernel argument"));



	/* Enqueue kernel */
	err = clEnqueueNDRangeKernel(ocl->cmd_queue, ocl->kernels[0], 2, NULL /*dim_offsets*/, work_dim, 
			NULL /*&local_size*/, 0, NULL, NULL); 
	if (err < 0)
		return (debug_perror("Couldn't enqueue the kernel"));
	/* Read the kernel's output */
	err = clEnqueueReadBuffer(ocl->cmd_queue, ocl->result_gpu_buf, CL_TRUE, 0, 
			sizeof(uint) * pixel_nb, screen->pixels, 0, NULL, NULL);
	if(err < 0)
		return (debug_perror("Couldn't read the buffer"));




	clReleaseKernel(ocl->kernels[0]);
	clReleaseMemObject(ocl->result_gpu_buf);
//	clReleaseMemObject(ocl->scene_gpu_buf);
}

void	render(t_rt_sdl *sdl, t_rt_cl *ocl)
{
	// fill the screen->pixels buffer here
	if (render_init(sdl->screen, ocl))
	{
		debug_output_error("Rendering failed: ", TRUE);
		return ;
	}
	// and update the window display
	if (SDL_RenderClear(sdl->renderer))
		debug_output_error("Error during render screen clear: ", TRUE);
	if (SDL_RenderCopy(sdl->renderer, sdl->screen, NULL, NULL))
		debug_output_error("Error during render copy: ", TRUE);
	SDL_RenderPresent(sdl->renderer);
}
