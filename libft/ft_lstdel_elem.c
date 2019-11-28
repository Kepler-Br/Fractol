/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 15:20:19 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_elem(t_list *elem)
{
	if (elem)
	{
		free(elem->content);
		elem->content = NULL;
		free(elem);
	}
}
