/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:26:32 by nsena             #+#    #+#             */
/*   Updated: 2020/09/10 17:26:33 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GL_SILENCE_DEPRECATION
#include <unistd.h>
#include "julia_state.h"
#include "mlx_keys.h"
#include "linear_alg.h"
#include "math_tools.h"
#include <stdlib.h>
#include "libft.h"
#include <OpenGL/gl.h>

static void				loop(struct s_state *this)
{
	t_julia_struct	*this_str;

	this_str = (t_julia_struct *)this->instance_struct;
	this_str->zoom = lerpf(this_str->zoom, this_str->target_zoom, 0.1f);
	this_str->camera_position = lerpvec2(this_str->camera_position,
									this_str->target_camera_position, 0.1f);
	this_str->palette_shift = lerpf(this_str->palette_shift,
									this_str->target_palette_shift, 0.1f);
	if (this_str->target_zoom < -1.5f)
		this_str->target_zoom = -1.5f;
	if (this_str->target_zoom > 1.3f)
		this_str->target_zoom = 1.3f;
}

static void				render(struct s_state *this)
{
	const t_julia_struct	*this_str = (t_julia_struct *)this->instance_struct;

	glBindVertexArrayAPPLE(this_str->vertex_buffer.vao);
	glUseProgram(this_str->shader.shaderProgram);
	glUniform2f(this_str->iresolution_location,
		(GLfloat)this->mlx_instance.window_geometry.x,
		(GLfloat)this->mlx_instance.window_geometry.y);
	glUniform2fv(this_str->camera_position_location, 1,
				this_str->camera_position.s);
	glUniform1f(this_str->zoom_location, this_str->zoom);
	glUniform3fv(this_str->col_pal_location, 4, this_str->palette->s);
	glUniform2fv(this_str->julia_parameters_location, 1,
				this_str->julia_parameters.s);
	glUniform1f(this_str->palette_shift_location, this_str->palette_shift);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

static void				on_key3(t_julia_struct *str, int keyid)
{
	if (keyid == MLX_K_4)
	{
		str->palette[0] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[1] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[2] = (t_vec3){1.0, 1.0, 0.5};
		str->palette[3] = (t_vec3){0.80, 0.90, 0.30};
	}
	if (keyid == MLX_K_5)
	{
		str->palette[0] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[1] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[2] = (t_vec3){1.0, 0.7, 0.4};
		str->palette[3] = (t_vec3){0.00, 0.15, 0.20};
	}
	if (keyid == MLX_K_6)
	{
		str->palette[0] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[1] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[2] = (t_vec3){2.0, 1.0, 0.0};
		str->palette[3] = (t_vec3){0.50, 0.20, 0.25};
	}
}

static void				on_key2(t_julia_struct *str, int keyid)
{
	if (keyid == MLX_K_1)
	{
		str->palette[0] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[1] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[2] = (t_vec3){1.0, 1.0, 1.0};
		str->palette[3] = (t_vec3){0.00, 0.33, 0.67};
	}
	if (keyid == MLX_K_2)
	{
		str->palette[0] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[1] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[2] = (t_vec3){1.0, 1.0, 1.0};
		str->palette[3] = (t_vec3){0.00, 0.10, 0.20};
	}
	if (keyid == MLX_K_3)
	{
		str->palette[0] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[1] = (t_vec3){0.5, 0.5, 0.5};
		str->palette[2] = (t_vec3){1.0, 1.0, 1.0};
		str->palette[3] = (t_vec3){0.30, 0.20, 0.20};
	}
	on_key3(str, keyid);
}

static void				on_key(int keyid, struct s_state *this)
{
	t_julia_struct	*this_str;

	this_str = (t_julia_struct*)this->instance_struct;
	if (keyid == MLX_K_ESC)
	{
		this->on_close(this);
		exit(0);
	}
	on_key2(this_str, keyid);
	if (keyid == MLX_K_7)
	{
		this_str->palette[0] = (t_vec3){0.8, 0.5, 0.4};
		this_str->palette[1] = (t_vec3){0.2, 0.4, 0.2};
		this_str->palette[2] = (t_vec3){2.0, 1.0, 1.0};
		this_str->palette[3] = (t_vec3){0.00, 0.25, 0.25};
	}
	if (keyid == MLX_K_Q)
		this_str->target_palette_shift += 0.1f;
	if (keyid == MLX_K_E)
		this_str->target_palette_shift -= 0.1f;
	if (keyid == MLX_K_W)
	{
		this_str->target_zoom = 1.0f;
		this_str->target_camera_position = (t_vec2){0.0f, 0.0f};
	}
}

static void				on_mouse_move(t_ivec2 position, t_ivec2 delta,
							struct s_state *this)
{
	t_julia_struct	*this_str;

	this_str = (t_julia_struct*)this->instance_struct;
	if (!this_str->lmb_pressed && !this_str->rmb_pressed)
	{
		this_str->julia_parameters.x -= delta.x / 500.0f;
		this_str->julia_parameters.y -= delta.y / 500.0f;
	}
	if (this_str->lmb_pressed)
	{
		this_str->target_camera_position.x -= (float)delta.x / (1.0f -
				this_str->target_zoom + 0.1f) / (200000.0f * (1.0f -
						this_str->target_zoom + 0.1f));
		this_str->target_camera_position.y += (float)delta.y / (1.0f -
				this_str->target_zoom + 0.1f) / (200000.0f * (1.0f -
						this_str->target_zoom + 0.1f));
	}
}

static void				on_mouse_down(int keyid, t_ivec2 position,
							struct s_state *this)
{
	t_julia_struct	*this_str;

	this_str = (t_julia_struct*)this->instance_struct;
	if (keyid == MLX_M_SCROLL_UP)
		this_str->target_zoom += 0.01f;
	if (keyid == MLX_M_SCROLL_DOWN)
		this_str->target_zoom -= 0.01f;
	if (keyid == MLX_M_LEFT)
		this_str->lmb_pressed = GL_TRUE;
	if (keyid == MLX_M_RIGHT)
		this_str->rmb_pressed = GL_TRUE;
}

static void				on_mouse_up(int keyid, t_ivec2 position,
						struct s_state *this)
{
	t_julia_struct	*this_str;

	this_str = (t_julia_struct*)this->instance_struct;
	if (keyid == MLX_M_LEFT)
		this_str->lmb_pressed = GL_FALSE;
	if (keyid == MLX_M_RIGHT)
		this_str->rmb_pressed = GL_FALSE;
}

static void				on_close(struct s_state *this)
{
	t_julia_state_destroy(this);
}

void					t_julia_state_destroy(t_state *object)
{
	const t_julia_struct	*this_str;

	this_str = (t_julia_struct *)object->instance_struct;
	glDeleteBuffers(1, &this_str->vertex_buffer.vbo);
	glDeleteVertexArraysAPPLE(1, &this_str->vertex_buffer.vao);
	destroy_shader(this_str->shader);
	free(object->instance_struct);
	free(object);
}

static t_vertex_buffer	create_vertex_buffer(void)
{
	const GLfloat	square[4][3] = {
			{ -1.0, 1.0, 0.0 },
			{ 1.0, 1.0, 0.0 },
			{ 1.0, -1.0, 0.0 },
			{ -1.0, -1.0, 0.0 },
	};
	const uint32_t	count_vbos = 1;
	const uint32_t	position_attrib_index = 0;
	const uint32_t	size_in_bytes = (4 * 3) * sizeof(GLfloat);
	t_vertex_buffer	buffer;

	glGenBuffers(count_vbos, &buffer.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);
	glBufferData(GL_ARRAY_BUFFER, size_in_bytes, square, GL_STATIC_DRAW);
	glGenVertexArraysAPPLE(1, &buffer.vao);
	glBindVertexArrayAPPLE(buffer.vao);
	glVertexAttribPointer(position_attrib_index, 3, GL_FLOAT, GL_FALSE,
						0, NULL);
	glEnableVertexAttribArray(position_attrib_index);
	glBindVertexArrayAPPLE(0);
	return (buffer);
}

static void				setup_julia_variables(t_julia_struct *js,
									char *fragment)
{
	const t_shader	shader = create_shader("./programs/vert.glsl", fragment);
	const GLuint	shader_p = shader.shaderProgram;

	js->camera_position = (t_vec2){10.0f, 10.0f};
	js->target_camera_position = (t_vec2){0.0f, 0.0f};
	js->zoom = 0.0f;
	js->target_zoom = 1.0f;
	js->shader = shader;
	js->lmb_pressed = GL_FALSE;
	js->vertex_buffer = create_vertex_buffer();
	js->iresolution_location = glGetUniformLocation(shader_p, "iResolution");
	js->camera_position_location = glGetUniformLocation(shader_p,
		"cameraPosition");
	js->zoom_location = glGetUniformLocation(shader_p, "zoom");
	js->palette_shift_location = glGetUniformLocation(shader_p, "paletteShift");
	js->col_pal_location = glGetUniformLocation(shader_p, "colPal");
	js->julia_parameters_location = glGetUniformLocation(shader_p,
		"juliaParameters");
	js->palette[0] = (t_vec3){0.5, 0.5, 0.5};
	js->palette[1] = (t_vec3){0.5, 0.5, 0.5};
	js->palette[2] = (t_vec3){1.0, 1.0, 1.0};
	js->palette[3] = (t_vec3){0.00, 0.10, 0.20};
	js->julia_parameters = (t_vec2){-0.123, 0.745};
	js->palette_shift = 0.0f;
	js->target_palette_shift = 0.0f;
}

t_state					*t_julia_state_create(t_mlx_instance mlx_instance,
								char *fragment)
{
	t_state			*object;
	t_julia_struct	*julia_struct;

	ft_assert((object = (t_state*)malloc(sizeof(t_state))) != NULL,
		"t_julia_state_create: cannot allocate s_state.\n");
	ft_assert((julia_struct = (t_julia_struct*)
			malloc(sizeof(t_julia_struct))) != NULL,
		"t_julia_state_create: cannot allocate s_raymarch_struct.\n");
	setup_julia_variables(julia_struct, fragment);
	object->mlx_instance = mlx_instance;
	object->instance_struct = julia_struct;
	object->on_mouse_move = &on_mouse_move;
	object->on_mouse_up = &on_mouse_up;
	object->on_mouse_down = &on_mouse_down;
	object->on_close = &on_close;
	object->on_key = &on_key;
	object->render = &render;
	object->loop = &loop;
	return (object);
}
