#include <unistd.h>
#include <mlx.h>
#include "julia_state.h"
#include "mlx_keys.h"
#include "linear_alg.h"
#include <math.h>
#include "math_tools.h"
#include <stdlib.h>

#include <OpenGL/gl.h>

static void loop(struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct *)this->instance_struct;
    this_str->zoom = lerpf(this_str->zoom, this_str->target_zoom, 0.1f);
}
static void render(struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct *)this->instance_struct;

    glBindVertexArrayAPPLE(this_str->vertex_buffer.vao);
    glUseProgram(this_str->shader.shaderProgram);
    glUniform2f(this_str->iresolution_location, (GLfloat)this->mlx_instance.window_geometry.x, (GLfloat)this->mlx_instance.window_geometry.y);
    glUniform2fv(this_str->camera_position_location, 1, this_str->camera_position.s);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}
static void on_key(int keyid, struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct*)this->instance_struct;
    printf("%d!\n", keyid);
    if (keyid == MLX_K_ESC)
    {
        printf("ESC!\n");
        this->on_close(this);
        exit(0);
    }
//    if (keyid == MLX_K_Q)
//        this_str->target_mandelbulb_power+=0.1f;
//    if (keyid == MLX_K_E)
//        this_str->target_mandelbulb_power-=0.1f;
}
static void on_mouse_move(t_ivec2 position, t_ivec2 delta, struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct*)this->instance_struct;
//    if(this_str->lmb_pressed)
//    {
//        this_str->target_rotation.x -= delta.x / 500.0f;
//        this_str->target_rotation.y -= delta.y / 500.0f;
//    }
}
static void on_mouse_down(int keyid, t_ivec2 position, struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct*)this->instance_struct;
    if(keyid == MLX_M_SCROLL_UP)
        this_str->target_zoom += 0.01f;
    if(keyid == MLX_M_SCROLL_DOWN)
        this_str->target_zoom -= 0.01f;
    if(keyid == MLX_M_LEFT)
        this_str->lmb_pressed = GL_TRUE;
}
static void on_mouse_up(int keyid, t_ivec2 position, struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct*)this->instance_struct;
    if(keyid == MLX_M_LEFT)
        this_str->lmb_pressed = GL_FALSE;
}
static void on_close(struct s_state *this)
{
    t_julia_state_destroy(this);
}

void		t_julia_state_destroy(t_state *object)
{
    const t_julia_struct *this_str = (t_julia_struct *)object->instance_struct;
    glDeleteBuffers(1, &this_str->vertex_buffer.vbo);
    glDeleteVertexArraysAPPLE(1, &this_str->vertex_buffer.vao);
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
    glBufferData(GL_ARRAY_BUFFER, sizeInBytes, square, GL_STATIC_DRAW);

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

t_state		*t_julia_state_create(t_mlx_instance mlx_instance, char *fragment)
{
    t_state *object;
    t_julia_struct *julia_struct;

    if(!(object = (t_state*)malloc(sizeof(t_state))))
    {
        write(1, "t_julia_state_create: cannot allocate t_state.\n", 47);
        exit(1);
    }
    if(!(julia_struct = (t_julia_struct*)malloc(sizeof(t_julia_struct))))
    {
        write(1, "t_julia_state_create: cannot allocate s_raymarch_struct.\n", 57);
        exit(1);
    }
    julia_struct->camera_position = (t_vec2){0.0f, 0.0f};
    julia_struct->zoom = 0.0f;
    julia_struct->target_zoom = 1.0f;
    julia_struct->shader = createShader("./programs/vert.glsl", fragment);
    julia_struct->lmb_pressed = GL_FALSE;
    julia_struct->vertex_buffer = create_vertex_buffer();
    julia_struct->iresolution_location = glGetUniformLocation(julia_struct->shader.shaderProgram, "iResolution");
//    julia_struct->inversed_pv_location = glGetUniformLocation(julia_struct->shader.shaderProgram, "inversedProjectionView");
    julia_struct->camera_position_location = glGetUniformLocation(julia_struct->shader.shaderProgram, "cameraPosition");
//    julia_struct->fractal_parameter_location = glGetUniformLocation(julia_struct->shader.shaderProgram, "fractalParameter");

    object->mlx_instance = mlx_instance;
    object->instance_struct = julia_struct;
    object->on_mouse_move = &on_mouse_move;
    object->on_mouse_up = &on_mouse_up;
    object->on_mouse_down = &on_mouse_down;
    object->on_close = &on_close;
    object->on_key = &on_key;
    object->render = &render;
    object->loop = &loop;
    return (object);
}