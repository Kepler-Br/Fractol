#ifndef MLX_INSTANCE_H
#define MLX_INSTANCE_H

#include <OpenCL/cl.h>

typedef struct	s_mlx_instance
{
	void		*mlx;
	void		*window;
	cl_uint2	window_geometry;
}				t_mlx_instance;

#endif
