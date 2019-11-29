#ifndef RAYMARCH_STATE_H
#define RAYMARCH_STATE_H

#include "state.h"
#include "opencl_instance.h"

typedef struct	s_raymarch_struct
{
	t_opencl_instance	*opencl_instance;
	cl_float3			rotation;
}				t_raymarch_struct;

void		t_raymarch_state_destroy(t_state *object);
t_state		*t_raymarch_state_create(t_mlx_instance mlx_instance);

#endif
