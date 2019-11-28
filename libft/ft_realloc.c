/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:55:04 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *arr, size_t arr_size, size_t size)
{
	void *new;

	if (!arr && size == 0)
		return (NULL);
	new = malloc((arr_size + size) * sizeof(char));
	new = ft_memcpy(new, arr, arr_size);
	free(arr);
	return (new);
}
