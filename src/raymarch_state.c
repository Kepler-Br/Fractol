#include "raymarch_state.h"
#include <unistd.h>


static int loop(struct s_state *this)
{
	return (0);
}
static int render(struct s_state *this)
{
	write(1, "render\n", 7);
	return (0);
}
static int on_key(int keyid, struct s_state *this)
{
	return (0);
}
static int on_mouse_move(cl_int2 position, cl_int2 delta, struct s_state *this)
{
	return (0);
}
static int on_mouse_down(int keyid, cl_int2 position, struct s_state *this)
{
	return (0);
}
static int on_mouse_up(int keyid, cl_int2 position, struct s_state *this)
{
	return (0);
}
static int on_close(struct s_state *this)
{
	t_raymarch_state_destroy(this);
	return (0);
}

void		t_raymarch_state_destroy(t_state *object)
{
	free(object->instance_struct);
	free(object);
}

t_state		*t_raymarch_state_create()
{
	t_state *object;
	t_raymarch_struct *raymarch_struct;

	if(!(object = (t_state*)malloc(sizeof(t_state))))
	{
		write(1, "t_raymarch_state_create: cannot allocate t_state.", 49);
		exit(1);
	}
	if(!(raymarch_struct = (t_raymarch_struct*)malloc(sizeof(t_raymarch_struct))))
	{
		write(1, "t_raymarch_state_create: cannot allocate s_raymarch_struct.", 59);
		exit(1);
	}
	object->instance_struct = raymarch_struct;
	object->on_mouse_move = &on_mouse_move;
	object->on_mouse_up = &on_mouse_up;
	object->on_mouse_down = &on_mouse_down;
	object->on_close = &on_close;
	object->on_key = &on_key;
	object->render = &render;
	object->loop = &loop;
	return (object);
}