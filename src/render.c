/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 14:01:52 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft_memory.h"
#include "../rt.h"
#include "debug.h"
#include "rt_scene.h"

/*
** code to print program as is stored in memory
** char str[40000];
**
** err = clGetProgramInfo(rt.ocl.program, CL_PROGRAM_SOURCE, 40000, str, NULL);
** 		if (err < 0)
** 		return (debug_perror("Couldn't create read source "RT_CL_PROGRAM_SOURCE));
** 		printf("%s", str);
*/

/*
** run-time and JIT compiler errors
*/

const char	*get_error_string(cl_int error)
{
	switch (error)
	{
		case 0:
		return ("CL_SUCCESS");
		case -1:
		return ("CL_DEVICE_NOT_FOUND");
		case -2:
		return ("CL_DEVICE_NOT_AVAILABLE");
		case -3:
		return ("CL_COMPILER_NOT_AVAILABLE");
		case -4:
		return ("CL_MEM_OBJECT_ALLOCATION_FAILURE");
		case -5:
		return ("CL_OUT_OF_RESOURCES");
		case -6:
		return ("CL_OUT_OF_HOST_MEMORY");
		case -7:
		return ("CL_PROFILING_INFO_NOT_AVAILABLE");
		case -8:
		return ("CL_MEM_COPY_OVERLAP");
		case -9:
		return ("CL_IMAGE_FORMAT_MISMATCH");
		case -10:
		return ("CL_IMAGE_FORMAT_NOT_SUPPORTED");
		case -11:
		return ("CL_BUILD_PROGRAM_FAILURE");
		case -12:
		return ("CL_MAP_FAILURE");
		case -13:
		return ("CL_MISALIGNED_SUB_BUFFER_OFFSET");
		case -14:
		return ("CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST");
		case -15:
		return ("CL_COMPILE_PROGRAM_FAILURE");
		case -16:
		return ("CL_LINKER_NOT_AVAILABLE");
		case -17:
		return ("CL_LINK_PROGRAM_FAILURE");
		case -18:
		return ("CL_DEVICE_PARTITION_FAILED");
		case -19:
		return ("CL_KERNEL_ARG_INFO_NOT_AVAILABLE");
		// compile-time errors
		case -30:
		return ("CL_INVALID_VALUE");
		case -31:
		return ("CL_INVALID_DEVICE_TYPE");
		case -32:
		return ("CL_INVALID_PLATFORM");
		case -33:
		return ("CL_INVALID_DEVICE");
		case -34:
		return ("CL_INVALID_CONTEXT");
		case -35:
		return ("CL_INVALID_QUEUE_PROPERTIES");
		case -36:
		return ("CL_INVALID_COMMAND_QUEUE");
		case -37:
		return ("CL_INVALID_HOST_PTR");
		case -38:
		return ("CL_INVALID_MEM_OBJECT");
		case -39:
		return ("CL_INVALID_IMAGE_FORMAT_DESCRIPTOR");
		case -40:
		return ("CL_INVALID_IMAGE_SIZE");
		case -41:
		return ("CL_INVALID_SAMPLER");
		case -42:
		return ("CL_INVALID_BINARY");
		case -43:
		return ("CL_INVALID_BUILD_OPTIONS");
		case -44:
		return ("CL_INVALID_PROGRAM");
		case -45:
		return ("CL_INVALID_PROGRAM_EXECUTABLE");
		case -46:
		return ("CL_INVALID_KERNEL_NAME");
		case -47:
		return ("CL_INVALID_KERNEL_DEFINITION");
		case -48:
		return ("CL_INVALID_KERNEL");
		case -49:
		return ("CL_INVALID_ARG_INDEX");
		case -50:
		return ("CL_INVALID_ARG_VALUE");
		case -51:
		return ("CL_INVALID_ARG_SIZE");
		case -52:
		return ("CL_INVALID_KERNEL_ARGS");
		case -53:
		return ("CL_INVALID_WORK_DIMENSION");
		case -54:
		return ("CL_INVALID_WORK_GROUP_SIZE");
		case -55:
		return ("CL_INVALID_WORK_ITEM_SIZE");
		case -56:
		return ("CL_INVALID_GLOBAL_OFFSET");
		case -57:
		return ("CL_INVALID_EVENT_WAIT_LIST");
		case -58:
		return ("CL_INVALID_EVENT");
		case -59:
		return ("CL_INVALID_OPERATION");
		case -60:
		return ("CL_INVALID_GL_OBJECT");
		case -61:
		return ("CL_INVALID_BUFFER_SIZE");
		case -62:
		return ("CL_INVALID_MIP_LEVEL");
		case -63:
		return ("CL_INVALID_GLOBAL_WORK_SIZE");
		case -64:
		return ("CL_INVALID_PROPERTY");
		case -65:
		return ("CL_INVALID_IMAGE_DESCRIPTOR");
		case -66:
		return ("CL_INVALID_COMPILER_OPTIONS");
		case -67:
		return ("CL_INVALID_LINKER_OPTIONS");
		case -68:
		return ("CL_INVALID_DEVICE_PARTITION_COUNT");
		// extension errors
		case -1000:
		return ("CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR");
		case -1001:
		return ("CL_PLATFORM_NOT_FOUND_KHR");
		case -1002:
		return ("CL_INVALID_D3D10_DEVICE_KHR");
		case -1003:
		return ("CL_INVALID_D3D10_RESOURCE_KHR");
		case -1004:
		return ("CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR");
		case -1005:
		return ("CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR");
		default:
		return ("Unknown OpenCL error");
	}
}

