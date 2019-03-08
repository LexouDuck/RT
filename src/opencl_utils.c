/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_utils.c                                     :+:      :+:    :+:   */
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

/*
**	cl_int clGetDeviceInfo(
**		cl_device_id device, 			//gpu id
**		cl_device_info param_name,		// a flag, see man
**		size_t param_value_size,		// sizeof(*(pointer passed param_value))
**		void *param_value,				// returns queried arg value
**		size_t *param_value_size_ret)	// returns actual size of return arg
**	return CL_SUCCESS, CL_INVALID_DEVICE or
*/

/*
** 1 thread (work item) per core; each compute unit on the gpu may have multiple cores
**
** work group size = product of work group dim(i) ; also equal to number of threads
** (work items) in work group. This number should always be a multiple of the number
** of cores per compute unit (cpcu generally = 16 on nvidia and 64 on AMD)
**
** CL_QUEUE_SIZE
**
** CL_DEVICE_VENDOR					:
** CL_DEVICE_NAME						:
** CL_DRIVER_VERSION					:
** CL_DEVICE_PROFILE					:
** CL_DEVICE_VERSION					:
** CL_DEVICE_OPENCL_C_VERSION			:
** CL_DEVICE_MAX_COMPUTE_UNITS			:
** CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS	:
** CL_DEVICE_MAX_WORK_ITEM_SIZES		:
** CL_DEVICE_MAX_WORK_GROUP_SIZE		:
** CL_DEVICE_MEM_BASE_ADDR_ALIGN 		:
** CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE	:
** CL_DEVICE_MAX_CLOCK_FREQUENCY		:
** CL_DEVICE_LOCAL_MEM_SIZE			:
** CL_DEVICE_MAX_MEM_ALLOC_SIZE		:
**
** cl_int clGetPlatformInfo( 	cl_platform_id platform,
**   	cl_platform_info param_name, //CL_PLATFORM_...
**   	size_t param_value_size,
**   	void *param_value,
**   	size_t *param_value_size_ret)
** CL_PLATFORM_PROFILE
** CL_PLATFORM_VERSION
** CL_PLATFORM_NAME
** CL_PLATFORM_VENDOR
*/

static void		opencl_print_device_info(char *gpu_name,
										char *platform_name,
										char *gpu_ocl_version)
{
	debug_output_value("Platform index: ",
		ft_u32_to_str(rt.ocl.gpu_platform_index), TRUE);
	debug_output_value("Platform name: ", platform_name, FALSE);
	debug_output_value("Device name: ", gpu_name, FALSE);
	debug_output_value("Version n° ", gpu_ocl_version, FALSE);
	debug_output_value("- global mem size: 0x",
		ft_u64_to_hex(rt.ocl.gpu.global_mem_size), TRUE);
	debug_output_value("- compute units: 0x",
		ft_u32_to_hex(rt.ocl.gpu.comp_unit_nb), TRUE);
	debug_output_value("- max kernel args size: 0x",
		ft_u64_to_hex(rt.ocl.gpu.max_kernel_args_size), TRUE);
	debug_output_value("- max work items per group: 0x",
		ft_u64_to_hex(rt.ocl.gpu.max_witems_per_wgroup), TRUE);
	debug_output_value("- max nD range: 0x",
		ft_u32_to_hex(rt.ocl.gpu.max_nd_range), TRUE);
	debug_output("- max work items per dim:\n");
	debug_output_value("\t- x: 0x",
		ft_u64_to_hex(rt.ocl.gpu.max_witems_per_dim[0]), TRUE);
	debug_output_value("\t- y: 0x",
		ft_u64_to_hex(rt.ocl.gpu.max_witems_per_dim[1]), TRUE);
	debug_output_value("\t- z: 0x",
		ft_u64_to_hex(rt.ocl.gpu.max_witems_per_dim[2]), TRUE);
}

int			opencl_set_device_info(void)
{
	char	gpu_name[256];
	char	platform_name[256];
	char	gpu_ocl_version[16];

	clGetPlatformInfo(rt.ocl.platforms[rt.ocl.gpu_platform_index],
						CL_PLATFORM_NAME, 256, platform_name, NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong),
						&(rt.ocl.gpu.global_mem_size), NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_ulong),
						&(rt.ocl.gpu.comp_unit_nb), NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_NAME, 256, gpu_name, NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_VERSION, 16, gpu_ocl_version, NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(size_t),
						&(rt.ocl.gpu.max_kernel_args_size), NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t),
						&(rt.ocl.gpu.max_witems_per_wgroup), NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
						sizeof(cl_uint),
						&(rt.ocl.gpu.max_nd_range), NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_MAX_WORK_ITEM_SIZES,
						sizeof(size_t) * rt.ocl.gpu.max_nd_range,
						&(rt.ocl.gpu.max_witems_per_dim), NULL);
	opencl_print_device_info(gpu_name, platform_name, gpu_ocl_version);
	return (OK);
}

int			opencl_init_gpu_memory(void)
{
	int		err;

	err = CL_SUCCESS;
	rt.ocl.gpu_buf.scene = clCreateBuffer(rt.ocl.context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(t_scene), &rt.scene, &err);
	if (err < 0)
		return (debug_perror("Couldn't create read buffer for "RT_CL_KERNEL_0));
	rt.ocl.gpu_buf.canvas_pixels = clCreateBuffer(rt.ocl.context,
		CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_u32) * rt.scene.work_dim[0] * rt.scene.work_dim[1],
		rt.canvas->pixels, &err);
	if (err < 0)
		return (debug_perror("Couldn't create write buffer for "RT_CL_KERNEL_1));
	return (OK);
}

void		opencl_refresh_gpu_memory_buffers(void)
{
	clReleaseMemObject(rt.ocl.gpu_buf.canvas_pixels);
	clReleaseMemObject(rt.ocl.gpu_buf.scene);
	opencl_init_gpu_memory();
}

void		opencl_freeall(void)
{
	int		i;

	i = -1;
	while (++i < RT_CL_KERNEL_AMOUNT)
		clReleaseKernel(rt.ocl.kernels[i]);
	clReleaseMemObject(rt.ocl.gpu_buf.canvas_pixels);
	clReleaseMemObject(rt.ocl.gpu_buf.scene);
	clReleaseCommandQueue(rt.ocl.cmd_queue);
	clReleaseProgram(rt.ocl.program);
	clReleaseContext(rt.ocl.context);
}

void		opencl_log_compiler(void)
{
	char	*file_buf;
	size_t	file_len;

	file_buf = NULL;
	clGetProgramBuildInfo(rt.ocl.program, rt.ocl.gpu.id, CL_PROGRAM_BUILD_LOG,
			0, NULL, &file_len);
	if (!(file_buf = (char *)malloc(file_len + 1)))
		return ;
	file_buf[file_len] = '\0';
	clGetProgramBuildInfo(rt.ocl.program, rt.ocl.gpu.id, CL_PROGRAM_BUILD_LOG,
			file_len + 1, file_buf, NULL);
	debug_output(file_buf);
	free(file_buf);
}
