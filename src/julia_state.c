#include <unistd.h>
#include <mlx.h>
#include "julia_state.h"
#include "mlx_keys.h"
#include "linear_alg.h"
#include <math.h>
#include "math_tools.h"
#include <stdlib.h>
#include "libft.h"

#include <OpenGL/gl.h>

static void loop(struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct *)this->instance_struct;
    this_str->zoom = lerpf(this_str->zoom, this_str->target_zoom, 0.1f);
    this_str->camera_position = lerpvec2(this_str->camera_position, this_str->target_camera_position, 0.1f);
    this_str->palette_shift = lerpf(this_str->palette_shift, this_str->target_palette_shift, 0.1f);
    if (this_str->target_zoom < -1.5f)
        this_str->target_zoom = -1.5f;
    if (this_str->target_zoom > 1.3f)
        this_str->target_zoom = 1.3f;
//    printf("%f\n", (this_str->target_zoom + 1.5f)/2.8f);
}
static void render(struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct *)this->instance_struct;

    glBindVertexArrayAPPLE(this_str->vertex_buffer.vao);
    glUseProgram(this_str->shader.shaderProgram);
    glUniform2f(this_str->iresolution_location, (GLfloat)this->mlx_instance.window_geometry.x, (GLfloat)this->mlx_instance.window_geometry.y);
    glUniform2fv(this_str->camera_position_location, 1, this_str->camera_position.s);
    glUniform1f(this_str->zoom_location, this_str->zoom);
    glUniform3fv(this_str->col_pal_location, 4, this_str->palette->s);
    glUniform2fv(this_str->julia_parameters_location, 1, this_str->julia_parameters.s);
    glUniform1f(this_str->palette_shift_location, this_str->palette_shift);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}
