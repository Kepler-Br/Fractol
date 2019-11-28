/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:20:41 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_head;
	t_list *iter;

	new_head = NULL;
	if (!lst || !f)
		return (NULL);
	new_head = ft_lst_elem_cpy(f(lst));
	iter = lst->next;
	while (iter != NULL)
	{
		if (f(iter))
		{
			ft_lst_add_tail(new_head, ft_lst_elem_cpy(f(iter)));
			iter = iter->next;
		}
		else
		{
			iter = new_head;
			ft_lstdelete(iter);
			return (NULL);
		}
	}
	return (new_head);
}
