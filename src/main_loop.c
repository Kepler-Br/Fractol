#include <unistd.h>
#include <mlx.h>
#include "main_loop.h"
#include "state.h"

static int loop(struct s_main_loop *this)
{
	this->state->loop(this->state);
	this->render(this);
	return (0);
}
static int render(struct s_main_loop *this)
{
	this->state->render(this->state);
	return (0);
}
static void run(struct s_main_loop *this)
{
	mlx_loop(this->mlx_instance.mlx);
}
static int on_key(int keyid, struct s_main_loop *this)
{
	this->state->on_key(keyid, this->state);
	return (0);
}
static int on_mouse_move(int x, int y, struct s_main_loop *this)
{
	cl_int2 position = (cl_int2){x, y};
	cl_int2 delta = (cl_int2){x - this->prev_mouse_position.x, y - this->prev_mouse_position.y};
	this->prev_mouse_position = position;
	this->state->on_mouse_move(position, delta, this->state);
	return (0);
}
static int on_mouse_down(int keyid, int x, int y, struct s_main_loop *this)
{
	cl_int2 position = (cl_int2){x, y};
	this->state->on_mouse_down(keyid, position, this->state);
	return (0);
}
static int on_mouse_up(int keyid, int x, int y, struct s_main_loop *this)
{
	cl_int2 position = (cl_int2){x, y};
	this->state->on_mouse_up(keyid, position, this->state);
	return (0);
}
static int on_close(struct s_main_loop *this)
{
	this->state->on_close(this->state);
	t_main_loop_destroy(this);
	exit(0);
}

void t_main_loop_destroy(struct s_main_loop *this)
{
	mlx_destroy_window(this->mlx_instance.mlx, this->mlx_instance.window);
	free(this);
}

t_main_loop *t_main_loop_create(char *title, cl_uint2 window_geometry, struct s_state *state)
{
	t_main_loop		*object;
	t_mlx_instance	mlx_instance;

	if(!(object = (t_main_loop*)malloc(sizeof(t_main_loop))))
	{
		write(1, "t_main_loop_create: could not allocate memory.", 46);
		exit(1);
	}
	if(!(mlx_instance.mlx = mlx_init()))
	{
		write(1, "t_main_loop_create: cannot init mlx.", 36);
		exit(1);
	}
	if(!(mlx_instance.window = mlx_new_window(mlx_instance.mlx, window_geometry.x, window_geometry.y, title)))
	{
		write(1, "t_main_loop_create: cannot init mlx window.", 43);
		exit(1);
	}
	object->prev_mouse_position = (cl_int2){0, 0};

	mlx_instance.window_geometry = window_geometry;
	object->mlx_instance = mlx_instance;
	object->state = state;
	state->mlx_instance = mlx_instance;

	object->loop = &loop;
	object->render = &render;
	object->run = &run;
	object->on_key = &on_key;
	object->on_mouse_move = &on_mouse_move;
	object->on_mouse_down = &on_mouse_down;
	object->on_mouse_up = &on_mouse_up;
	object->on_close = &on_close;
	mlx_hook(object->mlx_instance.window, 2, 0, object->on_key, (void *)object);
	mlx_hook(object->mlx_instance.window, 6, 0, object->on_mouse_move, (void *)object);
	mlx_hook(object->mlx_instance.window, 4, 0, object->on_mouse_down, (void *)object);
	mlx_hook(object->mlx_instance.window, 5, 0, object->on_mouse_up, (void *)object);
	mlx_hook(object->mlx_instance.window, 17, 0, object->on_close, (void *)object);
	mlx_loop_hook(object->mlx_instance.mlx, object->loop, (void *)object);
	return (object);
}