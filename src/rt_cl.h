/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RT_CL_H
# define __RT_CL_H

# ifdef __APPLE__
#  define CL_SILENCE_DEPRECATION
#  include <OpenCL/cl.h>
# elif (defined __WIN32__)
#  define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#  define CL_TARGET_OPENCL_VERSION	120
#  include "CL/cl.h"
# else
#  include <CL/cl.h>
# endif

/*
# define HALF_PI		0x1.921fb54442d18p0
# define PI				0x1.921fb54442d18p1
# define TAU 			0x1.921fb54442d18p2
# define INV_PI			0x1.45f306dc9c883p-2
# define INV_TAU		0x1.45f306dc9c883p-3
*/

/*
** ************************************************************************** *|
**                                  OpenCL                                    *|
** ************************************************************************** *|
*/
/*
** see clBuildProgram in OpenCL API for details
// TODO experiment with optimization options
*/
# define RT_CL_HOST_PLATFORM_AMOUNT	1
# define RT_CL_PROGRAM_SOURCE		"src/rt_cl_render.cl"//"tmp_srcs/opencl_sandbox/qjulia_kernel.cl"//
# define RT_CL_PROGRAM_OPTIONS		""//-Werror"// -g" //-cl-nv-verbose" //-cl-kernel-arg-info" //-cl-fast-relaxed-math" //-cl-unsafe-math-optimizations //-cl-mad-enable
# define RT_CL_KERNEL_NB			1
# define RT_CL_KERNEL_0				"rt_cl_render"//"QJuliaKernel"//

typedef struct	s_gpu
{
	//gpu info
	cl_device_id	id;
	cl_ulong		global_mem_size;
	cl_uint			comp_unit_nb;
	size_t			max_kernel_args_size;
	size_t			max_witems_per_wgroup;
	cl_uint			max_nd_range;
	size_t			max_witems_per_dim[16];//should be replaced by value of max_nd_range
	//gpu mem
//	t_u8			*in_buf_hostptr;
//	t_u8			*out_buf_hostptr;
//	cl_mem			in_buf;
//	cl_mem			out_buf;
}				t_gpu;

typedef	struct	s_gpu_buffers
{
	cl_mem			scene;
	cl_mem			res_canvas;
//	cl_mem			rand_seed;
}				t_gpu_buffers;

typedef struct	s_cl
{
	cl_platform_id		platform[RT_CL_HOST_PLATFORM_AMOUNT];
	t_gpu				gpu;
	cl_context			context;
	cl_program			program;
	cl_command_queue	cmd_queue;
	cl_kernel			kernels[RT_CL_KERNEL_NB];
	t_gpu_buffers		gpu_buf;
	cl_int				status;
}				t_cl;

/*
** init_opencl.c
*/
int		init_opencl();
#endif