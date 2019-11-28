/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_t_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:39:08 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_map_item	*t_map_find(t_map *this, void *key, size_t key_size)
{
	t_map_item *pointer;

	pointer = this->first_item;
	while (pointer)
	{
		if (key_size == pointer->key_size)
		{
			if (!ft_memcmp(pointer->key, key, key_size))
				return (pointer);
		}
		pointer = pointer->next_item;
	}
	return (NULL);
}

static void			t_map_emplace(t_map *this, t_map_item item)
{
	t_map_item *pointer;
	t_map_item *new_item;

	pointer = this->find(this, item.key, item.key_size);
	if (pointer)
	{
		free(pointer->value);
		pointer->value = ft_memdup(item.value, item.value_size);
	}
	else
	{
		pointer = this->first_item;
		while (pointer && pointer->next_item)
			pointer = pointer->next_item;
		new_item = (t_map_item *)malloc(sizeof(t_map_item));
		new_item->value_size = item.value_size;
		new_item->key_size = item.key_size;
		new_item->key = ft_memdup(item.key, item.key_size);
		new_item->value = ft_memdup(item.value, item.value_size);
		new_item->next_item = NULL;
		if (!pointer)
			this->first_item = new_item;
		else
			pointer->next_item = new_item;
	}
}

static void			t_map_erase(t_map *this)
{
	t_map_item *next_pointer;
	t_map_item *pointer;

	pointer = this->first_item;
	while (pointer != NULL)
	{
		next_pointer = pointer->next_item;
		free(pointer->value);
		free(pointer->key);
		free(pointer);
		pointer = next_pointer;
	}
	this->first_item = NULL;
}

static void			t_map_remove(t_map *this, void *key, size_t key_size)
{
	t_map_item *pointer;
	t_map_item *prev_pointer;

	pointer = this->first_item;
	prev_pointer = NULL;
	while (pointer)
	{
		if (key_size == pointer->key_size)
		{
			if (ft_memcmp(pointer->value, key, key_size))
				break ;
		}
		prev_pointer = pointer;
		pointer = pointer->next_item;
	}
	if (!pointer)
		return ;
	if (!prev_pointer)
		this->first_item = NULL;
	else
		prev_pointer->next_item = pointer->next_item;
	free(pointer->key);
	free(pointer->value);
	free(pointer);
}

t_map				*ft_make_t_map(void)
{
	t_map *object;

	object = (t_map *)malloc(sizeof(t_map));
	if (!object)
		return (NULL);
	object->first_item = NULL;
	object->emplace = t_map_emplace;
	object->find = t_map_find;
	object->erase = t_map_erase;
	object->remove = t_map_remove;
	return (object);
}
