#ifndef LINEAR_ALG_H
#define LINEAR_ALG_H

#include <OpenCL/cl.h>
#include <OpenGL/gl.h>

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

float	float3_length(const cl_float3 vec);
cl_float3 float3_normalize(const cl_float3 vec);
cl_float3 float3_cross(const cl_float3 a, const cl_float3 b);
cl_float16 look_at(const cl_float3 eye, const cl_float3 center, const cl_float3 up);
cl_float16	mat4_mat4_mul(const cl_float16 *a, const cl_float16 *b);
cl_float16	orthographic(const cl_float4 bounds, const float near, const float far);
cl_float16	perspective(const cl_float aspect, const float fov, const float near, const float far);
float float16_det(cl_float16 m);
cl_float16 float16_inverse(cl_float16 m);

#endif