static int		render_launch_kernel0_build_scene(void)
{
	int err;

	err = CL_SUCCESS;
	err = clEnqueueWriteBuffer(rt.ocl.cmd_queue, rt.ocl.gpu_buf.scene, CL_TRUE,
			0, sizeof(t_scene), &(rt.scene), 0, NULL, NULL);
	if (err < 0)
		return (debug_perror("Couldn't enqueue write to gpu for "RT_CL_KERNEL_0));
	err = clSetKernelArg(rt.ocl.kernels[0], 0, sizeof(cl_mem), &(rt.ocl.gpu_buf.scene));
	if (err < 0)
		return (debug_perror("Couldn't create a kernel argument for "RT_CL_KERNEL_0));
	err = clEnqueueNDRangeKernel(rt.ocl.cmd_queue, rt.ocl.kernels[0], 1, NULL,
				&(rt.scene.object_amount), NULL, 0, NULL, NULL);
	if (err < 0)
	{
		debug_perror(get_error_string(err));
		return (debug_perror("Couldn't enqueue the kernel for "RT_CL_KERNEL_0));
	}
	if ((err = clFinish(rt.ocl.cmd_queue)) < 0)
		return (debug_perror("Couldn't finish "RT_CL_KERNEL_0));
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

static int			render_piecewise_2d_kernel(cl_kernel krnl)
{
	int		err;
	int		work_dim_amount;
	size_t	work_dim_array[2];
	size_t	work_offsets_array[2];
//	size_t	work_buffer_end[2];

	work_dim_amount = 2;
	work_dim_array[0] = rt.scene.work_dim[0];
	work_dim_array[1] = 1;//(size_t)rt.canvas_h;
	work_offsets_array[0] = 0;
	work_offsets_array[1] = 0;
	rt.ocl.render_progress = 0.;
	while (work_offsets_array[1] < (size_t)rt.scene.work_dim[1])
	{ 
		if ((err = clEnqueueNDRangeKernel(rt.ocl.cmd_queue, krnl,
			work_dim_amount, work_offsets_array, work_dim_array, NULL, 0, NULL, NULL)) < 0)
		{
			debug_perror(get_error_string(err));
			return (debug_perror("Couldn't enqueue a kernel for "RT_CL_KERNEL_1));
		}
		++work_offsets_array[1];
		rt.ocl.render_progress = ((float)work_offsets_array[1]) / rt.scene.work_dim[1];
	}
	return (OK);
}

static int			render_launch_kernel1_rendermain(void)
{
	int		err;
	int		kernel_arg_nbr;

	err = 0;
	kernel_arg_nbr = -1;
	err = clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr, sizeof(cl_mem),
							&(rt.ocl.gpu_buf.canvas_pixels));
	err |= clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr, sizeof(cl_mem),
							&(rt.ocl.gpu_buf.scene));
//	err |= clSetKernelArg(rt.ocl.kernels[1], ++kernel_arg_nbr, sizeof(cl_uint), NULL); TODO: check if adding this fixes work group seed problem
	if (err < 0)
	{
//		debug_perror(get_error_string(err));
		return (debug_perror("Couldn't create a kernel argument for "RT_CL_KERNEL_1));
	}
	render_piecewise_2d_kernel(rt.ocl.kernels[1]);
	if ((err = clFinish(rt.ocl.cmd_queue)) < 0)
	{
		debug_perror(get_error_string(err));
		return (debug_perror("Couldn't finish "RT_CL_KERNEL_1));
	}
	return (OK);
}

int			render_read_gpu_buffer(void)
{
	int err;

	err = 0;
//assign group size and work dim etc //fat data buffers
//kernels //setting args is done later ? //clCreateKernelsInProgram
	err = clEnqueueReadBuffer(rt.ocl.cmd_queue, rt.ocl.gpu_buf.canvas_pixels,
		CL_TRUE, 0, sizeof(t_u32) * rt.canvas_pixel_amount,
		rt.canvas->pixels, 0, NULL, NULL);
	if (err < 0)
	{
		debug_perror(get_error_string(err));
		return (debug_perror("render_read_gpu_buffer:"
			" couldn't read the buffer for "RT_CL_KERNEL_1));
	}
//	clReleaseKernel(rt.ocl.kernels[1]);
//	clReleaseKernel(rt.ocl.kernels[0]);
//	clReleaseMemObject(rt.ocl.gpu_buf.canvas_pixels);
//	clReleaseMemObject(rt.ocl.gpu_buf.scene);
//#endif
	return (OK);
}

int			render(void)
{
//	int		err;
//	rt.scene.render_mode = RENDERMODE_MCPT;
//	rt.scene.camera.model = CAMERA_MODEL_TMP;
//	rt.scene.camera.model = CAMERA_MODEL_FOCAL;
//	rt.scene.camera.model = CAMERA_MODEL_PINHOLE;
//	rt.scene.camera.model = CAMERA_MODEL_ORTHOGRAPHIC;
	rt.scene.camera.aperture = .1;
	rt.scene.camera.focal_length = 50.;
//rt.scene.render_mode = RENDERMODE_SOLIDCOLOR;
//rt.scene.objects[0].material = !lightsource;
//float intensity = 1. / 255.;
//rt.scene.objects[0].rgb = (cl_float3){255., 255., 255.};//((BG_COLOR & 0xFF0000) >> 16) * intensity, ((BG_COLOR & 0xFF00) >> 8) * intensity, (BG_COLOR & 0xFF) * intensity};
	rt.scene.random_seed_time = rt.sdl.current_frame;
	if (render_launch_kernel0_build_scene())
		return (ERROR);
	if (render_launch_kernel1_rendermain())
		return (ERROR);
	if (render_read_gpu_buffer())
		return (ERROR);
	return (OK);
}
