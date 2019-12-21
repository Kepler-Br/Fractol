#include "shader.h"
#include "tools.h"
#include <OpenGL/gl.h>
#include "libft.h"

static void printError(GLint shaderId, GLenum type)
{
    GLint length;
    char *log;

    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
    if (length == 0)
        return;
    log = malloc(length);
    glGetShaderInfoLog(shaderId, length, &length, log);
    if(type == GL_FRAGMENT_SHADER)
        printf("Error fragment shader compilation:\n%s\n", log);
    else if (type == GL_VERTEX_SHADER)
        printf("Error vertex shader compilation:\n%s\n", log);
    else if (type == GL_LINK_STATUS)
        printf("Error linking shader compilation:\n%s\n", log);
    free(log);
}


static void loadShader(char *fragmentPath, t_shader *shader, GLenum type)
{
    const char *source = read_file(fragmentPath);
    GLint size;
    GLint success;
    GLuint shaderId;

    if(source == NULL)
    {
        printf("Shader loading error\n");
        exit(0);
    }
    size = ft_strlen(source);
    printf("DELETEME: Loading shader %s\n", fragmentPath);
    shaderId = glCreateShader(type);
    if (type == GL_VERTEX_SHADER)
        shader->vertexShader = shaderId;
    else if(type == GL_FRAGMENT_SHADER)
        shader->fragmentShader = shaderId;
    glShaderSource(shaderId, 1, &source, &size);

    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    printError(shaderId, type);

    if (success == GL_FALSE)
        exit(0);
    else
        glAttachShader(shader->shaderProgram, shaderId);
}

t_shader createShader(char *vertexPath, char *fragmentPath)
{
    t_shader shader;
    GLint isLinked;

    shader.shaderProgram = glCreateProgram();

    loadShader(vertexPath, &shader, GL_VERTEX_SHADER);
    loadShader(fragmentPath, &shader, GL_FRAGMENT_SHADER);

    glLinkProgram(shader.shaderProgram);
    glGetProgramiv(shader.shaderProgram, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        printError(shader.shaderProgram, GL_LINK_STATUS);
        exit(0);
    }
    return (shader);
}

void destroyShader(t_shader shader)
{
    glUseProgram(0);
    glDetachShader(shader.shaderProgram, shader.fragmentShader);
    glDetachShader(shader.shaderProgram, shader.vertexShader);
    glDeleteProgram(shader.shaderProgram);
    glDeleteShader(shader.vertexShader);
    glDeleteShader(shader.fragmentShader);
}