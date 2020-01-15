/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:55:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/13 18:55:00 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recursion(char *path, t_flags flags, _Bool name, _Bool new_line)
{
	t_dir	*dir;
	int		i;

	i = 0;
	if ((dir = create_dir(path, flags)))
	{
		write_dir(dir, flags, name, new_line);
		while (i < dir->size)
		{
			if (dir->files_arr[i]->type == 'd' &&
			ft_strcmp(dir->files_arr[i]->name, ".") &&
			ft_strcmp(dir->files_arr[i]->name, ".."))
			{
				recursion(dir->files_arr[i]->full_path, flags, 1, 1);
			}
			i++;
		}
		free_dir(dir);
	}
}
