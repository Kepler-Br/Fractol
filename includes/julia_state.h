#ifndef JULIA_STATE_H
#define JULIA_STATE_H

#include "state.h"
#include "shader.h"
#include "vertex_buffer.h"
#include "linear_alg.h"

typedef struct	s_julia_struct
{
    t_vec2              camera_position;
    GLfloat             zoom;
    GLfloat             target_zoom;
    GLboolean           lmb_pressed;
    t_shader            shader;
    t_vertex_buffer     vertex_buffer;
    GLint iresolution_location;
    GLint camera_position_location;
}				t_julia_struct;

void		t_julia_state_destroy(t_state *object);
t_state		*t_julia_state_create(t_mlx_instance mlx_instance, char *fragment);

#endif
