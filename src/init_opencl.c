/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
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
// TODO remove stdio include
#include <stdio.h>

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
1 thread (work item) per core; each compute unit on the gpu may have multiple cores

work group size = product of work group dim(i) ; also equal to number of threads
(work items) in work group. This number should always be a multiple of the number
of cores per compute unit (cpcu generally = 16 on nvidia and 64 on AMD)

CL_QUEUE_SIZE

CL_DEVICE_VENDOR					:
CL_DEVICE_NAME						:
CL_DRIVER_VERSION					:
CL_DEVICE_PROFILE					:
CL_DEVICE_VERSION					:
CL_DEVICE_OPENCL_C_VERSION			:
CL_DEVICE_MAX_COMPUTE_UNITS			:
CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS	:
CL_DEVICE_MAX_WORK_ITEM_SIZES		:
CL_DEVICE_MAX_WORK_GROUP_SIZE		:
CL_DEVICE_MEM_BASE_ADDR_ALIGN 		:
CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE	:
CL_DEVICE_MAX_CLOCK_FREQUENCY		:
CL_DEVICE_LOCAL_MEM_SIZE			:
CL_DEVICE_MAX_MEM_ALLOC_SIZE		:


cl_int clGetPlatformInfo( 	cl_platform_id platform,
  	cl_platform_info param_name, //CL_PLATFORM_...
  	size_t param_value_size,
  	void *param_value,
  	size_t *param_value_size_ret)
CL_PLATFORM_PROFILE
CL_PLATFORM_VERSION
CL_PLATFORM_NAME
CL_PLATFORM_VENDOR
*/
int				print_device_info()
{
	char	gpu_name[256];
	char	platform_name[256];
	char	gpu_ocl_version[16];

	//mem size
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong),
						&(rt.ocl.gpu.global_mem_size), NULL);
	//compute units
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_ulong),
						&(rt.ocl.gpu.comp_unit_nb), NULL);
	//check for availability ? for cache info ?
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_NAME, 256, gpu_name, NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_VERSION, 16, gpu_ocl_version, NULL);


	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(size_t),
						&(rt.ocl.gpu.max_kernel_args_size), NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t),
						&(rt.ocl.gpu.max_witems_per_wgroup), NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint),
						&(rt.ocl.gpu.max_nd_range), NULL);
	clGetDeviceInfo(rt.ocl.gpu.id, CL_DEVICE_MAX_WORK_ITEM_SIZES,
						sizeof(size_t) * rt.ocl.gpu.max_nd_range,
						&(rt.ocl.gpu.max_witems_per_dim), NULL);


	clGetPlatformInfo(rt.ocl.platform[0], CL_PLATFORM_NAME, 256, platform_name, NULL);


printf("Platform: %s | Device: %s | Version: %s\n\t"
		"- global mem size (nb of bytes): "OPENCL_LLU64"\n\t"//"- global mem size (nb of bytes): %#lx\n\t"
		"- compute unit nb: %u\n\t"
		"- max kernel args size: "OPENCL_LU64"\n\t"
		"- max work items per group: "OPENCL_LU64"\n\t"
		"- max nD range: %u\n\t"
		"- max_witems_per_dim: ("OPENCL_LU64", "OPENCL_LU64", "OPENCL_LU64")\n",
		platform_name, gpu_name, gpu_ocl_version,
		rt.ocl.gpu.global_mem_size,
		rt.ocl.gpu.comp_unit_nb,
		rt.ocl.gpu.max_kernel_args_size,
		rt.ocl.gpu.max_witems_per_wgroup,
		rt.ocl.gpu.max_nd_range,
		rt.ocl.gpu.max_witems_per_dim[0], rt.ocl.gpu.max_witems_per_dim[1], rt.ocl.gpu.max_witems_per_dim[2]
);
	return (OK);
}

//TODO: more precise error handling for OpenCL with flags etc.
int				create_device_context_and_queue()
{
	int			err;

	if ((err = clGetPlatformIDs(RT_CL_HOST_PLATFORM_AMOUNT, rt.ocl.platform, NULL)) != CL_SUCCESS)
	{
		printf("%d\n", err);
		return (debug_perror("OpenCL: could not get a platform ID."));
	}
//	if (clGetDeviceIDs(rt.ocl.platform, CL_DEVICE_TYPE_CPU, 1, &(rt.ocl.cpu), NULL))
//		return (ERROR);
	if ((err = clGetDeviceIDs(rt.ocl.platform[0], CL_DEVICE_TYPE_GPU, 1, &(rt.ocl.gpu.id), NULL)))
		return (debug_perror("OpenCL: no GPU device found."));
	
	print_device_info();
	rt.ocl.context = clCreateContext(NULL, 1, &(rt.ocl.gpu.id), NULL, NULL, &err);
	if (err < 0)
		return (debug_perror("OpenCL: could not create context."));
	rt.ocl.cmd_queue = clCreateCommandQueue(rt.ocl.context, rt.ocl.gpu.id, 0, &err);
	if (err < 0)
		return (debug_perror("OpenCL: could not create command queue."));
	return (OK);
}


/*
cl_program clCreateProgramWithSource (cl_context context,
  	cl_uint count,
  	const char **strings,
  	const size_t *lengths,
  	cl_int *errcode_ret)

cl_int clBuildProgram (cl_program program,
	cl_uint num_devices,
	const cl_device_id *device_list, 
	const char *options,
	void (CL_CALLBACK *pfn_notify)(cl_program program, void *user_data),
	void *user_data)

also see clGetProgramInfo and clGetProgramBuildInfo
 */
int				read_and_build_program()
{
	int			fd;
	cl_int		err;
	char		*file_buf;
	size_t		file_len;

	if ((fd = open(RT_CL_PROGRAM_SOURCE, O_RDONLY)) == -1)
		return (debug_perror("build_cl_program: file couldn't be opened"));//add errno to debug_perror?
	if (FT_Read_File(fd, &file_buf))
		return (debug_perror("build_cl_program: file couldn't be read"));
	file_len = FT_StringLength(file_buf);
	rt.ocl.program = clCreateProgramWithSource(rt.ocl.context, 1, (char const **)(&file_buf),
						&file_len, &err);
	free(file_buf);
	if (err < 0)
		return (debug_perror("build_cl_program: clCreateProgramWithSource returned error."));
	if ((err = clBuildProgram(rt.ocl.program, 1, &(rt.ocl.gpu.id), RT_CL_PROGRAM_OPTIONS, NULL, NULL)) < 0)
	{
		/* Find size of log and print to std output */
		clGetProgramBuildInfo(rt.ocl.program, rt.ocl.gpu.id, CL_PROGRAM_BUILD_LOG, 
				0, NULL, &file_len);
		file_buf = (char *)malloc(file_len + 1);
		file_buf[file_len] = '\0';
		clGetProgramBuildInfo(rt.ocl.program, rt.ocl.gpu.id, CL_PROGRAM_BUILD_LOG, 
				file_len + 1, file_buf, NULL);
		debug_output(file_buf);
		free(file_buf);
		return (debug_perror("build_cl_program: clBuildProgram returned error."));
	}
	if (close(fd) == -1)
		return (debug_perror("build_cl_program: file closed improperly"));//add errno to debug_perror ?
	return (OK);
}

int				init_opencl()
{
	if (create_device_context_and_queue())
		return (debug_perror("init_opencl: could not create device, context or queue."));
	if (read_and_build_program())
		return (debug_perror("init_opencl: could not build program."));
	return (OK);
}
