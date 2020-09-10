#ifndef SHADER_H
#define SHADER_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>

typedef struct s_shader {
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
} t_shader;

t_shader create_shader(char *vertex_path, char *fragment_path);
void destroy_shader(t_shader shader);

#endif //FRACTOL_RELOADED_SHADER_H
