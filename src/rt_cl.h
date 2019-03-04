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

/*
** #  define CL_USE_DEPRECATED_OPENCL_1_2_APIS
** #  include <stdint.h>
*/

#ifndef __RT_CL_H
# define __RT_CL_H

# ifdef __APPLE__
#  define CL_TARGET_OPENCL_VERSION	120
#  define CL_SILENCE_DEPRECATION
#  include <OpenCL/cl.h>

# elif (defined __WIN32__)
#  define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#  define CL_TARGET_OPENCL_VERSION	120
#  include "CL/cl.h"

# else
#  define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#  define CL_TARGET_OPENCL_VERSION	120
#  include <CL/cl.h>

# endif

/*
** ************************************************************************** *|
**                                  OpenCL                                    *|
** ************************************************************************** *|
*/

/*
** see clBuildProgram in OpenCL API for details
** TODO experiment with optimization options
*/
# define RT_CL_PLATFORM_MAX_AMOUNT		2
# define RT_CL_PLATFORM_UNINITIALIZED	-1

/*
**	-cl-opt-disable
**	-Werror
**	-g
**	-cl-nv-verbose
**	-cl-kernel-arg-info
**	-cl-fast-relaxed-math
**	-cl-unsafe-math-optimizations
**	-cl-mad-enable
*/
# define RT_CL_PROGRAM_OPTIONS			"-Werror"
# define RT_CL_PROGRAM_SOURCE			"concat.cl"

# define RT_CL_KERNEL_AMOUNT			2
# define RT_CL_KERNEL_0					"rt_cl_build_scene"
# define RT_CL_KERNEL_1					"rt_cl_render"

typedef struct	s_gpu
{
//	gpu info
	cl_device_id	id;
	cl_ulong		global_mem_size;
	cl_uint			comp_unit_nb;
	size_t			max_kernel_args_size;
	size_t			max_witems_per_wgroup;
	cl_uint			max_nd_range;
	// should be replaced by value of max_nd_range
	size_t			max_witems_per_dim[4];
}				t_gpu;

typedef	struct	s_gpu_buffers
{
	cl_mem			scene;
	cl_mem			canvas_pixels;
}				t_gpu_buffers;

typedef struct	s_cl
{
	cl_platform_id		platforms[RT_CL_PLATFORM_MAX_AMOUNT];
	cl_uint				platform_amount;
	cl_uint				gpu_platform_index;
	t_gpu				gpu;
	cl_context			context;
	cl_program			program;
	cl_command_queue	cmd_queue;
	cl_kernel			kernels[RT_CL_KERNEL_AMOUNT];
	t_gpu_buffers		gpu_buf;
	float				render_progress;
//	cl_int				status;
}				t_cl;

/*
** opencl_init.c
*/
int				opencl_init_gpu_memory(void);
int				opencl_init(int platform_index);

/*
** opencl_utils.c
*/
int				opencl_set_device_info(void);
void			opencl_refresh_gpu_memory_buffers(void);
void			opencl_freeall(void);
void			opencl_log_compiler(void);

#endif