static void on_key(int keyid, struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct*)this->instance_struct;
//    printf("%d!\n", keyid);
    if (keyid == MLX_K_ESC)
    {
//        printf("ESC!\n");
        this->on_close(this);
        exit(0);
    }
    if(keyid == MLX_K_1)
        ft_memcpy(this_str->palette, (t_vec3[]){(t_vec3){0.5, 0.5, 0.5},
                                                (t_vec3){0.5, 0.5, 0.5}, (t_vec3){1.0, 1.0, 1.0},
                                                (t_vec3){0.00, 0.33, 0.67}}, sizeof(this_str->palette));
    if(keyid == MLX_K_2)
        ft_memcpy(this_str->palette, (t_vec3[]){(t_vec3){0.5, 0.5, 0.5},
                                                (t_vec3){0.5, 0.5, 0.5}, (t_vec3){1.0, 1.0, 1.0},
                                                (t_vec3){0.00, 0.10, 0.20}}, sizeof(this_str->palette));
    if(keyid == MLX_K_3)
        ft_memcpy(this_str->palette, (t_vec3[]){(t_vec3){0.5, 0.5, 0.5},
                                                (t_vec3){0.5, 0.5, 0.5}, (t_vec3){1.0, 1.0, 1.0},
                                                (t_vec3){0.30, 0.20, 0.20}}, sizeof(this_str->palette));
    if(keyid == MLX_K_4)
        ft_memcpy(this_str->palette, (t_vec3[]){(t_vec3){0.5, 0.5, 0.5},
                                                (t_vec3){0.5, 0.5, 0.5}, (t_vec3){1.0, 1.0, 0.5},
                                                (t_vec3){0.80, 0.90, 0.30}}, sizeof(this_str->palette));
    if(keyid == MLX_K_5)
        ft_memcpy(this_str->palette, (t_vec3[]){(t_vec3){0.5, 0.5, 0.5},
                                                (t_vec3){0.5, 0.5, 0.5}, (t_vec3){1.0, 0.7, 0.4},
                                                (t_vec3){0.00, 0.15, 0.20}}, sizeof(this_str->palette));
    if(keyid == MLX_K_6)
        ft_memcpy(this_str->palette, (t_vec3[]){(t_vec3){0.5, 0.5, 0.5},
                                                     (t_vec3){0.5, 0.5, 0.5},
                                                     (t_vec3){2.0, 1.0, 0.0},
                                                     (t_vec3){0.50, 0.20, 0.25}}, sizeof(this_str->palette));
    if(keyid == MLX_K_7)
        ft_memcpy(this_str->palette, (t_vec3[]){(t_vec3){0.8, 0.5, 0.4},
         (t_vec3){0.2, 0.4, 0.2}, (t_vec3){2.0, 1.0, 1.0},
         (t_vec3){0.00, 0.25, 0.25}}, sizeof(this_str->palette));
    if (keyid == MLX_K_Q)
        this_str->target_palette_shift+=0.1f;
    if (keyid == MLX_K_E)
        this_str->target_palette_shift-=0.1f;
    if (keyid == MLX_K_W)
    {
        this_str->target_zoom = 1.0f;
        this_str->target_camera_position = (t_vec2){0.0f, 0.0f};
    }
}
static void on_mouse_move(t_ivec2 position, t_ivec2 delta, struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct*)this->instance_struct;
    if(!this_str->lmb_pressed && !this_str->rmb_pressed)
    {
        this_str->julia_parameters.x -= delta.x / 500.0f;
        this_str->julia_parameters.y -= delta.y / 500.0f;
    }
    if(this_str->lmb_pressed)
    {
        this_str->target_camera_position.x -= (float)delta.x / (500.0f + (1.0f - (this_str->target_zoom + 1.5f)/2.8f)*2000.0f);
        this_str->target_camera_position.y += (float)delta.y / (500.0f + (1.0f - (this_str->target_zoom + 1.5f)/2.8f)*2000.0f);
    }

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
    if(keyid == MLX_M_RIGHT)
        this_str->rmb_pressed = GL_TRUE;
}
static void on_mouse_up(int keyid, t_ivec2 position, struct s_state *this)
{
    t_julia_struct *this_str = (t_julia_struct*)this->instance_struct;
    if(keyid == MLX_M_LEFT)
        this_str->lmb_pressed = GL_FALSE;
    if(keyid == MLX_M_RIGHT)
        this_str->rmb_pressed = GL_FALSE;
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
    destroy_shader(this_str->shader);
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
    julia_struct->camera_position = (t_vec2){10.0f, 10.0f};
    julia_struct->target_camera_position = (t_vec2){0.0f, 0.0f};
    julia_struct->zoom = 0.0f;
    julia_struct->target_zoom = 1.0f;
    julia_struct->shader = create_shader("./programs/vert.glsl", fragment);
    julia_struct->lmb_pressed = GL_FALSE;
    julia_struct->vertex_buffer = create_vertex_buffer();
    julia_struct->iresolution_location = glGetUniformLocation(julia_struct->shader.shaderProgram, "iResolution");
    julia_struct->camera_position_location = glGetUniformLocation(julia_struct->shader.shaderProgram, "cameraPosition");
    julia_struct->zoom_location = glGetUniformLocation(julia_struct->shader.shaderProgram, "zoom");
    julia_struct->palette_shift_location = glGetUniformLocation(julia_struct->shader.shaderProgram, "paletteShift");
    julia_struct->col_pal_location = glGetUniformLocation(julia_struct->shader.shaderProgram, "colPal");
    julia_struct->julia_parameters_location = glGetUniformLocation(julia_struct->shader.shaderProgram, "juliaParameters");
    julia_struct->palette[0] = (t_vec3){0.5, 0.5, 0.5};
    julia_struct->palette[1] = (t_vec3){0.5, 0.5, 0.5};
    julia_struct->palette[2] = (t_vec3){1.0, 1.0, 1.0};
    julia_struct->palette[3] = (t_vec3){0.00, 0.10, 0.20};
    julia_struct->julia_parameters = (t_vec2){-0.123, 0.745};
    julia_struct->palette_shift = 0.0f;
    julia_struct->target_palette_shift = 0.0f;

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