#include <unistd.h>
#include <mlx.h>
#include "raymarch_state.h"
#include "mlx_keys.h"
#include "linear_alg.h"
#include <math.h>

#include <OpenGL/gl.h>

static void loop(struct s_state *this)
{

}
static void render(struct s_state *this)
{

    t_raymarch_struct *this_str = (t_raymarch_struct *)this->instance_struct;
    glBindVertexArrayAPPLE(this_str->vertex_buffer.vao);

    glUseProgram(this_str->shader.shaderProgram);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}
static void on_key(int keyid, struct s_state *this)
{
    t_raymarch_struct *this_str = (t_raymarch_struct*)this->instance_struct;
	printf("%d!\n", keyid);
	if (keyid == MLX_K_ESC)
	{
		printf("ESC!\n");
		this->on_close(this);
		exit(0);
	}
	if (keyid == MLX_K_Q)
    {
	    this_str->mandelbulb_iterations++;
    }
	if (keyid == MLX_K_E)
    {
        this_str->mandelbulb_iterations--;
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
    t_raymarch_struct *this_str = (t_raymarch_struct*)this->instance_struct;
    if(keyid == MLX_M_SCROLL_UP)
        this_str->camera_radius += 0.1f;
    if(keyid == MLX_M_SCROLL_DOWN)
        this_str->camera_radius -= 0.1f;
}
static void on_mouse_up(int keyid, cl_int2 position, struct s_state *this)
{
}
static void on_close(struct s_state *this)
{
//	t_opencl_instance *ocl_instance = ((t_raymarch_struct*)this->instance_struct)->opencl_instance;
	t_raymarch_state_destroy(this);
//	t_opencl_instance_destroy(ocl_instance);
}

void		t_raymarch_state_destroy(t_state *object)
{
    const t_raymarch_struct *this_str = (t_raymarch_struct *)object->instance_struct;
    destroyShader(this_str->shader);
	free(object->instance_struct);
	free(object);
}

static t_vertex_buffer create_vertex_buffer()
{
    const GLfloat square[4][3] = {
            { -1.0,  1.0,  0.0 }, // Top left
            {  1.0,  1.0,  0.0 }, // Top right
            {  1.0, -1.0,  0.0 }, // Bottom right
            { -1.0, -1.0,  0.0 }, // Bottom left
    };
    const uint32_t countVBOs = 1;
    t_vertex_buffer buffer;
    glGenBuffers(countVBOs, &buffer.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);
    uint32_t sizeInBytes = (4*3) * sizeof(GLfloat);
    glBufferData(GL_ARRAY_BUFFER,sizeInBytes, square, GL_STATIC_DRAW);

    // VAO

    glGenVertexArraysAPPLE(1, &buffer.vao);
    glBindVertexArrayAPPLE(buffer.vao);

    // call glBindBuffer() and glBindVertexArray() first
    // ...so that OpenGL knows what buffers we want to work on
    const uint32_t positionAttributeIndex = 0;
    glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    // Enable our attribute within the current VAO
    glEnableVertexAttribArray(positionAttributeIndex);

    glBindVertexArrayAPPLE(0);

    return (buffer);
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
//	raymarch_struct->opencl_instance = t_opencl_instance_create("./programs/hello.cl", mlx_instance);
	raymarch_struct->rotation = (cl_float3){0.0f, 0.0f, 0.0f};
    raymarch_struct->camera_radius = 10.0f;
    raymarch_struct->mandelbulb_iterations = 1.0f;
    raymarch_struct->shader = createShader("./programs/vert.glsl", "./programs/frag.glsl");

    raymarch_struct->vertex_buffer = create_vertex_buffer();
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