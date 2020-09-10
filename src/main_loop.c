/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:22:40 by nsena             #+#    #+#             */
/*   Updated: 2020/09/10 18:22:41 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mlx.h>
#include "main_loop.h"
#include "state.h"
#include <OpenGL/gl.h>
#include <stdlib.h>
#include "libft.h"

static int			loop(struct s_main_loop *this)
{
	this->state->loop(this->state);
	this->render(this);
	return (0);
}

static int			render(struct s_main_loop *this)
{
	this->state->render(this->state);
	glSwapAPPLE();
	return (0);
}

static void			run(struct s_main_loop *this)
{
	mlx_loop(this->mlx_instance.mlx);
}

static int			on_key(int keyid, struct s_main_loop *this)
{
	this->state->on_key(keyid, this->state);
	return (0);
}

static int			on_mouse_move(int x, int y, struct s_main_loop *this)
{
	const t_ivec2	position = (t_ivec2){x, y};
	t_ivec2			delta;

	delta = (t_ivec2){x - this->prev_mouse_position.x, y -
			this->prev_mouse_position.y};
	this->prev_mouse_position = position;
	this->state->on_mouse_move(position, delta, this->state);
	return (0);
}

static int			on_mouse_down(int keyid, int x, int y,
						struct s_main_loop *this)
{
	const t_ivec2 position = (t_ivec2){x, y};

	this->state->on_mouse_down(keyid, position, this->state);
	return (0);
}

static int			on_mouse_up(int keyid, int x, int y,
						struct s_main_loop *this)
{
	const t_ivec2 position = (t_ivec2){x, y};

	this->state->on_mouse_up(keyid, position, this->state);
	return (0);
}

static int			on_close(struct s_main_loop *this)
{
	this->state->on_close(this->state);
	t_main_loop_destroy(this);
	exit(0);
}

void				t_main_loop_destroy(struct s_main_loop *this)
{
	mlx_destroy_window(this->mlx_instance.mlx, this->mlx_instance.window);
	free(this);
}

static void			setup_hooks(t_main_loop *object)
{
	mlx_hook(object->mlx_instance.window, 2, 0,
		object->on_key, (void *)object);
	mlx_hook(object->mlx_instance.window, 6, 0,
		object->on_mouse_move, (void *)object);
	mlx_hook(object->mlx_instance.window, 4, 0,
		object->on_mouse_down, (void *)object);
	mlx_hook(object->mlx_instance.window, 5, 0,
		object->on_mouse_up, (void *)object);
	mlx_hook(object->mlx_instance.window, 17, 0,
		object->on_close, (void *)object);
	mlx_loop_hook(object->mlx_instance.mlx, object->loop, (void *)object);
}

t_main_loop			*t_main_loop_create(char *title, t_ivec2 window_geometry)
{
	t_main_loop		*object;

	ft_assert((object = (t_main_loop*)malloc(sizeof(t_main_loop))) != NULL,
			"t_main_loop_create: could not allocate memory.");
	ft_assert((object->mlx_instance.mlx = mlx_init()) != NULL &&
		(object->mlx_instance.window = mlx_new_window(object->mlx_instance.mlx,
		window_geometry.x, window_geometry.y, title)) != NULL,
		"t_main_loop_create: cannot init mlx.");
	object->prev_mouse_position = (t_ivec2){0, 0};
	object->mlx_instance.window_geometry = window_geometry;
	object->loop = &loop;
	object->render = &render;
	object->run = &run;
	object->on_key = &on_key;
	object->on_mouse_move = &on_mouse_move;
	object->on_mouse_down = &on_mouse_down;
	object->on_mouse_up = &on_mouse_up;
	object->on_close = &on_close;
	setup_hooks(object);
	return (object);
}
