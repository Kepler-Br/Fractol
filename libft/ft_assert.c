/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:39:52 by nsena             #+#    #+#             */
/*   Updated: 2020/08/29 17:39:54 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_assert(int condition, char *message_on_fail)
{
	if (!condition)
	{
		if (message_on_fail != NULL)
		{
			ft_putstr(message_on_fail);
			ft_putstr("\n");
		}
		else
		{
			ft_putstr("Assertion failed.\n");
		}
		exit(0);
	}
}
