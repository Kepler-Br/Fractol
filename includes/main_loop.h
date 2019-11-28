#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include <OpenCL/cl.h>
#include "mlx_instance.h"

struct s_state;

typedef struct	s_main_loop
{
	cl_int2 prev_mouse_position;
	struct s_state	*state;
	t_mlx_instance	mlx_instance;

	int				(*loop)(struct s_main_loop *this);
	int				(*render)(struct s_main_loop *this);

	void			(*run)(struct s_main_loop *this);

	int				(*on_key)(int keyid, struct s_main_loop *this);
	int				(*on_mouse_move)(int x, int y, struct s_main_loop *this);
	int				(*on_mouse_down)(int keyid, int x, int y, struct s_main_loop *this);
	int				(*on_mouse_up)(int keyid, int x, int y, struct s_main_loop *this);
	int				(*on_close)(struct s_main_loop *this);
}				t_main_loop;

t_main_loop		*t_main_loop_create(char *title, cl_uint2 geometry);
void			t_main_loop_destroy(struct s_main_loop *this);

#endif
