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

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"

static int		opencl_initialize_platforms(void)
{
	cl_int		error;
	t_bool		has_gpu;

	if ((error = clGetPlatformIDs(RT_CL_PLATFORM_MAX_AMOUNT,
		g_rt.ocl.platforms, &(g_rt.ocl.platform_amount))) < 0)
		return (opencl_handle_error(error, "opencl_get_platform_and_gpu:"
		" could not get platform IDs."));
	has_gpu = FALSE;
	g_rt.ocl.gpu_platform_index = -1;
	while (!has_gpu && ++g_rt.ocl.gpu_platform_index < g_rt.ocl.platform_amount)
	{
		if ((error =
			clGetDeviceIDs(g_rt.ocl.platforms[g_rt.ocl.gpu_platform_index],
			CL_DEVICE_TYPE_GPU, 1, &(g_rt.ocl.gpu.id), NULL)) == CL_SUCCESS)
			has_gpu = TRUE;
		else
			debug_output_value("No GPU found for platform -> ",
				(char *)opencl_get_error_string(error), FALSE);
	}
	if (!has_gpu)
		return (debug_perror("opencl_get_platform_and_gpu:"
		" no GPU device found."));
	return (OK);
}

static int		opencl_get_platform_and_gpu(int platform_index)
{
	cl_int		error;

	if (platform_index == RT_CL_PLATFORM_UNINITIALIZED)
	{
		if (opencl_initialize_platforms())
			return (debug_perror("opencl_get_platform_and_gpu:"
			" error while querying available platforms."));
	}
	else
	{
		g_rt.ocl.gpu_platform_index = platform_index;
		if ((error =
			clGetDeviceIDs(g_rt.ocl.platforms[g_rt.ocl.gpu_platform_index],
			CL_DEVICE_TYPE_GPU, 1, &(g_rt.ocl.gpu.id), NULL)) < 0)
			return (opencl_handle_error(error, "opencl_get_platform_and_gpu:"
			" error getting selected platform's GPU."));
	}
	debug_output_value("Platform amount found: ",
		ft_u64_to_str(g_rt.ocl.platform_amount), TRUE);
	opencl_set_device_info();
	return (OK);
}

static int		opencl_create_context_and_queue(void)
{
	cl_int		error;

	g_rt.ocl.context = clCreateContext(NULL, 1, &(g_rt.ocl.gpu.id),
									NULL, NULL, &error);
	if (error < 0)
		return (opencl_handle_error(error, "opencl_create_context_and_queue:"
		" could not create context."));
	g_rt.ocl.cmd_queue = clCreateCommandQueue(g_rt.ocl.context,
											g_rt.ocl.gpu.id, 0, &error);
	if (error < 0)
		return (opencl_handle_error(error, "opencl_create_context_and_queue:"
		" could not create command queue."));
	return (OK);
}

/*
** cl_program clCreateProgramWithSource (cl_context context,
**  	cl_uint count,
**   	const char **strings,
**   	const size_t *lengths,
**   	cl_int *errcode_ret)
**
** cl_int clBuildProgram (cl_program program,
** 		cl_uint num_devices,
** 		const cl_device_id *device_list,
** 		const char *options,
** 		void (CL_CALLBACK *pfn_notify)(cl_program program, void *user_data),
** 		void *user_data)
**
** also see clGetProgramInfo and clGetProgramBuildInfo
**
** TODO add errno to debug_perror ?
*/

static int		opencl_read_and_build_program(void)
{
	int			fd;
	cl_int		error;
	char		*file_buf;
	size_t		file_len;

	if ((fd = open(RT_CL_PROGRAM_SOURCE, O_RDONLY)) == -1)
		return (debug_perror("opencl_read_and_build_program: open failed."));
	if (ft_readfile(fd, &file_buf, (size_t)-1))
		return (debug_perror("opencl_read_and_build_program: read failed."));
	file_len = ft_strlen(file_buf);
	g_rt.ocl.program = clCreateProgramWithSource(g_rt.ocl.context, 1,
		(char const **)(&file_buf), &file_len, &error);
	free(file_buf);
	if (error < 0)
		return (debug_perror("opencl_read_and_build_program:"
		" clCreateProgramWithSource returned error."));
	if ((error = clBuildProgram(g_rt.ocl.program, 1, &(g_rt.ocl.gpu.id),
		RT_CL_PROGRAM_OPTIONS, NULL, NULL)) < 0)
	{
		opencl_log_compiler();
		return (opencl_handle_error(error, "opencl_read_and_build_program:"
		" build failed."));
	}
	return (close(fd) == -1 ? debug_perror("opencl_read_and_build_program:"
	" close failed.") : OK);
}

/*
** WATCH OUT the following function creates the kernel array in reverse order
**	on Mac-Intel.
**	if ((err = clCreateKernelsInProgram(g_rt.ocl.program,
**		RT_CL_KERNEL_AMOUNT, g_rt.ocl.kernels, NULL)) < 0)
**		return (debug_perror("opencl_init: could not init kernels."));
*/

int				opencl_init(int platform_index)
{
	if (opencl_get_platform_and_gpu(platform_index))
		return (debug_perror("opencl_init:"
		" could not find an appropriate GPU/platform."));
	if (opencl_create_context_and_queue())
		return (debug_perror("opencl_init:"
		" could not create device, context or queue."));
	if (opencl_read_and_build_program())
		return (debug_perror("opencl_init: could not build program."));
	if (opencl_init_gpu_memory())
		return (debug_perror("opencl_init:"
		" could not initialize gpu memory buffers."));
	if (opencl_init_kernels())
		return (debug_perror("opencl_init:"
		" could not initialize kernels."));
	return (OK);
}
