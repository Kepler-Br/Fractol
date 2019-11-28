/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:59:30 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *head)
{
	t_list *new_head;
	t_list *iter;
	t_list *temp;

	if (!head)
		return (NULL);
	new_head = ft_lst_elem_cpy(head);
	iter = head;
	while (iter->next != NULL)
	{
		temp = ft_lst_elem_cpy(iter->next);
		if (!temp)
		{
			ft_lstdelete(new_head);
			return (NULL);
		}
		ft_lst_add_tail(new_head, temp);
		iter = iter->next;
	}
	return (new_head);
}
