#ifndef OPENCL_INSTANCE_H
#define OPENCL_INSTANCE_H

#include <OpenCL/cl.h>
#include "image.h"
#include "mlx_instance.h"

typedef struct	s_opencl_instance
{
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;

	cl_mem				img_mem_obj;

	t_image				*image;
	void	(*render)(struct s_opencl_instance *this);
}				t_opencl_instance;

t_opencl_instance	*t_opencl_instance_create(char *program_path, t_mlx_instance mlx_instance);
void				t_opencl_instance_destroy(t_opencl_instance *object);

#endif
