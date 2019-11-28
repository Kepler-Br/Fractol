/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:37:45 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *data, size_t data_size)
{
	char *new_data;
	char *new_data_pointer;
	char *old_data_pointer;

	if (!(new_data = (char *)malloc(data_size)) || !data)
		return (NULL);
	new_data_pointer = new_data;
	old_data_pointer = (char *)data;
	while (data_size--)
	{
		*new_data_pointer = *old_data_pointer;
		old_data_pointer++;
		new_data_pointer++;
	}
	return (new_data);
}
