/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_alg.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:13:39 by nsena             #+#    #+#             */
/*   Updated: 2020/09/11 13:13:40 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEAR_ALG_H
# define LINEAR_ALG_H

# define GL_SILENCE_DEPRECATION
# include <OpenGL/gl.h>

typedef union	u_ivec2
{
	GLint s[2];
}				t_ivec2;

typedef union	u_ivec3
{
	GLint s[3];
}				t_ivec3;

typedef union	u_vec2
{
	GLfloat s[2];
}				t_vec2;

typedef union	u_vec3
{
	GLfloat s[3];
}				t_vec3;

typedef union	u_vec4
{
	GLfloat s[4];
}				t_vec4;

typedef union	u_mat4
{
	GLfloat s[16];
}				t_mat4;

float			float3_length(t_vec3 vec);
t_vec3			float3_normalize(t_vec3 vec);
t_vec3			float3_cross(t_vec3 a, t_vec3 b);
t_mat4			look_at(t_vec3 eye, t_vec3 center, t_vec3 up);
t_mat4			mat4_mat4_mul(t_mat4 *a, t_mat4 *b);
t_mat4			orthographic(t_vec4 bounds, float near, float far);
t_mat4			perspective(GLfloat aspect, float fov, float near, float far);
t_mat4			float16_inverse(t_mat4 m);

#endif
