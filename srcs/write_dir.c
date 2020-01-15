/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:14:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/03 15:14:00 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	show_l_flag(t_dir *dir)
{
	size_t	size_str;
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size_str = ((31 + dir->padding_nlink + dir->padding_login +
	dir->padding_group) * dir->size) + dir->names_len +
	dir->links_len + (dir->links_count * 4) + dir->size;
	if (dir->c_or_b_type)
		size_str += ((3 + dir->padding_maj + dir->padding_min) * dir->size);
	else
		size_str += (dir->padding_size * dir->size);
	res = (char*)malloc(size_str);
	while (i < dir->size)
	{
		j += fill_str(res + j, dir->files_arr[i], dir);
		i++;
	}
	write(1, res, j);
	free(res);
}

void	show_no_flags(t_dir *dir)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char*)malloc(dir->size + dir->names_len + 1);
	while (i < dir->size)
	{
		ft_memcpy((void*)(str + j), (void*)dir->files_arr[i]->name,
				dir->files_arr[i]->name_len);
		j += dir->files_arr[i]->name_len;
		str[j++] = '\n';
		i++;
	}
	write(1, str, dir->size + dir->names_len);
	free(str);
}

void	show_total(blkcnt_t total)
{
	char	*str;
	int		i;
	int		count;

	count = nbr_len(total);
	str = (char*)malloc(count + 7);
	ft_memcpy(str, "total ", 6);
	i = 5 + count;
	while (i > 5)
	{
		str[i] = (total % 10) + 48;
		total = total / 10;
		i--;
	}
	str[i + count + 1] = '\n';
	write(1, str, count + 7);
	free(str);
}

void	write_dir(t_dir *dir, t_flags flags, _Bool name, _Bool new_line)
{
	if (new_line)
		write(1, "\n", 1);
	if (name)
	{
		write(1, dir->name, ft_strlen(dir->name));
		write(1, ":\n", 2);
	}
	if (dir->size)
		dir->files_arr = sort_files(dir->files, flags, dir->size);
	if (flags.l && dir->size)
	{
		if (dir->name)
			show_total(dir->total);
		show_l_flag(dir);
	}
	else
		show_no_flags(dir);
}
