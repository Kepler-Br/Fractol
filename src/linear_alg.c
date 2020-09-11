/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:03:47 by nsena             #+#    #+#             */
/*   Updated: 2020/09/10 18:03:49 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_alg.h"
#include <math.h>

float		float3_length(const t_vec3 vec)
{
	return (sqrtf(vec.s[0] * vec.s[0] + vec.s[1] * vec.s[1] + vec.s[2] * vec.s[2]));
}

t_vec3		float3_normalize(const t_vec3 vec)
{
	const float	len = float3_length(vec);

	return ((t_vec3){vec.s[0] / len,
						vec.s[1] / len,
						vec.s[2] / len});
}

t_vec3		float3_cross(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){
						a.s[1] * b.s[2] - a.s[2] * b.s[1],
						a.s[2] * b.s[0] - a.s[0] * b.s[2],
						a.s[0] * b.s[1] - a.s[1] * b.s[0]
	});
}

float		float3_dot(const t_vec3 x, const t_vec3 y)
{
	return (x.s[0] * y.s[0] + x.s[1] * y.s[1] + x.s[2] * y.s[2]);
}

t_mat4		look_at(const t_vec3 eye, const t_vec3 center, const t_vec3 up)
{
	t_vec3	u;
	t_vec3	f;
	t_vec3	s;
	t_vec3	u2;

	u = float3_normalize(up);
	f = float3_normalize((t_vec3){center.s[0] - eye.s[0], center.s[1] -
							eye.s[1], center.s[2] - eye.s[2]});
	s = float3_normalize(float3_cross(f, u));
	u2 = float3_cross(s, f);
	return ((t_mat4){s.s[0], s.s[1], s.s[2], -float3_dot(s, eye),
					u2.s[0], u2.s[1], u2.s[2], -float3_dot(u2, eye),
					-f.s[0], -f.s[1], -f.s[2], float3_dot(f, eye),
					0.0f, 0.0f, 0.0f, 1.0f});
}



t_mat4		orthographic(const t_vec4 bounds, const float near, const float far)
{
	return ((t_mat4){2.0f / (bounds.s[0] - bounds.s[1]), 0.0f, 0.0f, 0.0f,
					0.0f, 2.0f / (bounds.s[2] - bounds.s[3]), 0.0f, 0.0f,
					0.0f, 0.0f, -2.0f / (near - far), 0.0f,
					-(bounds.s[0] + bounds.s[1]) / (bounds.s[0] - bounds.s[1]),
					-(bounds.s[2] + bounds.s[3]) / (bounds.s[2] - bounds.s[3]),
					-(far + near) / (far - near), 1.0f});
}

t_mat4		perspective(const GLfloat aspect, const float fov, const float near,
					const float far)
{
	const float	tan_half_fov = tanf(fov / 2.0f);

	return ((t_mat4){1.0f / (aspect * tan_half_fov), 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f / tan_half_fov, 0.0f, 0.0f,
						0.0f, 0.0f, -(far + near) / (far - near), -1.0f,
						0.0f, 0.0f, -(2.0f * far * near) / (far - near), 0.0f});
}
