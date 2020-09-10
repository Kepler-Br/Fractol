/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarch_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:38:36 by nsena             #+#    #+#             */
/*   Updated: 2020/09/10 18:38:37 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "raymarch_state.h"
#include "mlx_keys.h"
#include "linear_alg.h"
#include <math.h>
#include "math_tools.h"
#include <stdlib.h>
#include <OpenGL/gl.h>
#include "libft.h"

static void				loop(struct s_state *this)
{
	t_raymarch_struct *this_str;

	this_str = (t_raymarch_struct *)this->instance_struct;
	this_str->mandelbulb_power = lerpf(this_str->mandelbulb_power,
									this_str->target_mandelbulb_power, 0.1f);
	this_str->camera_radius = lerpf(this_str->camera_radius,
								this_str->target_camera_radius, 0.1f);
	this_str->rotation = lerpvec3(this_str->rotation,
							this_str->target_rotation, 0.5f);
}

static void				render_gl_stuff(t_raymarch_struct *this_str,
							t_vec3 *camera_position, t_state *this,
							t_mat4 *inverse_proj_view)
{
	glBindVertexArrayAPPLE(this_str->vertex_buffer.vao);
	glUseProgram(this_str->shader.shaderProgram);
	glUniform2f(this_str->iresolution_location,
				(GLfloat)this->mlx_instance.window_geometry.x,
				(GLfloat)this->mlx_instance.window_geometry.y);
	glUniformMatrix4fv(this_str->inversed_pv_location, 1, GL_FALSE,
					inverse_proj_view->s);
	glUniform3fv(this_str->camera_position_location, 1, camera_position->s);
	glUniform1f(this_str->fractal_parameter_location,
				this_str->mandelbulb_power);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

static void				render(struct s_state *this)
{
	t_raymarch_struct	*this_str;
	t_vec3				camera_position;
	t_mat4				view;
	t_mat4				proj;
	t_mat4				inverse_proj_view;

	this_str = (t_raymarch_struct *)this->instance_struct;
	proj = orthographic(
			(t_vec4){500.0f, -500.0f, 500.0f, -500.0f}, 100.0f, 301.0f);
	camera_position = (t_vec3){
			this_str->camera_radius * cosf(this_str->rotation.x) *
			sinf(this_str->rotation.y),
			this_str->camera_radius * sinf(this_str->rotation.x) *
			sinf(this_str->rotation.y),
			this_str->camera_radius * cosf(this_str->rotation.y)};
	view = look_at(camera_position, (t_vec3){0.0f, 0.0f, 0.0f},
				(t_vec3){0.0f, 0.0f, 1.0f});
	inverse_proj_view = float16_inverse(mat4_mat4_mul(&proj, &view));
	render_gl_stuff(this_str, &camera_position, this, &inverse_proj_view);
}

static void				on_key(int keyid, struct s_state *this)
{
	t_raymarch_struct	*this_str;

	this_str = (t_raymarch_struct*)this->instance_struct;
	if (keyid == MLX_K_ESC)
	{
		this->on_close(this);
		exit(0);
	}
	if (keyid == MLX_K_Q)
		this_str->target_mandelbulb_power += 0.1f;
	if (keyid == MLX_K_E)
		this_str->target_mandelbulb_power -= 0.1f;
}

static void				on_mouse_move(t_ivec2 position, t_ivec2 delta,
							struct s_state *this)
{
	t_raymarch_struct *this_str;

	this_str = (t_raymarch_struct*)this->instance_struct;
	if (this_str->lmb_pressed)
	{
		this_str->target_rotation.x -= delta.x / 500.0f;
		this_str->target_rotation.y -= delta.y / 500.0f;
	}
}

static void				on_mouse_down(int keyid, t_ivec2 position,
							struct s_state *this)
{
	t_raymarch_struct *this_str;

	this_str = (t_raymarch_struct*)this->instance_struct;
	if (keyid == MLX_M_SCROLL_UP)
		this_str->target_camera_radius += 0.1f;
	if (keyid == MLX_M_SCROLL_DOWN)
		this_str->target_camera_radius -= 0.1f;
	if (keyid == MLX_M_LEFT)
		this_str->lmb_pressed = GL_TRUE;
}

static void				on_mouse_up(int keyid, t_ivec2 position,
						struct s_state *this)
{
	t_raymarch_struct *this_str;

	this_str = (t_raymarch_struct*)this->instance_struct;
	if (keyid == MLX_M_LEFT)
		this_str->lmb_pressed = GL_FALSE;
}

static void				on_close(struct s_state *this)
{
	t_raymarch_state_destroy(this);
}

void					t_raymarch_state_destroy(t_state *object)
{
	const t_raymarch_struct *this_str;

	this_str = (t_raymarch_struct *)object->instance_struct;
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
	t_vertex_buffer	buffer;
	const uint32_t	position_attr_index = 0;
	const uint32_t	size_in_bytes = (4 * 3) * sizeof(GLfloat);

	glGenBuffers(count_vbos, &buffer.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);
	glBufferData(GL_ARRAY_BUFFER, size_in_bytes, square, GL_STATIC_DRAW);
	glGenVertexArraysAPPLE(1, &buffer.vao);
	glBindVertexArrayAPPLE(buffer.vao);
	glVertexAttribPointer(position_attr_index, 3, GL_FLOAT, GL_FALSE, 0,
						NULL);
	glEnableVertexAttribArray(position_attr_index);
	glBindVertexArrayAPPLE(0);
	return (buffer);
}

static void				init_raymarch(t_raymarch_struct *raymarch_struct,
						char *fragment)
{
	raymarch_struct->rotation = (t_vec3){0.0f, 0.0f, 0.0f};
	raymarch_struct->target_rotation = (t_vec3){0.0f, 0.0f, 0.0f};
	raymarch_struct->camera_radius = 1.0f;
	raymarch_struct->target_camera_radius = 1.0f;
	raymarch_struct->mandelbulb_power = 0.0f;
	raymarch_struct->target_mandelbulb_power = 1.0f;
	raymarch_struct->shader = create_shader("./programs/vert.glsl", fragment);
	raymarch_struct->lmb_pressed = GL_FALSE;
	raymarch_struct->vertex_buffer = create_vertex_buffer();
	raymarch_struct->iresolution_location = glGetUniformLocation(
			raymarch_struct->shader.shaderProgram, "iResolution");
	raymarch_struct->inversed_pv_location = glGetUniformLocation(
			raymarch_struct->shader.shaderProgram, "inversedProjectionView");
	raymarch_struct->camera_position_location = glGetUniformLocation(
			raymarch_struct->shader.shaderProgram, "cameraPosition");
	raymarch_struct->fractal_parameter_location = glGetUniformLocation(
			raymarch_struct->shader.shaderProgram, "fractalParameter");
}

t_state					*t_raymarch_state_create(t_mlx_instance mlx_instance,
									char *fragment)
{
	t_state				*object;
	t_raymarch_struct	*raymarch_struct;

	ft_assert((object = (t_state*)malloc(sizeof(t_state))) != NULL,
			"t_raymarch_state_create: cannot allocate t_state.");
	ft_assert((raymarch_struct =
			(t_raymarch_struct*)malloc(sizeof(t_raymarch_struct))) != NULL,
			"t_raymarch_state_create: cannot allocate t_state.");
	init_raymarch(raymarch_struct, fragment);
	object->mlx_instance = mlx_instance;
	object->instance_struct = raymarch_struct;
	object->on_mouse_move = &on_mouse_move;
	object->on_mouse_up = &on_mouse_up;
	object->on_mouse_down = &on_mouse_down;
	object->on_close = &on_close;
	object->on_key = &on_key;
	object->render = &render;
	object->loop = &loop;
	return (object);
}
