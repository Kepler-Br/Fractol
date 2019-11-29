#include <OpenCL/cl.h>

#ifndef LINEAR_ALG_H
#define LINEAR_ALG_H

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
