/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_get_error_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

/*
** run-time and JIT compiler errors
*/

static const char	*opencl_get_error_string5(cl_int error)
{
	if (error == -58)
		return ("CL_INVALID_EVENT");
	else if (error == -59)
		return ("CL_INVALID_OPERATION");
	else if (error == -60)
		return ("CL_INVALID_GL_OBJECT");
	else if (error == -61)
		return ("CL_INVALID_BUFFER_SIZE");
	else if (error == -62)
		return ("CL_INVALID_MIP_LEVEL");
	else if (error == -63)
		return ("CL_INVALID_GLOBAL_WORK_SIZE");
	else if (error == -64)
		return ("CL_INVALID_PROPERTY");
	else if (error == -65)
		return ("CL_INVALID_IMAGE_DESCRIPTOR");
	else if (error == -66)
		return ("CL_INVALID_COMPILER_OPTIONS");
	else if (error == -67)
		return ("CL_INVALID_LINKER_OPTIONS");
	else if (error == -68)
		return ("CL_INVALID_DEVICE_PARTITION_COUNT");
	return ("Unknown OpenCL error, or error below -1000 (extension error)");
}

static const char	*opencl_get_error_string4(cl_int error)
{
	if (error == -46)
		return ("CL_INVALID_KERNEL_NAME");
	else if (error == -47)
		return ("CL_INVALID_KERNEL_DEFINITION");
	else if (error == -48)
		return ("CL_INVALID_KERNEL");
	else if (error == -49)
		return ("CL_INVALID_ARG_INDEX");
	else if (error == -50)
		return ("CL_INVALID_ARG_VALUE");
	else if (error == -51)
		return ("CL_INVALID_ARG_SIZE");
	else if (error == -52)
		return ("CL_INVALID_KERNEL_ARGS");
	else if (error == -53)
		return ("CL_INVALID_WORK_DIMENSION");
	else if (error == -54)
		return ("CL_INVALID_WORK_GROUP_SIZE");
	else if (error == -55)
		return ("CL_INVALID_WORK_ITEM_SIZE");
	else if (error == -56)
		return ("CL_INVALID_GLOBAL_OFFSET");
	else if (error == -57)
		return ("CL_INVALID_EVENT_WAIT_LIST");
	return (opencl_get_error_string5(error));
}

static const char	*opencl_get_error_string3(cl_int error)
{
	if (error == -34)
		return ("CL_INVALID_CONTEXT");
	else if (error == -35)
		return ("CL_INVALID_QUEUE_PROPERTIES");
	else if (error == -36)
		return ("CL_INVALID_COMMAND_QUEUE");
	else if (error == -37)
		return ("CL_INVALID_HOST_PTR");
	else if (error == -38)
		return ("CL_INVALID_MEM_OBJECT");
	else if (error == -39)
		return ("CL_INVALID_IMAGE_FORMAT_DESCRIPTOR");
	else if (error == -40)
		return ("CL_INVALID_IMAGE_SIZE");
	else if (error == -41)
		return ("CL_INVALID_SAMPLER");
	else if (error == -42)
		return ("CL_INVALID_BINARY");
	else if (error == -43)
		return ("CL_INVALID_BUILD_OPTIONS");
	else if (error == -44)
		return ("CL_INVALID_PROGRAM");
	else if (error == -45)
		return ("CL_INVALID_PROGRAM_EXECUTABLE");
	return (opencl_get_error_string4(error));
}

static const char	*opencl_get_error_string2(cl_int error)
{
	if (error == -12)
		return ("CL_MAP_FAILURE");
	else if (error == -13)
		return ("CL_MISALIGNED_SUB_BUFFER_OFFSET");
	else if (error == -14)
		return ("CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST");
	else if (error == -15)
		return ("CL_COMPILE_PROGRAM_FAILURE");
	else if (error == -16)
		return ("CL_LINKER_NOT_AVAILABLE");
	else if (error == -17)
		return ("CL_LINK_PROGRAM_FAILURE");
	else if (error == -18)
		return ("CL_DEVICE_PARTITION_FAILED");
	else if (error == -19)
		return ("CL_KERNEL_ARG_INFO_NOT_AVAILABLE");
	else if (error == -30)
		return ("CL_INVALID_VALUE");
	else if (error == -31)
		return ("CL_INVALID_DEVICE_TYPE");
	else if (error == -32)
		return ("CL_INVALID_PLATFORM");
	else if (error == -33)
		return ("CL_INVALID_DEVICE");
	return (opencl_get_error_string3(error));
}

const char			*opencl_get_error_string(cl_int error)
{
	if (error == 0)
		return ("CL_SUCCESS");
	else if (error == -1)
		return ("CL_DEVICE_NOT_FOUND");
	else if (error == -2)
		return ("CL_DEVICE_NOT_AVAILABLE");
	else if (error == -3)
		return ("CL_COMPILER_NOT_AVAILABLE");
	else if (error == -4)
		return ("CL_MEM_OBJECT_ALLOCATION_FAILURE");
	else if (error == -5)
		return ("CL_OUT_OF_RESOURCES");
	else if (error == -6)
		return ("CL_OUT_OF_HOST_MEMORY");
	else if (error == -7)
		return ("CL_PROFILING_INFO_NOT_AVAILABLE");
	else if (error == -8)
		return ("CL_MEM_COPY_OVERLAP");
	else if (error == -9)
		return ("CL_IMAGE_FORMAT_MISMATCH");
	else if (error == -10)
		return ("CL_IMAGE_FORMAT_NOT_SUPPORTED");
	else if (error == -11)
		return ("CL_BUILD_PROGRAM_FAILURE");
	return (opencl_get_error_string2(error));
}
