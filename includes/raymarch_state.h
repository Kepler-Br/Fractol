#ifndef RAYMARCH_STATE_H
#define RAYMARCH_STATE_H

#include "state.h"
//#include "opencl_instance.h"
#include "shader.h"
#include "vertex_buffer.h"

typedef struct	s_raymarch_struct
{
//	t_opencl_instance	*opencl_instance;
	cl_float3			rotation;
    cl_float            camera_radius;
    cl_float            target_camera_radius;
    cl_float            mandelbulb_power;
    cl_float            target_mandelbulb_power;
    t_shader shader;
    t_vertex_buffer     vertex_buffer;
}				t_raymarch_struct;

void		t_raymarch_state_destroy(t_state *object);
t_state		*t_raymarch_state_create(t_mlx_instance mlx_instance);

#endif
