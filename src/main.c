/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:20:03 by nsena             #+#    #+#             */
/*   Updated: 2020/09/10 17:20:05 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GL_SILENCE_DEPRECATION
#include "main_loop.h"
#include "raymarch_state.h"
#include "julia_state.h"
#include "linear_alg.h"
#include "libft.h"

static void			print_help(void)
{
	write(1, "Invalid argument.\n", 18);
	write(1, "Here's valid arguments(choice one):\n", 36);
	write(1, "2D fractals:\n", 13);
	write(1, "julia, mandelbrot\n", 18);
	write(1, "3D fractals:\n", 13);
	write(1, "menger, mandelbulb\n", 19);
}

static int			is_valid_parameter(char *str)
{
	if (ft_strcmp("menger", str) == 0)
		return (1);
	if (ft_strcmp("mandelbulb", str) == 0)
		return (1);
	if (ft_strcmp("julia", str) == 0)
		return (1);
	if (ft_strcmp("mandelbrot", str) == 0)
		return (1);
	return (0);
}

static t_state		*state_from_parameter(char *str, t_main_loop *main_loop)
{
	t_state	*state;

	state = NULL;
	if (ft_strcmp("menger", str) == 0)
		state = t_raymarch_state_create(main_loop->mlx_instance,
									"./programs/menger.glsl");
	if (ft_strcmp("mandelbulb", str) == 0)
		state = t_raymarch_state_create(main_loop->mlx_instance,
									"./programs/mandelbulb.glsl");
	if (ft_strcmp("julia", str) == 0)
		state = t_julia_state_create(main_loop->mlx_instance,
								"./programs/julia.glsl");
	if (ft_strcmp("mandelbrot", str) == 0)
		state = t_julia_state_create(main_loop->mlx_instance,
								"./programs/mandelbrot.glsl");
	return (state);
}

int					main(int argc, char **argv)
{
	t_main_loop	*main_loop;
	t_state		*state;

	if (argc != 2)
	{
		print_help();
		exit(0);
	}
	if (!is_valid_parameter(argv[1]))
	{
		print_help();
		exit(0);
	}
	main_loop = t_main_loop_create("Fract'ol", (t_ivec2){1000, 1000});
	state = state_from_parameter(argv[1], main_loop);
	main_loop->state = state;
	main_loop->run(main_loop);
	return (0);
}
