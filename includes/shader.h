#ifndef SHADER_H
#define SHADER_H

#include <OpenGL/gl.h>

typedef struct s_shader {
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
} t_shader;

t_shader createShader(char *vertexPath, char *fragmentPath);
void destroyShader(t_shader shader);

#endif //FRACTOL_RELOADED_SHADER_H
