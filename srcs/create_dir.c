/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 18:20:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/03 18:20:00 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*create_dir(char *name, t_flags flags)
{
	t_dir		*dir;
	DIR			*open;
	t_dirent	*entry;

	if ((open = opendir(name)) == NULL)
	{
		error(name);
		return (NULL);
	}
	dir = (t_dir*)ft_memalloc(sizeof(t_dir));
	dir->name = name;
	while ((entry = readdir(open)) != NULL)
	{
		if (((flags.f || flags.a) && entry->d_name[0] == '.') ||
			entry->d_name[0] != '.')
		{
			add_file(dir, entry, flags);
		}
	}
	closedir(open);
	return (dir);
}
