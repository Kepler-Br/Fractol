/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cheer_me_up.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:36:10 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cheer_me_up(char *msg)
{
	if (ft_strequ(msg, "I'm sad") == 1)
	{
		ft_putendl("Everything gonna be all right!");
		ft_putstr("I 💖 you! ");
		ft_putendl("You are the coolest person ever.");
		ft_putendl("🐨 loves you too, by the way...");
	}
}
