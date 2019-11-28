#include <unistd.h>
#include "opencl_instance.h"
#include "mlx_instance.h"
#include "tools.h"
#include "libft.h"

static void			init_opencl(char *program_path, t_opencl_instance *object, t_image *image)
{
	const int	image_size = (image->geometry.x * image->bpp / 8) + (image->geometry.y * image->stride);

	// Load kernel.
	char	*source_str;
	size_t source_size;

	if (!(source_str = read_file(program_path)))
	{
		write(1, "init_opencl: cannot open file.\n", 31);
		exit(1);
	}
	source_size = ft_strlen(source_str);
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	if (ret != CL_SUCCESS)
	{
		write(1, "clGetPlatformIDs failed.\n", 25);
		exit(1);
	}
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
						&device_id, &ret_num_devices);
	print_device_info(device_id);
	if (ret != CL_SUCCESS)
	{
		write(1, "clGetDeviceIDs failed\n", 22);
		exit(1);
	}
	// Create an OpenCL context
	object->context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
	{
		write(1, "clCreateContext failed\n", 23);
		exit(1);
	}
	// Create a command queue
	object->command_queue = clCreateCommandQueue(object->context, device_id, 0, &ret);
	if (ret != CL_SUCCESS)
	{
		write(1, "clCreateCommandQueue failed\n", 28);
		exit(1);
	}
	// Create memory buffers on the device for each vector
	object->img_mem_obj = clCreateBuffer(object->context, CL_MEM_WRITE_ONLY,
										 image_size * sizeof(char), NULL, &ret);
	if (ret != CL_SUCCESS)
	{
		write(1, "clCreateBuffer failed\n", 22);
		exit(1);
	}
	// Create a program from the kernel source
	object->program = clCreateProgramWithSource(object->context, 1,
												(const char **)&source_str, (const size_t *)&source_size, &ret);
	if (ret != CL_SUCCESS)
	{
		write(1, "clCreateProgramWithSource failed\n", 33);
		exit(1);
	}
	// Build the program
	ret = clBuildProgram(object->program, 1, &device_id, NULL, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		write(1, "clBuildProgram failed\n", 22);
		size_t size;
		clGetProgramBuildInfo(object->program, device_id, CL_PROGRAM_BUILD_LOG ,0,NULL,&size);
		if (size != 0)
		{
			char *build_log = malloc(size);
			clGetProgramBuildInfo(object->program, device_id, CL_PROGRAM_BUILD_LOG ,size,build_log,NULL);
			write(1, build_log, size);
			free(build_log);
		}
		exit(1);
	}
	size_t size;
	clGetProgramBuildInfo(object->program, device_id, CL_PROGRAM_BUILD_LOG ,0,NULL,&size);
	if (size != 0)
	{
		char *build_log = malloc(size);
		clGetProgramBuildInfo(object->program, device_id, CL_PROGRAM_BUILD_LOG ,size,build_log,NULL);
		write(1, build_log, size);
		free(build_log);
//		exit(0);
	}

	// Create the OpenCL kernel
	object->kernel = clCreateKernel(object->program, "main_image", &ret);
	if (ret != CL_SUCCESS)
	{
		write(1, "clCreateKernel failed\n", 22);
		exit(1);
	}

	// Set the arguments of the kernel
	ret = clSetKernelArg(object->kernel, 0, sizeof(cl_mem), (void *)&object->img_mem_obj);
}

static void	render(struct s_opencl_instance *this)
{
	int ret;

	ret = clEnqueueWriteBuffer(this->command_queue, this->img_mem_obj, CL_TRUE, 0,
							   this->image->size * sizeof(char), this->image->ptr, 0, NULL, NULL);
	size_t global_item_size = this->image->geometry.x * this->image->geometry.y; // Process the entire list
	ret = clEnqueueNDRangeKernel(this->command_queue, this->kernel, 1, NULL,
								 &global_item_size, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(this->command_queue, this->img_mem_obj, CL_TRUE, 0,
							  this->image->size * sizeof(char), this->image->ptr, 0, NULL, NULL);
	clFlush(this->command_queue);
	clFinish(this->command_queue);
}

t_opencl_instance	*t_opencl_instance_create(char *program_path, t_mlx_instance mlx_instance)
{
	t_opencl_instance *object;

	if (!(object = (t_opencl_instance*)malloc(sizeof(t_opencl_instance))))
	{
		write(1, "t_opencl_instance_create: cannot allocate opencl struct.", 56);
		exit(1);
	}
	t_image *image = t_image_create(mlx_instance.mlx, mlx_instance.window_geometry);
	object->image = image;
	init_opencl(program_path, object, image);
	object->render = &render;
	return (object);
}

void				t_opencl_instance_destroy(t_opencl_instance *object)
{
	clFlush(object->command_queue);
	clFinish(object->command_queue);
	clReleaseKernel(object->kernel);
	clReleaseProgram(object->program);
	clReleaseMemObject(object->img_mem_obj);
	clReleaseCommandQueue(object->command_queue);
	clReleaseContext(object->context);
	t_image_destroy(object->image);
	free(object);
}