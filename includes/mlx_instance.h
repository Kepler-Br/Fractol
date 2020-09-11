/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_instance.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:15:22 by nsena             #+#    #+#             */
/*   Updated: 2020/09/11 13:15:23 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INSTANCE_H
# define MLX_INSTANCE_H

# import "linear_alg.h"

typedef struct	s_mlx_instance
{
	void		*mlx;
	void		*window;
	t_ivec2		window_geometry;
}				t_mlx_instance;

#endif
