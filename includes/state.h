#ifndef STATE_H
#define STATE_H

#include <OpenCL/cl.h>
#include "mlx_instance.h"

typedef struct	s_state
{
	t_mlx_instance	mlx_instance;
	void			*instance_struct;

	void			(*loop)(struct s_state *this);
	void			(*render)(struct s_state *this);

	void			(*on_key)(int keyid, struct s_state *this);
	void			(*on_mouse_move)(cl_int2 position, cl_int2 delta, struct s_state *this);
	void			(*on_mouse_down)(int keyid, cl_int2 position, struct s_state *this);
	void			(*on_mouse_up)(int keyid, cl_int2 position, struct s_state *this);
	void			(*on_close)(struct s_state *this);
}				t_state;

#endif
