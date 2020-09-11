#include <stdlib.h>
#include "julia_state.h"
#include "state.h"
#include "mlx_keys.h"



static void				on_mouse_move(t_ivec2 position, t_ivec2 delta,
										 struct s_state *this)
{
	t_julia_struct	*this_str;

	this_str = (t_julia_struct*)this->instance_struct;
	if (!this_str->lmb_pressed && !this_str->rmb_pressed)
	{
		this_str->julia_parameters.s[0] -= delta.s[0] / 500.0f;
		this_str->julia_parameters.s[1] -= delta.s[1] / 500.0f;
	}
	if (this_str->lmb_pressed)
	{
		this_str->target_camera_position.s[0] -= (float)delta.s[0] / (1.0f -
			this_str->target_zoom + 0.1f) / (200000.0f * (1.0f -
			this_str->target_zoom + 0.1f));
		this_str->target_camera_position.s[1] += (float)delta.s[1] / (1.0f -
			this_str->target_zoom + 0.1f) / (200000.0f * (1.0f -
			this_str->target_zoom + 0.1f));
	}
}

static void				on_mouse_down(int keyid, t_ivec2 position,
										 struct s_state *this)
{
	t_julia_struct	*this_str;

	this_str = (t_julia_struct*)this->instance_struct;
	if (keyid == MLX_M_SCROLL_UP)
		this_str->target_zoom += 0.01f;
	if (keyid == MLX_M_SCROLL_DOWN)
		this_str->target_zoom -= 0.01f;
	if (keyid == MLX_M_LEFT)
		this_str->lmb_pressed = GL_TRUE;
	if (keyid == MLX_M_RIGHT)
		this_str->rmb_pressed = GL_TRUE;
}

static void				on_mouse_up(int keyid, t_ivec2 position,
									   struct s_state *this)
{
	t_julia_struct	*this_str;

	this_str = (t_julia_struct*)this->instance_struct;
	if (keyid == MLX_M_LEFT)
		this_str->lmb_pressed = GL_FALSE;
	if (keyid == MLX_M_RIGHT)
		this_str->rmb_pressed = GL_FALSE;
}

static void				on_close(struct s_state *this)
{
	t_julia_state_destroy(this);
}

void					setup_julia_state1(t_state	*object)
{
	object->on_mouse_move = &on_mouse_move;
	object->on_mouse_up = &on_mouse_up;
	object->on_mouse_down = &on_mouse_down;
	object->on_close = &on_close;
}