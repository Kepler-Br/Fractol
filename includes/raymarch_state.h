/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarch_state.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:19:08 by nsena             #+#    #+#             */
/*   Updated: 2020/09/11 13:19:09 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYMARCH_STATE_H
# define RAYMARCH_STATE_H

# include "state.h"
# include "shader.h"
# include "vertex_buffer.h"

typedef struct	s_raymarch_struct
{
	t_vec3				rotation;
	t_vec3				target_rotation;
	GLfloat				camera_radius;
	GLfloat				target_camera_radius;
	GLfloat				mandelbulb_power;
	GLfloat				target_mandelbulb_power;
	GLboolean			lmb_pressed;
	t_shader			shader;
	t_vertex_buffer		vertex_buffer;
	GLint				iresolution_location;
	GLint				inversed_pv_location;
	GLint				camera_position_location;
	GLint				fractal_parameter_location;
}				t_raymarch_struct;

void			t_raymarch_state_destroy(t_state *object);
t_state			*t_raymarch_state_create(t_mlx_instance mlx_instance,
								char *fragment);

#endif
