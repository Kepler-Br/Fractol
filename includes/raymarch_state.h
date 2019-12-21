#ifndef RAYMARCH_STATE_H
#define RAYMARCH_STATE_H

#include "state.h"
#include "shader.h"
#include "vertex_buffer.h"

typedef struct	s_raymarch_struct
{
	t_vec3	    		rotation;
    GLfloat             camera_radius;
    GLfloat             target_camera_radius;
    GLfloat             mandelbulb_power;
    GLfloat             target_mandelbulb_power;
    t_shader            shader;
    t_vertex_buffer     vertex_buffer;
}				t_raymarch_struct;

void		t_raymarch_state_destroy(t_state *object);
t_state		*t_raymarch_state_create(t_mlx_instance mlx_instance);

#endif
