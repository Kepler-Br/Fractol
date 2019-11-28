/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:17:38 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_gap(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

static int	get_first(char const *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!(is_gap(s[i])))
			return (i);
		i++;
	}
	return (i);
}

static int	get_last(char const *s)
{
	int i;

	i = ft_strlen((char*)s) - 1;
	while (i > 0)
	{
		if (!(is_gap(s[i])))
			return (i);
		i--;
	}
	return (i);
}

char		*ft_strtrim(char const *s)
{
	char	*new;
	int		first;
	int		last;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen((char*)s);
	first = get_first(s);
	last = get_last(s);
	if (last == 0)
	{
		new = (char *)malloc(1);
		if (!new)
			return (NULL);
		*new = '\0';
		return (new);
	}
	len = last - first + 1;
	new = ft_strsub(s, (unsigned int)first, (unsigned int)len);
	return (new);
}
