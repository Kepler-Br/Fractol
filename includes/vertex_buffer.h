#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>

typedef struct s_vertex_buffer {
    GLuint vbo;
    GLuint vao;
} t_vertex_buffer;

#endif
