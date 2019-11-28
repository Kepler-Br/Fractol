/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:22:47 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_size(long nb)
{
	int		size;

	size = 1;
	if (nb < 0)
	{
		nb = -nb;
		size++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char			*ft_itoa(int nb)
{
	long	size;
	char	*ret;
	long	n;

	n = (long)nb;
	size = get_size(n);
	if (!(ret = (char*)malloc((size + 1) * sizeof(char))))
		return (NULL);
	if (nb < 0)
	{
		ret[0] = '-';
		n = -n;
	}
	ret[size--] = '\0';
	if (n == 0)
		ret[0] = '0';
	while (n >= 1)
	{
		ret[size--] = (n % 10) + '0';
		n /= 10;
	}
	return (ret);
}
