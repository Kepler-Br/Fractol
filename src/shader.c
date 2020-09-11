/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:29:14 by nsena             #+#    #+#             */
/*   Updated: 2020/09/10 18:29:15 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"
#include "tools.h"
#include <OpenGL/gl.h>
#include "libft.h"

static void		print_error(GLint shader_id, GLenum type)
{
	GLint	length;
	char	*log;

	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
	if (length == 0)
		return ;
	log = malloc(length);
	glGetShaderInfoLog(shader_id, length, &length, log);
	if (type == GL_FRAGMENT_SHADER)
	{
		ft_putendl("Error fragment shader compilation:");
		ft_putendl(log);
	}
	else if (type == GL_VERTEX_SHADER)
	{
		ft_putendl("Error vertex shader compilation:");
		ft_putendl(log);
	}
	else if (type == GL_LINK_STATUS)
	{
		ft_putendl("Error linking shader compilation:");
		ft_putendl(log);
	}
	free(log);
}

static void		load_shader(char *fragment_path, t_shader *shader, GLenum type)
{
	const char	*source = read_file(fragment_path);
	GLint		size;
	GLint		success;
	GLuint		shader_id;

	if (source == NULL)
	{
		ft_putstr("Shader loading error\n");
		exit(0);
	}
	size = ft_strlen(source);
	shader_id = glCreateShader(type);
	if (type == GL_VERTEX_SHADER)
		shader->vertex_shader = shader_id;
	else if (type == GL_FRAGMENT_SHADER)
		shader->fragment_shader = shader_id;
	glShaderSource(shader_id, 1, &source, &size);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	print_error(shader_id, type);
	if (success == GL_FALSE)
		exit(0);
	else
		glAttachShader(shader->shader_program, shader_id);
}

t_shader		create_shader(char *vertex_path, char *fragment_path)
{
	t_shader	shader;
	GLint		is_linked;

	shader.shader_program = glCreateProgram();
	load_shader(vertex_path, &shader, GL_VERTEX_SHADER);
	load_shader(fragment_path, &shader, GL_FRAGMENT_SHADER);
	glLinkProgram(shader.shader_program);
	glGetProgramiv(shader.shader_program, GL_LINK_STATUS, &is_linked);
	if (is_linked == GL_FALSE)
	{
		print_error(shader.shader_program, GL_LINK_STATUS);
		exit(0);
	}
	return (shader);
}

void			destroy_shader(t_shader shader)
{
	glUseProgram(0);
	glDetachShader(shader.shader_program, shader.fragment_shader);
	glDetachShader(shader.shader_program, shader.vertex_shader);
	glDeleteProgram(shader.shader_program);
	glDeleteShader(shader.vertex_shader);
	glDeleteShader(shader.fragment_shader);
}
