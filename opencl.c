/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

# define CL_USE_DEPRECATED_OPENCL_1_1_APIS
# define CL_TARGET_OPENCL_VERSION	110
# include <opencl.h>

typedef struct	s_opencl
{
    cl_platform_id		platform_id;
    cl_device_id		device_id;
    cl_uint				devices;
    cl_uint				platforms;
    cl_context			context;
    cl_command_queue	command_queue;
    cl_program			program;
    cl_kernel			kernel;
}				t_opencl;

int	init_opencl()
{
	t_opencl	opencl;
    cl_int		result;
    int			fd;
    char		*file;
    size_t		length;

	opencl.platform_id = NULL;
	opencl.device_id = NULL;
	result = clGetPlatformIDs(1, &opencl.platform_id, &opencl.platforms);
	result = clGetDeviceIDs(opencl.platform_id,
		CL_DEVICE_TYPE_GPU, 1, &opencl.device_id, &opencl.devices);
	opencl.context = clCreateContext(
		NULL, 1, &opencl.device_id, NULL, NULL, &result);
	opencl.command_queue = clCreateCommandQueue(
		opencl.context, opencl.device_id, 0, &result);
	if ((fd = open("vector.c", O_RDONLY)) < 0)
	{
		ft_putendl("Error: could not open file");
		return (ERROR);
	}
	file = read_file(fd);
	length = ft_strlen(file);
	opencl.program = clCreateProgramWithSource(opencl.context, 1, 
		(const char **)&file, (const size_t *)&length, &result);
	result = clBuildProgram(
		opencl.program, 1, &opencl.device_id, NULL, NULL, NULL);
	opencl.kernel = clCreateKernel(opencl.program, "vector_add", &result);
	return (OK);
}