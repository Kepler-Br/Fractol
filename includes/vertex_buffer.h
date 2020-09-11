/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_buffer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:21:30 by nsena             #+#    #+#             */
/*   Updated: 2020/09/11 13:21:31 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_BUFFER_H
# define VERTEX_BUFFER_H

# define GL_SILENCE_DEPRECATION
# include <OpenGL/gl.h>

typedef struct	s_vertex_buffer
{
	GLuint vbo;
	GLuint vao;
}				t_vertex_buffer;

#endif
