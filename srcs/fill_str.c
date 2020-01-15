/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:10:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/15 15:10:00 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		rwx(blkcnt_t mode_number, char *str, int nb, const char *str_1)
{
	if (mode_number & 4)
		str[0] = 'r';
	else
		str[0] = '-';
	if (mode_number & 2)
		str[1] = 'w';
	else
		str[1] = '-';
	if (nb != 0)
	{
		if (mode_number & 1)
			str[2] = str_1[1];
		else
			str[2] = str_1[0];
	}
	else
	{
		if (mode_number & 1)
			str[2] = 'x';
		else
			str[2] = '-';
	}
}

int			fill_str_1(char *res, t_file *file, t_dir *dir)
{
	int	j;

	if (file->type == 'c' || file->type == 'b')
	{
		fill_spaces(res, 1 + dir->padding_maj - file->maj_len);
		j = 1 + dir->padding_maj;
		fill_number(res + j, major(file->stat->st_rdev), file->maj_len);
		res[j] = ',';
		fill_spaces(res + j + 1, 1 + dir->padding_min - file->min_len);
		j = j + 2 + dir->padding_min;
		fill_number(res + j, minor(file->stat->st_rdev), file->min_len);
	}
	else
	{
		if (dir->c_or_b_type)
			fill_spaces(res, 3 + dir->padding_maj +
				dir->padding_min - file->size_len);
		else
			fill_spaces(res, dir->padding_size - file->size_len);
		j = dir->c_or_b_type ? (3 + dir->padding_maj + dir->padding_min) :
			(dir->padding_size);
		fill_number(res + j, file->stat->st_size, file->size_len);
	}
	fill_spaces(res + j, 1);
	return (j + 1);
}

int			fill_str_2(char *res, t_file *file)
{
	time_t	now;
	char	*date;
	int		j;

	now = time(NULL);
	date = ctime(&file->stat->st_mtime);
	if (now - 15724800 > file->stat->st_mtime ||
		now + 15724800 < file->stat->st_mtime)
		ft_memcpy(date + 11, date + 19, 5);
	ft_memcpy(res, date + 4, 12);
	fill_spaces(res + 12, 1);
	ft_memcpy(res + 13, file->name, file->name_len);
	j = 13 + file->name_len;
	if (file->type == 'l')
	{
		ft_memcpy(res + j, " -> ", 4);
		ft_memcpy(res + j + 4, file->link, file->link_len);
		j = j + 4 + file->link_len;
	}
	res[j] = '\n';
	return (j + 1);
}

int			fill_str(char *res, t_file *file, t_dir *dir)
{
	t_stat	*stat;
	int		j;

	j = 12;
	stat = file->stat;
	res[0] = file->type;
	rwx(stat->st_mode >> 6 & 7, res + 1, stat->st_mode >> 11 & 1, "Ss");
	rwx(stat->st_mode >> 3 & 7, res + 4, stat->st_mode >> 10 & 1, "Ss");
	rwx(stat->st_mode & 7, res + 7, stat->st_mode >> 9 & 1, "Tt");
	fill_spaces(res + 10, 2 + dir->padding_nlink - file->nlink_len);
	j += dir->padding_nlink;
	fill_number(res + j, file->stat->st_nlink, file->nlink_len);
	fill_spaces(res + j, 1);
	ft_memcpy(res + j + 1, file->login, file->login_len);
	j = j + 1 + file->login_len;
	fill_spaces(res + j, dir->padding_login - file->login_len + 2);
	j = j + dir->padding_login - file->login_len + 2;
	ft_memcpy(res + j, file->group, file->group_len);
	j = j + file->group_len;
	fill_spaces(res + j, 2 + dir->padding_group - file->group_len);
	j = j + 2 + dir->padding_group - file->group_len;
	j += fill_str_1(res + j, file, dir);
	j += fill_str_2(res + j, file);
	return (j);
}
