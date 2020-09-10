/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:25:23 by nsena             #+#    #+#             */
/*   Updated: 2020/09/10 18:25:24 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_alg.h"

float		lerpf(float source, float target, float t)
{
	return ((1.0f - t) * source + t * target);
}

t_vec3		lerpvec3(t_vec3 source, t_vec3 target, float t)
{
	return (t_vec3){(1.0f - t) * source.x + t * target.x,
					(1.0f - t) * source.y + t * target.y,
					(1.0f - t) * source.z + t * target.z};
}

t_vec2		lerpvec2(t_vec2 source, t_vec2 target, float t)
{
	return (t_vec2){(1.0f - t) * source.x + t * target.x,
					(1.0f - t) * source.y + t * target.y};
}
