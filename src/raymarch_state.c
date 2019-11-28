#include <unistd.h>
#include <mlx.h>
#include "raymarch_state.h"
#include "mlx_keys.h"

static void loop(struct s_state *this)
{
}
static void render(struct s_state *this)
{
	t_raymarch_struct *raymarch_struct = ((t_raymarch_struct*)this->instance_struct);
	t_opencl_instance *opencl_instance = raymarch_struct->opencl_instance;
	cl_int color = 0x0F00F0;
	int ret = clSetKernelArg(opencl_instance->kernel, 1, sizeof(cl_int), &color);
	raymarch_struct->opencl_instance->render(opencl_instance);
	mlx_put_image_to_window(this->mlx_instance.mlx, this->mlx_instance.window, opencl_instance->image->image, 0, 0);
}
static void on_key(int keyid, struct s_state *this)
{
	printf("%d!\n", keyid);
	if (keyid == MLX_K_ESC)
	{
		printf("ESC!\n");
		this->on_close(this);
		exit(0);
	}
}
static void on_mouse_move(cl_int2 position, cl_int2 delta, struct s_state *this)
{

}
static void on_mouse_down(int keyid, cl_int2 position, struct s_state *this)
{
}
static void on_mouse_up(int keyid, cl_int2 position, struct s_state *this)
{
}
static void on_close(struct s_state *this)
{
	t_opencl_instance *ocl_instance = ((t_raymarch_struct*)this->instance_struct)->opencl_instance;
	t_raymarch_state_destroy(this);
	t_opencl_instance_destroy(ocl_instance);
}

void		t_raymarch_state_destroy(t_state *object)
{
	free(object->instance_struct);
	free(object);
}

t_state		*t_raymarch_state_create(t_mlx_instance mlx_instance)
{
	t_state *object;
	t_raymarch_struct *raymarch_struct;

	if(!(object = (t_state*)malloc(sizeof(t_state))))
	{
		write(1, "t_raymarch_state_create: cannot allocate t_state.\n", 50);
		exit(1);
	}
	if(!(raymarch_struct = (t_raymarch_struct*)malloc(sizeof(t_raymarch_struct))))
	{
		write(1, "t_raymarch_state_create: cannot allocate s_raymarch_struct.\n", 60);
		exit(1);
	}
	raymarch_struct->opencl_instance = t_opencl_instance_create("../programs/hello.cl", mlx_instance);
	object->mlx_instance = mlx_instance;
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