#include <unistd.h>
#include <mlx.h>
#include "raymarch_state.h"
#include "mlx_keys.h"
#include "linear_alg.h"
#include <math.h>

static void loop(struct s_state *this)
{
}
static void render(struct s_state *this)
{
	t_raymarch_struct *this_str = ((t_raymarch_struct*)this->instance_struct);
	t_opencl_instance *opencl_instance = this_str->opencl_instance;
	cl_float2 iresolution = (cl_float2){this->mlx_instance.window_geometry.x, this->mlx_instance.window_geometry.y};
	cl_float camera_radius = 50.0f;
	cl_float3 camera_position = (cl_float3){
		camera_radius * cosf(this_str->rotation.x) * sinf(this_str->rotation.y),
		camera_radius * sinf(this_str->rotation.x) * sinf(this_str->rotation.y),
		camera_radius * cosf(this_str->rotation.y)};
	cl_float16 view = look_at(camera_position, (cl_float3){0.0f, 0.0f, 0.0f}, (cl_float3){0.0f, 0.0f, 1.0f});
	cl_float16 proj = orthographic((cl_float4){500.0f, -500.0f, 500.0f, -500.0f}, 0.1f, 100.0f);
//	cl_float16 proj = perspective(1000.0f/1000.0f, 180.0f, 0.1f, 100.0f);
	cl_float16 projView = mat4_mat4_mul(&proj, &view);
	cl_float16 inverseProjView = float16_inverse(projView);

	clSetKernelArg(opencl_instance->kernel, 1, sizeof(cl_float2), &iresolution);
	clSetKernelArg(opencl_instance->kernel, 2, sizeof(cl_float16), &inverseProjView);
	clSetKernelArg(opencl_instance->kernel, 3, sizeof(cl_float3), &camera_position);
	printf("(%f %f)\n", this_str->rotation.x, this_str->rotation.y);
	opencl_instance->render(opencl_instance);
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
	t_raymarch_struct *this_str = (t_raymarch_struct*)this->instance_struct;
	this_str->rotation.x += delta.x / 500.0f;
	this_str->rotation.y += delta.y / 500.0f;
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
	raymarch_struct->rotation = (cl_float3){0.0f, 0.0f, 0.0f};
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