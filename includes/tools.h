#ifndef TOOLS_H
#define TOOLS_H

#include <OpenCL/cl.h>

int		get_file_size(char *filename);
char	*read_file(char *filename);
void	print_device_info(cl_device_id device_id);

#endif
