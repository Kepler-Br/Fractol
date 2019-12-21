#ifndef LINEAR_ALG_H
#define LINEAR_ALG_H

#include <OpenGL/gl.h>

typedef union u_ivec2 {
    GLint s[2];
    struct {
        GLint x;
        GLint y;
    };
} t_ivec2;

typedef union u_ivec3 {
    GLint s[3];
    struct {
        GLint x;
        GLint y;
        GLint z;
    };
} t_ivec3;

typedef union u_vec3 {
    GLfloat s[3];
    struct {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };
} t_vec3;

typedef union u_vec4 {
    GLfloat s[4];
    struct {
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat w;
    };
} t_vec4;

typedef union u_mat4 {
    GLfloat s[16];
    struct {
        GLfloat s0;
        GLfloat s1;
        GLfloat s2;
        GLfloat s3;
        GLfloat s4;
        GLfloat s5;
        GLfloat s6;
        GLfloat s7;
        GLfloat s8;
        GLfloat s9;
        GLfloat sa;
        GLfloat sb;
        GLfloat sc;
        GLfloat sd;
        GLfloat se;
        GLfloat sf;
    };
} t_mat4;

float	float3_length(const t_vec3 vec);
t_vec3 float3_normalize(const t_vec3 vec);
t_vec3 float3_cross(const t_vec3 a, const t_vec3 b);
t_mat4 look_at(const t_vec3 eye, const t_vec3 center, const t_vec3 up);
t_mat4	mat4_mat4_mul(const t_mat4 *a, const t_mat4 *b);
t_mat4	orthographic(const t_vec4 bounds, const float near, const float far);
t_mat4	perspective(const GLfloat aspect, const float fov, const float near, const float far);
float float16_det(t_mat4 m);
t_mat4 float16_inverse(t_mat4 m);

#endif
