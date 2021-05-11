/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/25 13:59:18 by jkoers        #+#    #+#                 */
/*   Updated: 2021/01/08 22:35:46 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "internal.h"
#include <stdlib.h>
#include <stddef.h>
#define ARR_DEFAULT_SIZE 100

static t_arr	*ft_arr(size_t initial_size)
{
	t_arr	*arr;

	if (initial_size == 0)
		initial_size = ARR_DEFAULT_SIZE;
	arr = ft_malloc(sizeof(t_arr));
	arr->table = ft_malloc(initial_size * sizeof(void *));
	arr->start_i = 0;
	arr->length = 0;
	arr->size = initial_size;
	return (arr);
}

static void	*ft_arr_grow(t_arr *arr, size_t new_size)
{
	void		*new_table;

	new_table = ft_malloc(new_size * sizeof(void *));
	ft_memcpy(new_table, arr->table, arr->size * sizeof(void *));
	free(arr->table);
	arr->table = new_table;
	arr->size = new_size;
	return (arr->table);
}

void	*ft_arr_set(t_arr **arr, size_t i, void *value)
{
	if (arr == NULL || *arr == NULL)
		*arr = ft_arr(i + ARR_DEFAULT_SIZE);
	else if ((*arr)->start_i + i >= (*arr)->size)
		ft_arr_grow(*arr, (*arr)->size + i);
	(*arr)->table[(*arr)->start_i + i] = value;
	if ((*arr)->length <= i)
		(*arr)->length = i + 1;
	return (*((*arr)->table + (*arr)->start_i + i));
}

void	*ft_arr_get(const t_arr *arr, size_t i)
{
	if (arr == NULL)
		return (NULL);
	if (i > arr->length - 1)
		return (NULL);
	return (arr->table[arr->start_i + i]);
}

void	*ft_arr_push(t_arr **arr, void *value)
{
	size_t	i;

	if (arr == NULL || *arr == NULL)
		i = 0;
	else
		i = (*arr)->length;
	return (ft_arr_set(arr, i, value));
}
