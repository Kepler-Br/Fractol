#ifndef STATE_H
#define STATE_H

#include "mlx_instance.h"

typedef struct	s_state
{
	t_mlx_instance	mlx_instance;
	void			*instance_struct;

	void			(*loop)(struct s_state *this);
	void			(*render)(struct s_state *this);

	void			(*on_key)(int keyid, struct s_state *this);
	void			(*on_mouse_move)(t_ivec2 position, t_ivec2 delta, struct s_state *this);
	void			(*on_mouse_down)(int keyid, t_ivec2 position, struct s_state *this);
	void			(*on_mouse_up)(int keyid, t_ivec2 position, struct s_state *this);
	void			(*on_close)(struct s_state *this);
}				t_state;

#endif
