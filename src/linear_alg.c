#include "linear_alg.h"
#include <math.h>

float	float3_length(const cl_float3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

cl_float3 float3_normalize(const cl_float3 vec)
{
	const float len = float3_length(vec);
	
	return ((cl_float3){vec.x / len,
						vec.y / len,
						vec.z / len});
}

cl_float3 float3_cross(const cl_float3 a, const cl_float3 b)
{
	return ((cl_float3){
						a.y * b.z - a.z * b.y,
						a.z * b.x - a.x * b.z,
						a.x * b.y - a.y * b.x
	});
}

float	float3_dot(const cl_float3 x, const cl_float3 y)
{
	return (x.x * y.x + x.y * y.y + x.z * y.z);
}

cl_float16 look_at(const cl_float3 eye, const cl_float3 center, const cl_float3 up)
{
	cl_float3	u;
	cl_float3	f;
	cl_float3	s;
	cl_float3	u2;

	u = float3_normalize(up);
	f = float3_normalize((cl_float3){center.x - eye.x, center.y - eye.y,
								center.z - eye.z});
	s = float3_normalize(float3_cross(f, u));
	u2 = float3_cross(s, f);
	return ((cl_float16){s.x, s.y, s.z, -float3_dot(s, eye),
					 u2.x, u2.y, u2.z, -float3_dot(u2, eye),
					 -f.x, -f.y, -f.z, float3_dot(f, eye),
					 0.0f, 0.0f, 0.0f, 1.0f});
}

cl_float16	mat4_mat4_mul(const cl_float16 *a, const cl_float16 *b)
{
	cl_float16 r;

	r.s0 = a->s0 * b->s0 + a->s1 * b->s4 + a->s2 * b->s8 + a->s3 * b->sc;
	r.s1 = a->s0 * b->s1 + a->s1 * b->s5 + a->s2 * b->s9 + a->s3 * b->sd;
	r.s2 = a->s0 * b->s2 + a->s1 * b->s6 + a->s2 * b->sa + a->s3 * b->se;
	r.s3 = a->s0 * b->s3 + a->s1 * b->s7 + a->s2 * b->sb + a->s3 * b->sf;
	r.s4 = a->s4 * b->s0 + a->s5 * b->s4 + a->s6 * b->s8 + a->s7 * b->sc;
	r.s5 = a->s4 * b->s1 + a->s5 * b->s5 + a->s6 * b->s9 + a->s7 * b->sd;
	r.s6 = a->s4 * b->s2 + a->s5 * b->s6 + a->s6 * b->sa + a->s7 * b->se;
	r.s7 = a->s4 * b->s3 + a->s5 * b->s7 + a->s6 * b->sb + a->s7 * b->sf;
	r.s8 = a->s8 * b->s0 + a->s9 * b->s4 + a->sa * b->s8 + a->sb * b->sc;
	r.s9 = a->s8 * b->s1 + a->s9 * b->s5 + a->sa * b->s9 + a->sb * b->sd;
	r.sa = a->s8 * b->s2 + a->s9 * b->s6 + a->sa * b->sa + a->sb * b->se;
	r.sb = a->s8 * b->s3 + a->s9 * b->s7 + a->sa * b->sb + a->sb * b->sf;
	r.sc = a->sc * b->s0 + a->sd * b->s4 + a->se * b->s8 + a->sf * b->sc;
	r.sd = a->sc * b->s1 + a->sd * b->s5 + a->se * b->s9 + a->sf * b->sd;
	r.se = a->sc * b->s2 + a->sd * b->s6 + a->se * b->sa + a->sf * b->se;
	r.sf = a->sc * b->s3 + a->sd * b->s7 + a->se * b->sb + a->sf * b->sf;
	return (r);
}

cl_float16	orthographic(const cl_float4 bounds, const float near, const float far)
{
	return ((cl_float16){2.0f / (bounds.x - bounds.y), 0.0f, 0.0f, 0.0f,
						 0.0f, 2.0f / (bounds.z - bounds.w), 0.0f, 0.0f,
						 0.0f, 0.0f, -2.0f / (near - far), 0.0f,
						 -(bounds.x + bounds.y) / (bounds.x - bounds.y),
						 -(bounds.z + bounds.w) / (bounds.z - bounds.w),
						 -(far + near) / (far - near), 1.0f});
}

cl_float16	perspective(const cl_float aspect, const float fov, const float near, const float far)
{
	const float tan_half_fov = tanf(fov/2.0f);
	return ((cl_float16){1.0f / (aspect*tan_half_fov), 0.0f, 0.0f, 0.0f,
						 0.0f, 1.0f/ tan_half_fov, 0.0f, 0.0f,
						 0.0f, 0.0f, -(far+near)/(far-near), -1.0f,
						 0.0f, 0.0f, -(2.0f*far*near)/(far-near), 0.0f});
}



float float16_det(cl_float16 m)
{
//	float plus = (m.s0 * m.s5 * m.sa*  m.sf) + (m.s1 * m.s6 * m.sb * m.sc) + (m.s2 * m.s7 * m.s8 * m.sd) + (m.s3 * m.s4 * m.s9 * m.se);
//	float minus = (m.s2 * m.s5 * m.s8 * m.sf) + (m.s1 * m.s4 * m.sb * m.se) + (m.s0 * m.s7 * m.sa * m.sd) + (m.s3 * m.s6 * m.s9 * m.sc);
//	plus = (m.s0 * m.s5 * m.sa*  m.sf)
//	return (plus - minus);
	return (m.s3 * m.s6 * m.s9 * m.sc - m.s2 * m.s7 * m.s9 * m.sc-
			m.s3 * m.s5 * m.sa * m.sc+m.s1 * m.s7 * m.sa * m.sc+
			m.s2 * m.s5 * m.sb * m.sc-m.s1 * m.s6 * m.sb * m.sc-
			m.s3 * m.s6 * m.s8 * m.sd+m.s2 * m.s7 * m.s8 * m.sd+
			m.s3 * m.s4 * m.sa * m.sd-m.s0 * m.s7 * m.sa * m.sd-
			m.s2 * m.s4 * m.sb * m.sd+m.s0 * m.s6 * m.sb * m.sd+
			m.s3 * m.s5 * m.s8 * m.se-m.s1 * m.s7 * m.s8 * m.se-
			m.s3 * m.s4 * m.s9 * m.se+m.s0 * m.s7 * m.s9 * m.se+
			m.s1 * m.s4 * m.sb * m.se-m.s0 * m.s5 * m.sb * m.se-
			m.s2 * m.s5 * m.s8 * m.sf+m.s1 * m.s6 * m.s8 * m.sf+
			m.s2 * m.s4 * m.s9 * m.sf-m.s0 * m.s6 * m.s9 * m.sf-
			m.s1 * m.s4 * m.sa * m.sf+m.s0 * m.s5 * m.sa * m.sf);
}

cl_float16 float16_inverse(cl_float16 m)
{
	cl_float16 inv;
	cl_float det;
	int i;
	inv.s[0] = m.s[5]  * m.s[10] * m.s[15] -
			 m.s[5]  * m.s[11] * m.s[14] -
			 m.s[9]  * m.s[6]  * m.s[15] +
			 m.s[9]  * m.s[7]  * m.s[14] +
			 m.s[13] * m.s[6]  * m.s[11] -
			 m.s[13] * m.s[7]  * m.s[10];

	inv.s[4] = -m.s[4]  * m.s[10] * m.s[15] +
			 m.s[4]  * m.s[11] * m.s[14] +
			 m.s[8]  * m.s[6]  * m.s[15] -
			 m.s[8]  * m.s[7]  * m.s[14] -
			 m.s[12] * m.s[6]  * m.s[11] +
			 m.s[12] * m.s[7]  * m.s[10];

	inv.s[8] = m.s[4]  * m.s[9] * m.s[15] -
			 m.s[4]  * m.s[11] * m.s[13] -
			 m.s[8]  * m.s[5] * m.s[15] +
			 m.s[8]  * m.s[7] * m.s[13] +
			 m.s[12] * m.s[5] * m.s[11] -
			 m.s[12] * m.s[7] * m.s[9];

	inv.s[12] = -m.s[4]  * m.s[9] * m.s[14] +
			  m.s[4]  * m.s[10] * m.s[13] +
			  m.s[8]  * m.s[5] * m.s[14] -
			  m.s[8]  * m.s[6] * m.s[13] -
			  m.s[12] * m.s[5] * m.s[10] +
			  m.s[12] * m.s[6] * m.s[9];

	inv.s[1] = -m.s[1]  * m.s[10] * m.s[15] +
			 m.s[1]  * m.s[11] * m.s[14] +
			 m.s[9]  * m.s[2] * m.s[15] -
			 m.s[9]  * m.s[3] * m.s[14] -
			 m.s[13] * m.s[2] * m.s[11] +
			 m.s[13] * m.s[3] * m.s[10];

	inv.s[5] = m.s[0]  * m.s[10] * m.s[15] -
			 m.s[0]  * m.s[11] * m.s[14] -
			 m.s[8]  * m.s[2] * m.s[15] +
			 m.s[8]  * m.s[3] * m.s[14] +
			 m.s[12] * m.s[2] * m.s[11] -
			 m.s[12] * m.s[3] * m.s[10];

	inv.s[9] = -m.s[0]  * m.s[9] * m.s[15] +
			 m.s[0]  * m.s[11] * m.s[13] +
			 m.s[8]  * m.s[1] * m.s[15] -
			 m.s[8]  * m.s[3] * m.s[13] -
			 m.s[12] * m.s[1] * m.s[11] +
			 m.s[12] * m.s[3] * m.s[9];

	inv.s[13] = m.s[0]  * m.s[9] * m.s[14] -
			  m.s[0]  * m.s[10] * m.s[13] -
			  m.s[8]  * m.s[1] * m.s[14] +
			  m.s[8]  * m.s[2] * m.s[13] +
			  m.s[12] * m.s[1] * m.s[10] -
			  m.s[12] * m.s[2] * m.s[9];

	inv.s[2] = m.s[1]  * m.s[6] * m.s[15] -
			 m.s[1]  * m.s[7] * m.s[14] -
			 m.s[5]  * m.s[2] * m.s[15] +
			 m.s[5]  * m.s[3] * m.s[14] +
			 m.s[13] * m.s[2] * m.s[7] -
			 m.s[13] * m.s[3] * m.s[6];

	inv.s[6] = -m.s[0]  * m.s[6] * m.s[15] +
			 m.s[0]  * m.s[7] * m.s[14] +
			 m.s[4]  * m.s[2] * m.s[15] -
			 m.s[4]  * m.s[3] * m.s[14] -
			 m.s[12] * m.s[2] * m.s[7] +
			 m.s[12] * m.s[3] * m.s[6];

	inv.s[10] = m.s[0]  * m.s[5] * m.s[15] -
			  m.s[0]  * m.s[7] * m.s[13] -
			  m.s[4]  * m.s[1] * m.s[15] +
			  m.s[4]  * m.s[3] * m.s[13] +
			  m.s[12] * m.s[1] * m.s[7] -
			  m.s[12] * m.s[3] * m.s[5];

	inv.s[14] = -m.s[0]  * m.s[5] * m.s[14] +
			  m.s[0]  * m.s[6] * m.s[13] +
			  m.s[4]  * m.s[1] * m.s[14] -
			  m.s[4]  * m.s[2] * m.s[13] -
			  m.s[12] * m.s[1] * m.s[6] +
			  m.s[12] * m.s[2] * m.s[5];

	inv.s[3] = -m.s[1] * m.s[6] * m.s[11] +
			 m.s[1] * m.s[7] * m.s[10] +
			 m.s[5] * m.s[2] * m.s[11] -
			 m.s[5] * m.s[3] * m.s[10] -
			 m.s[9] * m.s[2] * m.s[7] +
			 m.s[9] * m.s[3] * m.s[6];

	inv.s[7] = m.s[0] * m.s[6] * m.s[11] -
			 m.s[0] * m.s[7] * m.s[10] -
			 m.s[4] * m.s[2] * m.s[11] +
			 m.s[4] * m.s[3] * m.s[10] +
			 m.s[8] * m.s[2] * m.s[7] -
			 m.s[8] * m.s[3] * m.s[6];

	inv.s[11] = -m.s[0] * m.s[5] * m.s[11] +
			  m.s[0] * m.s[7] * m.s[9] +
			  m.s[4] * m.s[1] * m.s[11] -
			  m.s[4] * m.s[3] * m.s[9] -
			  m.s[8] * m.s[1] * m.s[7] +
			  m.s[8] * m.s[3] * m.s[5];

	inv.s[15] = m.s[0] * m.s[5] * m.s[10] -
			  m.s[0] * m.s[6] * m.s[9] -
			  m.s[4] * m.s[1] * m.s[10] +
			  m.s[4] * m.s[2] * m.s[9] +
			  m.s[8] * m.s[1] * m.s[6] -
			  m.s[8] * m.s[2] * m.s[5];

	det = m.s[0] * inv.s[0] + m.s[1] * inv.s[4] + m.s[2] * inv.s[8] + m.s[3] * inv.s[12];
	if (det == 0)
	{
		write(1, "FFFFFFFFFFUUUUUUUUU\n", 20);
		return (m);
	}
	det = 1.0f / det;
	i = 0;
	while (i < 16)
	{
		inv.s[i] = inv.s[i] * det;
		i++;
	}
	return (inv);
}
