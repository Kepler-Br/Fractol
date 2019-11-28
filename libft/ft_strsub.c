/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:24:17 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*new;

	if (s == NULL)
		return (NULL);
	i = 0;
	new = (char*)malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < (unsigned int)len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = 0;
	return (new);
}
