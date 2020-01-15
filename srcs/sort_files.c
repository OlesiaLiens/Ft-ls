/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:51:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/15 21:25:44 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static _Bool	check_for_swap(t_file *first, t_file *second, t_flags flags)
{
	int		i;

	i = 0;
	if (flags.t && second->stat->st_mtime != first->stat->st_mtime)
	{
		if (second->stat->st_mtime > first->stat->st_mtime)
			return (flags.r == 0);
		return (flags.r != 0);
	}
	while (first->name[i] && second->name[i])
	{
		if ((unsigned char)second->name[i] < (unsigned char)first->name[i] ||
			(second->name[i] == first->name[i] &&
			second->name[i + 1] == '\0' && first->name[i + 1] != '\0'))
			return (flags.r == 0);
		else if (first->name[i] == second->name[i])
			i++;
		else
			break ;
	}
	return (flags.r != 0);
}

t_file			**sort_arr(t_file **arr, t_flags flags, int size)
{
	t_file	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (check_for_swap(arr[i], arr[j], flags))
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

t_file			**sort_files(t_file *files, t_flags flags, int size)
{
	t_file	**arr;
	int		i;

	i = size - 1;
	arr = (t_file**)malloc(sizeof(t_file) * size);
	while (i >= 0)
	{
		arr[i] = files;
		files = files->next;
		i--;
	}
	if (flags.f == 0)
		return (sort_arr(arr, flags, size));
	return (arr);
}
