/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:56:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/03 16:56:00 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_file(t_file *file)
{
	ft_memdel((void**)&file->name);
	ft_memdel((void**)&file->full_path);
	ft_memdel((void**)&file->stat);
	ft_memdel((void**)&file);
}

void		free_all_files(t_file *file)
{
	t_file	*files;

	while (file)
	{
		files = file->next;
		free_file(file);
		file = files;
	}
}

void		free_dir(t_dir *dir)
{
	int		i;

	i = 0;
	while (i < dir->size)
	{
		ft_memdel((void**)&dir->files_arr[i]->name);
		ft_memdel((void**)&dir->files_arr[i]->stat);
		ft_memdel((void**)&dir->files_arr[i]->link);
		ft_memdel((void**)&dir->files_arr[i]->login);
		ft_memdel((void**)&dir->files_arr[i]->full_path);
		ft_memdel((void**)&dir->files_arr[i]->group);
		ft_memdel((void**)&dir->files_arr[i]);
		i++;
	}
	ft_memdel((void**)&dir->files_arr);
	ft_memdel((void**)&dir);
}
