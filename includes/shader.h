/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:19:54 by nsena             #+#    #+#             */
/*   Updated: 2020/09/11 13:19:55 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# define GL_SILENCE_DEPRECATION
# include <OpenGL/gl.h>

typedef struct	s_shader
{
	GLuint shader_program;
	GLuint vertex_shader;
	GLuint fragment_shader;
}				t_shader;

t_shader		create_shader(char *vertex_path, char *fragment_path);
void			destroy_shader(t_shader shader);

#endif
