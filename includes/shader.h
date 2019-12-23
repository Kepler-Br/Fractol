#ifndef SHADER_H
#define SHADER_H

#include <OpenGL/gl.h>

typedef struct s_shader {
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
} t_shader;

t_shader create_shader(char *vertexPath, char *fragmentPath);
void destroy_shader(t_shader shader);

#endif //FRACTOL_RELOADED_SHADER_H
