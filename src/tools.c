#include "tools.h"
#include <fcntl.h>
#include <unistd.h>

int		get_file_size(char *filename)
{
	const int		buff_size = 100;
	unsigned char	buff[buff_size];
	int				total_size;
	int				fd;
	int				ret;

	total_size = 0;
	fd = open(filename, O_RDONLY);
	while((ret = read(fd, buff, buff_size)))
	{
		if (ret == -1)
			return (-1);
		total_size += ret;
	}
	close(fd);
	return (total_size);
}

char	*read_file(char *filename)
{
	const int	file_size = get_file_size(filename);
	char		*text;
	int			fd;

	if (file_size == -1)
		return (NULL);
	text = (char *)malloc(file_size + 1);
	fd = open(filename, O_RDONLY);
	read(fd, text, file_size);
	text[file_size] = '\0';
	close(fd);
	return (text);
}

void	print_device_info(cl_device_id device_id)
{
	char	*device_name;
	cl_uint	unsigned_int;
	cl_bool	bool;
	size_t	t_size;

	if(!(device_name = (char *)malloc(sizeof(char)*255)))
		exit(0);
	clGetDeviceInfo(device_id, CL_DEVICE_AVAILABLE, sizeof(cl_bool), &bool, NULL);
	printf("Available: %d\n", bool);
	clGetDeviceInfo(device_id, CL_DEVICE_NAME, 255, device_name, NULL);
	printf("Device name: %s\n", device_name);
	clGetDeviceInfo(device_id, CL_DEVICE_VERSION, 255, device_name, NULL);
	printf("Device version: %s\n", device_name);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_SAMPLERS, sizeof(cl_uint), &unsigned_int, NULL);
	printf("Max samplers: %u\n", unsigned_int);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &t_size, NULL);
	printf("Max work group size: %u\n", unsigned_int);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &unsigned_int, NULL);
	printf("Max compute units: %u\n", unsigned_int);
	free(device_name);
}