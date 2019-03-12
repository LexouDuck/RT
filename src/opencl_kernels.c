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

#include "../rt.h"
#include "debug.h"

//TODO move to better pastures
inline t_u32		ft_min(t_u32 a, t_u32 b)
{
	return (a < b ? a : b);
}

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

/*
** The formula for calculating global id is:
**		(gx , gy) = (wx * Sx + sx + Fx, wy * Sy + sy + Fy)
**
** w{x,y} = work-group id{0, 1}
** S{x,y} = work-group size{0, 1}
** s{x,y} = local id{0, 1}
** F{x,y} = global ID offset{0, 1}
*/

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

/*
static int			render_piecewise_3d_kernel_subloops(cl_kernel krnl,
														t_work_array work_steps,
														t_work_array offsets)
{

}
*/
int					opencl_enqueue_piecewise_3d_kernel(cl_kernel krnl)
{
	static const int	dim_rank = 3;
	int					err;
	t_work_array		work_dim_end;
	t_work_array		work_offsets;
	t_work_array		work_steps;

	work_steps = *((t_work_array *)rt.ocl.gpu.max_witems_per_dim);
	work_offsets.z = 0;
	while (work_offsets.z < rt.scene.work_dims.z)
	{
		work_offsets.y = 0;
		while (work_offsets.y < rt.scene.work_dims.y)
		{
			work_offsets.x = 0;
			while (work_offsets.x < rt.scene.work_dims.x)
			{
				work_dim_end = (t_work_array){
					ft_min(work_steps.x, rt.scene.work_dims.x - work_offsets.x),
					ft_min(work_steps.y, rt.scene.work_dims.y - work_offsets.y),
					ft_min(work_steps.z, rt.scene.work_dims.z - work_offsets.z)};
				if ((err = clEnqueueNDRangeKernel(rt.ocl.cmd_queue, krnl, dim_rank,
												(size_t const *)&work_offsets,
												(size_t const *)&work_dim_end,
														NULL, 0, NULL, NULL)) < 0)
					return (opencl_handle_error(err, "render_piecewise_3d_kernel:"
													" enqueue kernel failed."));
				work_offsets.x += work_steps.x;
			}
			work_offsets.y += work_steps.y;
		}
		work_offsets.z += work_steps.z;
		rt.ocl.render_progress = (float)work_offsets.z / rt.scene.work_dims.z;
	}
	return (OK);
}
