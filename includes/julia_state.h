#ifndef JULIA_STATE_H
#define JULIA_STATE_H

#include "state.h"
#include "shader.h"
#include "vertex_buffer.h"
#include "linear_alg.h"

typedef struct	s_julia_struct
{
    t_vec2              camera_position;
    t_vec2              target_camera_position;
    GLfloat             zoom;
    GLfloat             target_zoom;
    GLboolean           lmb_pressed;
    GLboolean           rmb_pressed;
    t_shader            shader;
    t_vertex_buffer     vertex_buffer;
    t_vec3              palette[4];
    t_vec2              julia_parameters;
    GLfloat             palette_shift;
    GLfloat             target_palette_shift;

    GLint iresolution_location;
    GLint camera_position_location;
    GLint zoom_location;
    GLint col_pal_location;
    GLint julia_parameters_location;
    GLint palette_shift_location;
}				t_julia_struct;

void		t_julia_state_destroy(t_state *object);
t_state		*t_julia_state_create(t_mlx_instance mlx_instance, char *fragment);

#endif
